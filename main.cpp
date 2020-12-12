#include "graph.h"
#include "flightsVizualizer.h"
#include <string>

using namespace std;
int main(int argc, char *argv[])
{
    // Parse arguments from user
    string startingAirport = argv[1];
    string destinationAirport = argv[2];
    string routesFile = argv[3];
    string airportFile = argv[4];

    // Check if we should use default route and airport files
    if (routesFile == "default")
    {
        routesFile = "./dataset/routes_dataset.txt";
    }

    if (airportFile == "default")
    {
        airportFile = "./dataset/airports_extended_formatted.txt";
    }

    // Create graph structure
    Graph flightGraph(routesFile, airportFile);

    //Run Dijkstra's algorithm and BFS to find the shortest path
    flightGraph.Dijkstra(startingAirport, destinationAirport);

    return 0;
}