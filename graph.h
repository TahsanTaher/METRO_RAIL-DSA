#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>

// ─────────────────────────────────────────────
//  Edge: destination station index + distance
// ─────────────────────────────────────────────
struct Edge {
    int   dest;      // index of destination station
    int   distance;  // distance in minutes (travel time)
    std::string line; // tube line name
};

// ─────────────────────────────────────────────
//  Graph: weighted undirected graph via
//  adjacency list + station name registry
// ─────────────────────────────────────────────
class MetroGraph {
public:
    // Add a station and return its index
    int addStation(const std::string& name) {
        if (nameToIndex.count(name)) return nameToIndex[name];
        int idx = (int)stations.size();
        stations.push_back(name);
        adjList.push_back({});
        nameToIndex[name] = idx;
        return idx;
    }

    // Add a bidirectional (undirected) weighted edge
    void addEdge(const std::string& from,
                 const std::string& to,
                 int distance,
                 const std::string& line) {
        int u = addStation(from);
        int v = addStation(to);
        adjList[u].push_back({v, distance, line});
        adjList[v].push_back({u, distance, line});
    }

    // Total number of stations
    int stationCount() const { return (int)stations.size(); }

    // Station name from index
    const std::string& nameOf(int idx) const { return stations[idx]; }

    // Index from name (-1 if not found)
    int indexOf(const std::string& name) const {
        auto it = nameToIndex.find(name);
        return (it != nameToIndex.end()) ? it->second : -1;
    }

    // Adjacency list for a given station index
    const std::vector<Edge>& neighbors(int idx) const { return adjList[idx]; }

    // Print all stations (numbered list)
    void listStations() const {
        std::cout << "\n  ╔══════════════════════════════════════════╗\n";
        std::cout <<   "  ║        LONDON UNDERGROUND STATIONS       ║\n";
        std::cout <<   "  ╚══════════════════════════════════════════╝\n";
        for (int i = 0; i < (int)stations.size(); ++i) {
            std::cout << "   [" << std::setw(2) << i + 1 << "]  " << stations[i] << "\n";
        }
        std::cout << "\n  Total stations: " << stations.size() << "\n";
    }

    // Print neighbors of a station
    void showNeighbors(const std::string& name) const {
        int idx = indexOf(name);
        if (idx == -1) {
            std::cout << "  Station not found: " << name << "\n";
            return;
        }
        std::cout << "\n  Neighbors of [" << name << "]:\n";
        for (const Edge& e : adjList[idx]) {
            std::cout << "   ─▶  " << std::left << std::setw(30) << stations[e.dest]
                      << "  " << std::setw(2) << e.distance << " min"
                      << "  (" << e.line << ")\n";
        }
    }

private:
    std::vector<std::string>      stations;    // index → name
    std::vector<std::vector<Edge>> adjList;    // index → edges
    std::unordered_map<std::string, int> nameToIndex; // name → index
};
