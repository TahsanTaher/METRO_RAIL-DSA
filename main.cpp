/*
 * ══════════════════════════════════════════════════════════════════
 *   London Underground Metro Rail System — DSA Project
 *   Data Structure: Weighted Undirected Graph (Adjacency List)
 *   Algorithm     : Dijkstra's Shortest Path (Min-Heap / Priority Queue)
 *   Time Complexity: O((V + E) log V)
 * ══════════════════════════════════════════════════════════════════
 *
 *  Build:  g++ -std=c++17 -O2 main.cpp -o metro
 *  Run  :  ./metro
 */

#include "graph.h"
#include "dijkstra.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

// ─────────────────────────────────────────────
//  Populate graph with London Underground data
//  Edges represent travel time in minutes
//  (approximate, based on TfL timetable)
// ─────────────────────────────────────────────
void buildLondonUnderground(MetroGraph& g) {

    // ── Central Line ──────────────────────────
    g.addEdge("Ealing Broadway",       "West Acton",           3,  "Central Line");
    g.addEdge("West Acton",            "North Acton",          2,  "Central Line");
    g.addEdge("North Acton",           "East Acton",           2,  "Central Line");
    g.addEdge("East Acton",            "White City",           2,  "Central Line");
    g.addEdge("White City",            "Shepherd's Bush",      2,  "Central Line");
    g.addEdge("Shepherd's Bush",       "Holland Park",         2,  "Central Line");
    g.addEdge("Holland Park",          "Notting Hill Gate",    2,  "Central Line");
    g.addEdge("Notting Hill Gate",     "Queensway",            2,  "Central Line");
    g.addEdge("Queensway",             "Lancaster Gate",       2,  "Central Line");
    g.addEdge("Lancaster Gate",        "Marble Arch",          2,  "Central Line");
    g.addEdge("Marble Arch",           "Bond Street",          2,  "Central Line");
    g.addEdge("Bond Street",           "Oxford Circus",        2,  "Central Line");
    g.addEdge("Oxford Circus",         "Tottenham Court Road", 2,  "Central Line");
    g.addEdge("Tottenham Court Road",  "Holborn",              2,  "Central Line");
    g.addEdge("Holborn",               "Chancery Lane",        2,  "Central Line");
    g.addEdge("Chancery Lane",         "St. Paul's",           2,  "Central Line");
    g.addEdge("St. Paul's",            "Bank",                 2,  "Central Line");
    g.addEdge("Bank",                  "Liverpool Street",     3,  "Central Line");
    g.addEdge("Liverpool Street",      "Bethnal Green",        3,  "Central Line");
    g.addEdge("Bethnal Green",         "Mile End",             3,  "Central Line");
    g.addEdge("Mile End",              "Stratford",            5,  "Central Line");

    // ── Jubilee Line ──────────────────────────
    g.addEdge("Stanmore",              "Canons Park",          3,  "Jubilee Line");
    g.addEdge("Canons Park",           "Queensbury",           2,  "Jubilee Line");
    g.addEdge("Queensbury",            "Kingsbury",            2,  "Jubilee Line");
    g.addEdge("Kingsbury",             "Wembley Park",         4,  "Jubilee Line");
    g.addEdge("Wembley Park",          "Neasden",              3,  "Jubilee Line");
    g.addEdge("Neasden",               "Dollis Hill",          2,  "Jubilee Line");
    g.addEdge("Dollis Hill",           "Willesden Green",      2,  "Jubilee Line");
    g.addEdge("Willesden Green",       "Kilburn",              2,  "Jubilee Line");
    g.addEdge("Kilburn",               "West Hampstead",       2,  "Jubilee Line");
    g.addEdge("West Hampstead",        "Finchley Road",        2,  "Jubilee Line");
    g.addEdge("Finchley Road",         "Swiss Cottage",        2,  "Jubilee Line");
    g.addEdge("Swiss Cottage",         "St. John's Wood",      2,  "Jubilee Line");
    g.addEdge("St. John's Wood",       "Baker Street",         3,  "Jubilee Line");
    g.addEdge("Baker Street",          "Bond Street",          3,  "Jubilee Line");
    g.addEdge("Bond Street",           "Green Park",           2,  "Jubilee Line");
    g.addEdge("Green Park",            "Westminster",          2,  "Jubilee Line");
    g.addEdge("Westminster",           "Waterloo",             2,  "Jubilee Line");
    g.addEdge("Waterloo",              "Southwark",            2,  "Jubilee Line");
    g.addEdge("Southwark",             "London Bridge",        2,  "Jubilee Line");
    g.addEdge("London Bridge",         "Bermondsey",           2,  "Jubilee Line");
    g.addEdge("Bermondsey",            "Canada Water",         2,  "Jubilee Line");
    g.addEdge("Canada Water",          "Canary Wharf",         3,  "Jubilee Line");
    g.addEdge("Canary Wharf",          "North Greenwich",      4,  "Jubilee Line");
    g.addEdge("North Greenwich",       "Canning Town",         3,  "Jubilee Line");
    g.addEdge("Canning Town",          "West Ham",             3,  "Jubilee Line");
    g.addEdge("West Ham",              "Stratford",            3,  "Jubilee Line");

    // ── Northern Line (Charing Cross branch) ──
    g.addEdge("Edgware",               "Burnt Oak",            4,  "Northern Line");
    g.addEdge("Burnt Oak",             "Colindale",            2,  "Northern Line");
    g.addEdge("Colindale",             "Hendon Central",       3,  "Northern Line");
    g.addEdge("Hendon Central",        "Brent Cross",          3,  "Northern Line");
    g.addEdge("Brent Cross",           "Golders Green",        2,  "Northern Line");
    g.addEdge("Golders Green",         "Hampstead",            3,  "Northern Line");
    g.addEdge("Hampstead",             "Belsize Park",         2,  "Northern Line");
    g.addEdge("Belsize Park",          "Chalk Farm",           2,  "Northern Line");
    g.addEdge("Chalk Farm",            "Camden Town",          2,  "Northern Line");
    g.addEdge("Camden Town",           "Euston",               3,  "Northern Line");
    g.addEdge("Euston",                "Warren Street",        2,  "Northern Line");
    g.addEdge("Warren Street",         "Goodge Street",        2,  "Northern Line");
    g.addEdge("Goodge Street",         "Tottenham Court Road", 2,  "Northern Line");
    g.addEdge("Tottenham Court Road",  "Leicester Square",     2,  "Northern Line");
    g.addEdge("Leicester Square",      "Charing Cross",        2,  "Northern Line");
    g.addEdge("Charing Cross",         "Waterloo",             2,  "Northern Line");
    g.addEdge("Waterloo",              "Kennington",           3,  "Northern Line");
    g.addEdge("Kennington",            "Oval",                 2,  "Northern Line");
    g.addEdge("Oval",                  "Stockwell",            2,  "Northern Line");
    g.addEdge("Stockwell",             "Clapham North",        2,  "Northern Line");
    g.addEdge("Clapham North",         "Clapham Common",       2,  "Northern Line");
    g.addEdge("Clapham Common",        "Clapham South",        2,  "Northern Line");
    g.addEdge("Clapham South",         "Balham",               2,  "Northern Line");
    g.addEdge("Balham",                "Tooting Bec",          2,  "Northern Line");
    g.addEdge("Tooting Bec",           "Tooting Broadway",     2,  "Northern Line");
    g.addEdge("Tooting Broadway",      "Colliers Wood",        2,  "Northern Line");
    g.addEdge("Colliers Wood",         "South Wimbledon",      2,  "Northern Line");
    g.addEdge("South Wimbledon",       "Morden",               2,  "Northern Line");

    // ── Victoria Line ─────────────────────────
    g.addEdge("Brixton",               "Stockwell",            3,  "Victoria Line");
    g.addEdge("Stockwell",             "Vauxhall",             2,  "Victoria Line");
    g.addEdge("Vauxhall",              "Pimlico",              2,  "Victoria Line");
    g.addEdge("Pimlico",               "Victoria",             2,  "Victoria Line");
    g.addEdge("Victoria",              "Green Park",           2,  "Victoria Line");
    g.addEdge("Green Park",            "Oxford Circus",        2,  "Victoria Line");
    g.addEdge("Oxford Circus",         "Warren Street",        2,  "Victoria Line");
    g.addEdge("Warren Street",         "Euston",               2,  "Victoria Line");
    g.addEdge("Euston",                "King's Cross St. Pancras", 2, "Victoria Line");
    g.addEdge("King's Cross St. Pancras", "Highbury & Islington", 3, "Victoria Line");
    g.addEdge("Highbury & Islington",  "Finsbury Park",        3,  "Victoria Line");
    g.addEdge("Finsbury Park",         "Seven Sisters",        4,  "Victoria Line");
    g.addEdge("Seven Sisters",         "Tottenham Hale",       2,  "Victoria Line");
    g.addEdge("Tottenham Hale",        "Blackhorse Road",      3,  "Victoria Line");
    g.addEdge("Blackhorse Road",       "Walthamstow Central",  2,  "Victoria Line");

    // ── Piccadilly Line (selected) ─────────────
    g.addEdge("Heathrow Terminal 5",   "Heathrow Terminals 2&3", 5, "Piccadilly Line");
    g.addEdge("Heathrow Terminals 2&3","Hatton Cross",          4,  "Piccadilly Line");
    g.addEdge("Hatton Cross",          "Hounslow West",         3,  "Piccadilly Line");
    g.addEdge("Hounslow West",         "Hounslow Central",      2,  "Piccadilly Line");
    g.addEdge("Hounslow Central",      "Hounslow East",         2,  "Piccadilly Line");
    g.addEdge("Hounslow East",         "Osterley",              3,  "Piccadilly Line");
    g.addEdge("Osterley",              "Boston Manor",          2,  "Piccadilly Line");
    g.addEdge("Boston Manor",          "Northfields",           2,  "Piccadilly Line");
    g.addEdge("Northfields",           "South Ealing",          2,  "Piccadilly Line");
    g.addEdge("South Ealing",          "Acton Town",            3,  "Piccadilly Line");
    g.addEdge("Acton Town",            "Hammersmith",           5,  "Piccadilly Line");
    g.addEdge("Hammersmith",           "Baron's Court",         2,  "Piccadilly Line");
    g.addEdge("Baron's Court",         "Earl's Court",          2,  "Piccadilly Line");
    g.addEdge("Earl's Court",          "Gloucester Road",       3,  "Piccadilly Line");
    g.addEdge("Gloucester Road",       "South Kensington",      2,  "Piccadilly Line");
    g.addEdge("South Kensington",      "Knightsbridge",         3,  "Piccadilly Line");
    g.addEdge("Knightsbridge",         "Hyde Park Corner",      2,  "Piccadilly Line");
    g.addEdge("Hyde Park Corner",      "Green Park",            2,  "Piccadilly Line");
    g.addEdge("Green Park",            "Piccadilly Circus",     2,  "Piccadilly Line");
    g.addEdge("Piccadilly Circus",     "Leicester Square",      2,  "Piccadilly Line");
    g.addEdge("Leicester Square",      "Covent Garden",         2,  "Piccadilly Line");
    g.addEdge("Covent Garden",         "Holborn",               2,  "Piccadilly Line");
    g.addEdge("Holborn",               "Russell Square",        2,  "Piccadilly Line");
    g.addEdge("Russell Square",        "King's Cross St. Pancras", 2, "Piccadilly Line");
    g.addEdge("King's Cross St. Pancras", "Caledonian Road",   3,  "Piccadilly Line");
    g.addEdge("Caledonian Road",       "Holloway Road",         2,  "Piccadilly Line");
    g.addEdge("Holloway Road",         "Arsenal",               2,  "Piccadilly Line");
    g.addEdge("Arsenal",               "Finsbury Park",         2,  "Piccadilly Line");

    // ── Circle/District Line (selected) ───────
    g.addEdge("Edgware Road",          "Baker Street",          3,  "Circle Line");
    g.addEdge("Baker Street",          "Great Portland Street", 2,  "Circle Line");
    g.addEdge("Great Portland Street", "Euston Square",         2,  "Circle Line");
    g.addEdge("Euston Square",         "King's Cross St. Pancras", 2, "Circle Line");
    g.addEdge("King's Cross St. Pancras", "Farringdon",         3,  "Circle Line");
    g.addEdge("Farringdon",            "Barbican",              2,  "Circle Line");
    g.addEdge("Barbican",              "Moorgate",              2,  "Circle Line");
    g.addEdge("Moorgate",              "Liverpool Street",      2,  "Circle Line");
    g.addEdge("Liverpool Street",      "Aldgate",               2,  "Circle Line");
    g.addEdge("Aldgate",               "Tower Hill",            2,  "Circle Line");
    g.addEdge("Tower Hill",            "Monument",              2,  "Circle Line");
    g.addEdge("Monument",              "Cannon Street",         2,  "Circle Line");
    g.addEdge("Cannon Street",         "Mansion House",         2,  "Circle Line");
    g.addEdge("Mansion House",         "Blackfriars",           2,  "Circle Line");
    g.addEdge("Blackfriars",           "Temple",                2,  "Circle Line");
    g.addEdge("Temple",                "Embankment",            2,  "Circle Line");
    g.addEdge("Embankment",            "Westminster",           2,  "Circle Line");
    g.addEdge("Westminster",           "St. James's Park",      2,  "Circle Line");
    g.addEdge("St. James's Park",      "Victoria",              2,  "Circle Line");
    g.addEdge("Victoria",              "Sloane Square",         3,  "Circle Line");
    g.addEdge("Sloane Square",         "South Kensington",      3,  "Circle Line");
    g.addEdge("South Kensington",      "Gloucester Road",       2,  "Circle Line");
    g.addEdge("Gloucester Road",       "High Street Kensington",3,  "Circle Line");
    g.addEdge("High Street Kensington","Notting Hill Gate",      3,  "Circle Line");
    g.addEdge("Notting Hill Gate",     "Bayswater",             2,  "Circle Line");
    g.addEdge("Bayswater",             "Paddington",            2,  "Circle Line");
    g.addEdge("Paddington",            "Edgware Road",          3,  "Circle Line");

    // ── Metropolitan Line (selected) ───────────
    g.addEdge("Aldgate",               "Baker Street",          8,  "Metropolitan Line");
    g.addEdge("Baker Street",          "Harrow-on-the-Hill",   15,  "Metropolitan Line");
}

