#include "graph.h"

// EDGE CLASS CONSTRUCTOR
Graph::Edge::Edge(string startAirport, string endAirport, string airlineCode, int distance)
{
    this->startAirport = startAirport;
    this->endAirport = endAirport;
    this->airlineCode = airlineCode;
    this->weight = distance;
}

// GRAPH CLASS CONSTRUCTOR
Graph::Graph(string routesFileName, string airportFileName)
{
    // Populates airports:
    mapAirportsToLatLong(airportFileName);

    // Populates graphMap:
    mapStartAirportToEdge(routesFileName);
}

void Graph::mapStartAirportToEdge(string routeFile)
{
    // Indexes per line sepeof information, separated by commas, of OpenFlights routes dataset
    int airlineCodeIdx = 0;
    int startAirIdx = 2;
    int endAirIdx = 4;

    // Process the routes dataset line by line
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
        Edge newEdge(startAirport, endAirport, airlineCode, weight(startAirport, endAirport));
        graphEdges[startAirport].push_back(newEdge);
    }
}

double Graph::weight(string firstAirport, string secondAirport)
{
    //Calculate distance using Haversine's formula

    int r = 6371; //Earth's radius in KM

    //Convert the two airport's lattiude and longitude radians
    double firstLat = (airportsMap[firstAirport].lat) * (PI / 180);
    double firstLon = (airportsMap[firstAirport].lon) * (PI / 180);
    double secondLat = (airportsMap[secondAirport].lat) * (PI / 180);
    double secondLon = (airportsMap[secondAirport].lon) * (PI / 180);

    double distance = 2 * r * asin(sqrt(pow(sin((secondLat - firstLat) / 2), 2) + (cos(secondLat) * cos(firstLat) * pow(sin((secondLon - firstLon) / 2), 2))));
    return distance;
}

// Function maps an airport to a struct of its lattitude and longitude.
void Graph::mapAirportsToLatLong(string airportFile)
{
    // Indexes per line of information, separated by commas, of OpenFlights airport dataset
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

        string IATA = lineSects[IATAIdx]; // Extract ITIA code of the airport
        string lat = lineSects[latIdx];   // Extract lattitude of the airport
        string lon = lineSects[lonIdx];   // Extract the longitude of the airport

        // Populates the airportMap
        airportsMap[IATA].lat = stod(lat);
        airportsMap[IATA].lon = stod(lon);
    }
}

void Graph::printGraph()
{
    cout << "GRAPH" << endl;
    cout << "..................." << endl;
    for (auto it = graphEdges.begin(); it != graphEdges.end(); ++it)
    {
        cout << "Airport: " << it->first << endl;
        cout << "Incident Edges:" << endl;
        for (int i = 0; i < (it->second).size(); ++i)
        {
            cout << "Incident Airport: " << (it->second)[i].endAirport << " Airline Code: " << (it->second)[i].airlineCode << " Weight: " << (it->second)[i].weight << endl; 
        }
        cout << endl;
    }
    cout << "..................." << endl;
}

void Graph::printAirports()
{
    cout << "LIST OF AIRPORTS" << endl;
    cout << "..................." << endl;
    for (auto it = airportsMap.begin(); it != airportsMap.end(); ++it)
    {
        cout << "Airport: " << it->first << " Lattitude: " << (it->second).lat << " Longitude" << (it->second).lon << endl;
    }
    cout << "..................." << endl;
}

// //GRAPH PUBLIC FUNCTIONS
// void Graph::insertVertex(string airportCode)
// {
//     //Check if Vertex has already been added
//     if(graphMap.find(airportCode) != graphMap.end())
//     {
//         return;
//     }

//     //Insert airportCode to graphMap with empty adjacency linked list
//     list<Edge> newEdgeList;
//     graphMap.insert({airportCode, newEdgeList});
// }

// void Graph::insertEdge(string firstAirport, string secondAirport, Edge edgeToInsert)
// {
//     //**Note: Assumes no duplication of routes and assumes that firstAirport and secondAirport exists
//     graphMap[firstAirport].push_back(edgeToInsert);
//     graphMap[secondAirport].push_back(edgeToInsert);
// }
// list<Edge> Graph::incidentEdges(string airportCode)
// {
//     return graphMap[airportCode];
// }