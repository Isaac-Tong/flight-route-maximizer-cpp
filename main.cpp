#include "graph.h"
#include "flightsVizualizer.h"
#include <string>

using namespace std;
int main(int argc, char *argv[]) {
    string airportFile = "./dataset/airports_dataset.txt";
    // string airportFile = "./dataset/test.txt";
    string routesFile = "./dataset/routes_extended_dataset.txt";
    Graph newGraph(routesFile, airportFile);

    //newGraph.printAirports();
    newGraph.printGraph();

<<<<<<< HEAD
    flightsVizualizer vizualizer(newGraph);
    double lat = 51.4700;
    double lon = -0.4543;
    vizualizer.markAirport(lat, lon);
    vizualizer.printProjection();
=======
    // flightsVizualizer vizualizer;
    // vizualizer.printProjection();
>>>>>>> 81273edc7066ef16f25b12a4fb1766f32cb33fb4

    return 0;
}