// ─────────────────────────────────────────────
//  Utility: read a line from stdin safely
// ─────────────────────────────────────────────
std::string getLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

// ─────────────────────────────────────────────
//  Display main menu banner
// ─────────────────────────────────────────────
void printMenu() {
    std::cout << "\n";
    std::cout << "  ╔═══════════════════════════════════════════════╗\n";
    std::cout << "  ║   🚇  LONDON UNDERGROUND ROUTE PLANNER  🚇    ║\n";
    std::cout << "  ║         DSA Project — Dijkstra's Algorithm     ║\n";
    std::cout << "  ╠═══════════════════════════════════════════════╣\n";
    std::cout << "  ║  [1]  Find shortest path between stations      ║\n";
    std::cout << "  ║  [2]  List all stations                        ║\n";
    std::cout << "  ║  [3]  Show neighbours of a station             ║\n";
    std::cout << "  ║  [4]  Show graph info (V & E counts)           ║\n";
    std::cout << "  ║  [5]  Exit                                     ║\n";
    std::cout << "  ╚═══════════════════════════════════════════════╝\n";
    std::cout << "  Choice: ";
}

// ─────────────────────────────────────────────
//  Count total directed edges ÷ 2 = undirected
// ─────────────────────────────────────────────
int countEdges(const MetroGraph& g) {
    int total = 0;
    for (int i = 0; i < g.stationCount(); ++i)
        total += (int)g.neighbors(i).size();
    return total / 2; // each undirected edge stored twice
}

