#include <string>
#include <unordered_map>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iostream>
#include "cs225/PNG.h"
#include <queue>
#define PI 3.14159265358979323846

#pragma once

using namespace std;
class Graph
{
public:
    // EDGE CLASS
    class Edge
    {
    public:
        Edge(string startAirport, string endAirport, string airlineCode, int distance); // Constructor
        string startAirport;                                                            // Starting airport ID string
        string endAirport;                                                              // Ending airport ID string
        string airlineCode;                                                             // 4 Digit OpenFlights identifier for the airline serving the route
        int weight;                                                                     // Weight of the edge. Calculated by the distance between the start and end airport
    };

    struct LatLong
    {
        double lat; // latitude
        double lon; // longitude
    };
    //Constructor. Takes in the name of the routes file and the name of the airport file
    Graph(string routesFileName, string airportFileName);
    //Copy constructor
    Graph(Graph &other);
    Graph();
    void printGraph();
    void printAirports();
    bool BFS(string startingAirport, string destinationAirport);
    // Getters to attain graph and airport to coordinate mapping
    unordered_map<string, LatLong> getAirportsMap();
    unordered_map<string, vector<Edge>> getGraphEdges();

    // //GRAPH FUNCTIONS
    // void insertVertex(string airportCode);
    // void insertEdge(string firstAirport, string secondAirport, Edge edgeToInsert);
    // vector<Edge> incidentEdges(string airportCode);
    
private:
    // Helper functions for constructor.
    void mapStartAirportToEdge(string routeFile);
    void mapAirportsToLatLong(string airportFile);
    double weight(string firstAirport, string secondAirport);

    // Maps IATA to Latitude and Longitude.
    unordered_map<string, LatLong> airportsMap;

    //PRIVATE VARIABLES USED FOR THE GRAPH CLASS
    unordered_map<string, vector<Edge>> graphEdges;
};