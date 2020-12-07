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

    void drawConnection(int x1, int y1, int x2, int y2);

private:
    Graph graph;
    cs225::PNG worldMap;
};