// ─────────────────────────────────────────────
//  Main
// ─────────────────────────────────────────────
int main() {
    MetroGraph graph;
    buildLondonUnderground(graph);

    std::cout << "\n  Graph loaded: "
              << graph.stationCount() << " stations, "
              << countEdges(graph)    << " connections.\n";

    std::string choice;
    while (true) {
        printMenu();
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::string src = getLine("\n  Source station      : ");
            std::string dst = getLine("  Destination station : ");
            PathResult result = Dijkstra::shortestPath(graph, src, dst);
            Dijkstra::printResult(result);

        } else if (choice == "2") {
            graph.listStations();

        } else if (choice == "3") {
            std::string name = getLine("\n  Station name: ");
            graph.showNeighbors(name);

        } else if (choice == "4") {
            std::cout << "\n  ── Graph Statistics ──\n";
            std::cout << "  Vertices (stations) : " << graph.stationCount() << "\n";
            std::cout << "  Edges (connections) : " << countEdges(graph)    << "\n";
            std::cout << "  Representation      : Adjacency list\n";
            std::cout << "  Algorithm           : Dijkstra (min-heap)\n";
            std::cout << "  Time complexity     : O((V + E) log V)\n";
            std::cout << "  Space complexity    : O(V + E)\n\n";

        } else if (choice == "5" || choice == "q" || choice == "Q") {
            std::cout << "\n  Goodbye! Mind the gap. 🚇\n\n";
            break;

        } else {
            std::cout << "  Invalid choice. Please enter 1–5.\n";
        }
    }

    return 0;
}
