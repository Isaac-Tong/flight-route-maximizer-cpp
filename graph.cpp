#include "graph.h"

Graph::Edge::Edge(string startAirport, string endAirport, string airlineCode) {
    this->startAirport = startAirport;
    this->endAirport = endAirport;
    this->airlineCode = airlineCode;
}

Graph::Graph(string fileName, string airportFile)
{
    translateDataToGraph(fileName, airportFile);
}

void Graph::translateDataToGraph(string routeFile, string airportFile)
{ 
    // Populates startAirportToEdge:    
    // Key: string of the starting airport
    // Value: Vector of Edge (All nodes outgoing from the destination) 
    unordered_map<string, vector<Edge>> startAirportToEdge;
    mapStartAirportToEdge(routeFile, startAirportToEdge);

    // Populates airports:
    // Key: String of the airport
    // Value: Struct for the longitude and latitude of the airport
    mapAirportsToLatLong(airportFile);

    // Vector of edges of structs with start airport (IATA), end airport (IATA), alrine code
}


void Graph::mapStartAirportToEdge(string routeFile, unordered_map<string, vector<Edge>>& startAirportToEdge) {
    // From routes data
    int airlineCodeIdx = 0;
    int startAirIdx = 2;
    int endAirIdx = 4;

    ifstream routeFileIF(routeFile);
    string routeFileLine;
    while (getline(routeFileIF, routeFileLine)) 
    {
        stringstream lineSS(routeFileLine);
        string lineSect;
        // Split the line by splitting "," into parts with related information.
        vector<string> lineSects;  

        while(std::getline(lineSS, lineSect, ','))
        {
            lineSects.push_back(lineSect);
        }
        
        // Populate startAirportToDests.
        string startAirport = lineSects[startAirIdx];
        string endAirport = lineSects[endAirIdx];
        string airlineCode = lineSects[airlineCodeIdx];
        Edge edge(startAirport, endAirport, airlineCode);

        startAirportToEdge[startAirport].push_back(edge);
    }
}

void Graph::mapAirportsToLatLong(string airportFile) {
    // From airport data
    int IATAIdx = 4;
    int latIdx = 6;
    int lonIdx = 7;

    ifstream airportFileIF(airportFile);
    string airportFileLine;
    while (getline(airportFileIF, airportFileLine)) 
    {
        stringstream lineSS(airportFileLine);
        string lineSect;
        // Split the line by , into parts with related information.
        vector<string> lineSects;  

        while(std::getline(lineSS, lineSect, ','))
        {
            lineSects.push_back(lineSect);
        }

        // populates airports unordered_map.
        string IATA = lineSects[IATAIdx];
        string lat = lineSects[latIdx];
        string lon = lineSects[lonIdx];

        airports[IATA].lat = stod(lat);
        airports[IATA].lon = stod(lon);
    }
}