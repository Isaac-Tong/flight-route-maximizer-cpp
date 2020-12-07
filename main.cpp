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

    flightsVizualizer vizualizer(newGraph);
    double lat = 51.4700;
    double lon = -0.4543;
    vizualizer.markAirport(lat, lon);
    vizualizer.printProjection();

    return 0;
}