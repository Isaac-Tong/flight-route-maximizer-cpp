#include "graph.h"
#include "cs225/PNG.h"

#pragma once

using namespace std;
class flightsVizualizer
{
public:
    //Constructor takes in a graph object
    flightsVizualizer(Graph graph);

    //Helper function to draw a circle to represent an airport given its lattitude and longitude
    void markAirport(double lat, double lon);

    //Outputs the worldMap as a PNG
    void printProjection();

    void drawConnection(double x1, double y1, double x2, double y2);

private:
    Graph graph;
    cs225::PNG worldMap;
};