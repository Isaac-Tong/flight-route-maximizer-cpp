#include "graph.h"

//GRAPH PUBLIC FUNCTIONS
void Graph::insertVertex(string airportCode)
{
    //Check if Vertex has already been added
    if(graphMap.find(airportCode) != graphMap.end())
    {
        return;
    }

    //Insert airportCode to graphMap with empty adjacency linked list
    list<Edge> newEdgeList;
    graphMap.insert({airportCode, newEdgeList});
}

void Graph::insertEdge(string firstAirport, string secondAirport, Edge edgeToInsert)
{
    //**Note: Assumes no duplication of routes and assumes that firstAirport and secondAirport exists
    graphMap[firstAirport].push_back(edgeToInsert);
    graphMap[secondAirport].push_back(edgeToInsert);
}
list<Edge> Graph::incidentEdges(string airportCode)
{
    return graphMap[airportCode];
}



Graph::Edge::Edge(string startAirport, string endAirport, string airlineCode)
{
    this->startAirport = startAirport;
    this->endAirport = endAirport;
    this->airlineCode = airlineCode;
}

//GRAPH CLASS CONSTRUCTOR
//Parameters:
//1. String of the routes text file name
//2. String of the airport text file name
Graph::Graph(string routesFileName, string airportFileName)
{
    translateDataToGraph(routesFileName, airportFileName);
}

//HELPER FUNCTION FOR CONSTRUCTOR TO CONVERT THE ROUTES AND AIRPORT FILES TO A GRAPH
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

void Graph::mapStartAirportToEdge(string routeFile, unordered_map<string, vector<Edge>> &startAirportToEdge)
{
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

        while (std::getline(lineSS, lineSect, ','))
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

void Graph::mapAirportsToLatLong(string airportFile)
{
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

        while (std::getline(lineSS, lineSect, ','))
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