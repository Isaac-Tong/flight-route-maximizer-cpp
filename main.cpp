#include "graph.h"
#include "flightsVizualizer.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    // Parse arguments from user
    string startingAirport = argv[1];
    string destinationAirport = argv[2];
    string routesFile = argv[3];
    string airportsFile = argv[4];

    // Remove previous BFS and Dijkstra's outputs.
    system("rm bfs_airports_visited.txt");
    system("rm DijkstraOutput.txt");

    // Check if we should use default route and airport files
    if (routesFile == "default")
    {
        routesFile = "./dataset/routes_subset.txt";
    }

    if (airportsFile == "default")
    {
        airportsFile = "./dataset/airports_extended_formatted.txt";
    }

    ifstream routesFileIF(routesFile);
    ifstream airportsFileIF(airportsFile);

    if (!routesFileIF.is_open()) 
    {
        cout << "Routes file provided is invalid. Using default routes file." << endl;
        routesFile = "./dataset/routes_subset.txt";
    }
    if (!airportsFileIF.is_open()) 
    {
        cout << "Airports file provided is invalid. Using default airports file." << endl;
        airportsFile = "./dataset/airports_extended_formatted.txt";
    }

    // Create graph structure
    Graph flightGraph(routesFile, airportsFile);

    //Run BFS to see if path is possible.
    if (flightGraph.BFS(startingAirport, destinationAirport)) 
    {
        cout << "A path between " << startingAirport << " and " << destinationAirport << " exists." << endl;
    }
    else 
    {
        cout << "A path between " << startingAirport << " and " << destinationAirport << " does NOT exist." << endl;
        routesFileIF.close();
        airportsFileIF.close();
        return 0;
    }
    cout << "Saving BFS path to bfs_airports_visited.txt" << endl;

    // Run Dijkstra's algorithm and BFS to find the shortest path
    // Output may have previous airport as "000" if the airport is not in the dataset being used.
    flightGraph.Dijkstra(startingAirport, destinationAirport);
    cout << "Saving Dijktra's Algorithm output to DijkstraOutput.txt" << endl;

    flightsVizualizer vizualizer(flightGraph);
    vizualizer.printProjection();

    routesFileIF.close();
    airportsFileIF.close();

    return 0;
}