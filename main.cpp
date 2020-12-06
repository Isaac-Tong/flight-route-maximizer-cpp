#include "graph.h"
#include "flightsVizualizer.h"
#include <string>

using namespace std;
int main(int argc, char *argv[]) {
    string airportFile = "./dataset/airports_dataset.txt";
    // string airportFile = "./dataset/test.txt";
    string routesFile = "./dataset/routes_dataset.txt";
    Graph newGraph(routesFile, airportFile);

    // newGraph.printAirports();
    // newGraph.printGraph();

    flightsVizualizer vizualizer;
    vizualizer.printProjection();

    return 0;
}