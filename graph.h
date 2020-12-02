#include <string>
#include <unordered_map> 
#include <fstream> 
#include <sstream>
#include <vector>

#pragma once

using namespace std;
class Graph 
{

public:
    Graph(string routeFile, string airportFile);
    
private:
    class Edge 
    {  
    public:
        Edge(string startAirport, string endAirport, string airlineCode);
        string startAirport;
        string endAirport;
        string airlineCode;
    };

    struct LatLong 
    {
        double lat; // latitude
        double lon; // longitude
    };

    void translateDataToGraph(string routeFile, string airportFile);

    // Helper functions for translateDataToGraph().
    void mapStartAirportToEdge(string routeFile, unordered_map<string, vector<Edge>>& startAirportToEdge);
    void mapAirportsToLatLong(string airportFile);
    

    // Maps IATA to Latitude and Longitude.
    unordered_map<string, LatLong> airports;
};