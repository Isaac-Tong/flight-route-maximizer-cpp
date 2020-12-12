#include "graph.h"
#include "cs225/PNG.h"
#include <algorithm> 

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

    //Uses Djikstra's algorithm to print the shortest path between two airports on the world map
    void printShortest(vector<string> path);

    void drawConnection(double x1, double y1, double x2, double y2);
    
    double translateXCoordinate(double lon);
    double translateYCoordinate(double lat);

private:
    Graph graph;
    cs225::PNG worldMap;
};