#include "graph.h"
#include "flightsVizualizer.h"
#include <string>

using namespace std;
int main(int argc, char *argv[]) {
    string airportFile = "./dataset/airports_dataset.txt";
    // string airportFile = "./dataset/test.txt";
    string routesFile = "./dataset/routes_dataset.txt";
    Graph newGraph(routesFile, airportFile);

    newGraph.printAirports();
    // newGraph.printGraph();

    flightsVizualizer vizualizer(newGraph);
    double lat1 = 51.4700;
    double lon1 = -0.4543;
    vizualizer.markAirport(lat1, lon1);

    double lat2 = 41.9742;
    double lon2 = -87.9073;
    vizualizer.markAirport(lat2, lon2);

    vizualizer.drawConnection(1531.54, 764.163, 1026.4, 684.681);
    vizualizer.printProjection();

    return 0;
}