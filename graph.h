#include <string>
#include <unordered_map>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>

#pragma once

using namespace std;
class Graph
{

public:
    Graph(string routesFileName, string airportFileName); //Constructor
    
    //GRAPH FUNCTIONS
    void insertVertex(string airportCode);
    void insertEdge(string firstAirport, string secondAirport, Edge edgeToInsert);
    list<Edge> incidentEdges(string airportCode);

    
private:



    //EDGE CLASS
    class Edge
    {
    public:
        Edge(string startAirport, string endAirport, string airlineCode); //Constructor

    private:
        string startAirport; //Starting airport ID string
        string endAirport; //Ending airport ID string
        string airlineCode; //4 Digit OpenFlights identifier for the airline serving the route
    };

    struct LatLong
    {
        double lat; // latitude
        double lon; // longitude
    };

    void translateDataToGraph(string routeFile, string airportFile);

    // Helper functions for translateDataToGraph().
    void mapStartAirportToEdge(string routeFile, unordered_map<string, vector<Edge>> &startAirportToEdge);
    void mapAirportsToLatLong(string airportFile);

    // Maps IATA to Latitude and Longitude.
    unordered_map<string, LatLong> airports;

    //PRIVATE VARIABLES USED FOR THE GRAPH CLASS
    unordered_map<string, list<Edge>> graphMap;

};