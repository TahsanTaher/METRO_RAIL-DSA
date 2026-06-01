#pragma once
#include "graph.h"
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <algorithm>
#include <iomanip>

// ─────────────────────────────────────────────
//  Result of a Dijkstra query
// ─────────────────────────────────────────────
struct PathResult {
    std::vector<std::string> path;      // station names in order
    std::vector<std::string> lines;     // tube line for each hop
    int totalDistance = -1;             // -1 means no path found
    bool found = false;
};

// ─────────────────────────────────────────────
//  Dijkstra's shortest-path algorithm
//
//  Data structures used:
//    - dist[]     : shortest known distance to each node
//    - prev[]     : predecessor node for path reconstruction
//    - prevLine[] : which line was used to reach each node
//    - pq         : min-heap (priority_queue with greater<>)
//                   stores (distance, nodeIndex) pairs
//
//  Time complexity : O((V + E) log V)
//  Space complexity: O(V)
// ─────────────────────────────────────────────
class Dijkstra {
public:
    static PathResult shortestPath(const MetroGraph& graph,
                                   const std::string& srcName,
                                   const std::string& dstName) {
        PathResult result;

        int src = graph.indexOf(srcName);
        int dst = graph.indexOf(dstName);

        if (src == -1) { std::cout << "  Station not found: " << srcName << "\n"; return result; }
        if (dst == -1) { std::cout << "  Station not found: " << dstName << "\n"; return result; }
        if (src == dst) {
            result.found = true;
            result.totalDistance = 0;
            result.path = {srcName};
            return result;
        }

        int n = graph.stationCount();
        const int INF = std::numeric_limits<int>::max();

        // Distance array — initialised to infinity
        std::vector<int> dist(n, INF);
        // Predecessor array — for path reconstruction
        std::vector<int> prev(n, -1);
        // Which line was used to reach each node
        std::vector<std::string> prevLine(n, "");

        dist[src] = 0;

        // Min-heap: (distance, nodeIndex)
        // std::greater makes smallest distance pop first
        using PQItem = std::pair<int, int>;
        std::priority_queue<PQItem, std::vector<PQItem>, std::greater<PQItem>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            // Skip stale entries (lazy deletion)
            if (d > dist[u]) continue;

            // Early exit when destination is reached
            if (u == dst) break;

            // Relax all outgoing edges
            for (const Edge& e : graph.neighbors(u)) {
                int newDist = dist[u] + e.distance;
                if (newDist < dist[e.dest]) {
                    dist[e.dest] = newDist;
                    prev[e.dest]  = u;
                    prevLine[e.dest] = e.line;
                    pq.push({newDist, e.dest});
                }
            }
        }

        if (dist[dst] == INF) return result; // No path exists

        // ── Reconstruct path by tracing predecessors ──
        result.found = true;
        result.totalDistance = dist[dst];

        std::vector<int> pathIdx;
        for (int cur = dst; cur != -1; cur = prev[cur])
            pathIdx.push_back(cur);
        std::reverse(pathIdx.begin(), pathIdx.end());

        for (int i = 0; i < (int)pathIdx.size(); ++i) {
            result.path.push_back(graph.nameOf(pathIdx[i]));
            if (i > 0) result.lines.push_back(prevLine[pathIdx[i]]);
        }

        return result;
    }

    // Pretty-print the result
    static void printResult(const PathResult& res) {
        if (!res.found) {
            std::cout << "\n  No path found between the selected stations.\n";
            return;
        }

        std::cout << "\n  ╔══════════════════════════════════════════╗\n";
        std::cout <<   "  ║            SHORTEST ROUTE FOUND          ║\n";
        std::cout <<   "  ╚══════════════════════════════════════════╝\n\n";

        std::string currentLine = "";
        for (int i = 0; i < (int)res.path.size(); ++i) {
            if (i == 0) {
                std::cout << "   🚉  " << res.path[i] << "  (start)\n";
            } else {
                const std::string& line = res.lines[i - 1];
                if (line != currentLine) {
                    std::cout << "       │  [Take " << line << "]\n";
                    currentLine = line;
                }
                if (i == (int)res.path.size() - 1)
                    std::cout << "   🏁  " << res.path[i] << "  (destination)\n";
                else
                    std::cout << "   🚇  " << res.path[i] << "\n";
            }
        }

        std::cout << "\n   Total stops   : " << (int)res.path.size() - 1 << "\n";
        std::cout <<   "   Travel time   : " << res.totalDistance << " minutes\n";
        std::cout <<   "   Route length  : " << res.path.size() << " stations\n\n";
    }
};
