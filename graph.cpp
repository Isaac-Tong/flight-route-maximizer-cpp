#include "graph.h"

// EDGE CLASS CONSTRUCTOR
Graph::Edge::Edge(string startAirport, string endAirport, string airlineCode, int distance)
{
    this->startAirport = startAirport;
    this->endAirport = endAirport;
    this->airlineCode = airlineCode;
    this->weight = distance;
}

Graph::Graph()
{

}

// GRAPH CLASS CONSTRUCTOR
Graph::Graph(string routesFileName, string airportFileName)
{
    // Note that the format of the graph dataset was modified as to not have quotes and have commas only to indicate
    // a change in the field of the data (not within an airport name for example).

    // Populates airports:
    mapAirportsToLatLong(airportFileName);
    // Populates graphMap:
    mapStartAirportToEdge(routesFileName);
}

Graph::Graph(Graph& other)
{
    this->airportsMap = other.getAirportsMap();
    this->graphEdges = other.getGraphEdges();
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
    int transportTypeIdx = 3; // Transport type may not be airport.
    int IATAIdx = 0;
    int latIdx = 1;
    int lonIdx = 2;

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

        string IATA = lineSects[IATAIdx]; // Extract IATA code of the airport
        string lat = lineSects[latIdx];   // Extract lattitude of the airport
        string lon = lineSects[lonIdx];   // Extract the longitude of the airport

        //Since some IATA codes are unknown, skip airports which have unknown IATA codes.
        //Make sure the transport type is airport.
        string transportName = lineSects[transportTypeIdx];

        if (IATA.size() < 3 || transportName.substr(0, 7) != "airport")
        {
            continue;
        }
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
        for (size_t i = 0; i < (it->second).size(); ++i)
        {
            cout << "Incident Airport: " << (it->second)[i].endAirport << " Airline Code: " << (it->second)[i].airlineCode << " Weight: " << (it->second)[i].weight << endl;
        }
        cout << endl;
    }
    cout << "..................." << endl;
}

void Graph::printAirports()
{
    int counter = 1;
    cout << "LIST OF AIRPORTS" << endl;
    cout << "..................." << endl;
    for (auto it = airportsMap.begin(); it != airportsMap.end(); ++it)
    {
        cout << counter << " Airport: " << it->first << " Lattitude: " << (it->second).lat << " Longitude: " << (it->second).lon << endl;
        counter++;
    }
    cout << "..................." << endl;
}

bool Graph::BFS(string startingAirport, string destinationAirport) {
    unordered_map<string, LatLong> validAirportName = getAirportsMap();
    if (validAirportName.find(startingAirport) == validAirportName.end() || validAirportName.find(destinationAirport) == validAirportName.end()) {
        return false;
    }
    queue<string> queue;
    queue.push(startingAirport);
    unordered_map<string, int> redundantDestAirport;
    bool toPop = true;
    while (!queue.empty()) {
        toPop = true;
        for (auto it = graphEdges.begin(); it != graphEdges.end(); ++it) {
            if (it->first == queue.front()) {
                queue.pop();
                toPop = false;
                for (size_t i = 0; i < (it->second).size(); ++i) {
                    if ((it->second)[i].endAirport == destinationAirport) {
                        return true;
                    }
                    //If the destination airport does not exist in map, add to map and queue of airports that need to be visited.
                    if (redundantDestAirport.find((it->second)[i].endAirport) == redundantDestAirport.end()) {
                        queue.push((it->second)[i].endAirport); 
                        redundantDestAirport.insert(make_pair((it->second)[i].endAirport, 1));
                    } 
                }
            } 
        }
        if (toPop == true) {
            queue.pop();
        }
    }
    return false;
}


void Graph::Dijkstra(string start, string destination){
    unordered_map<string, LatLong> validAirportName = getAirportsMap();
    if (validAirportName.find(start) == validAirportName.end() || validAirportName.find(destination) == validAirportName.end()) {
        return;
    }
    //need to check if valid
    unordered_map<string, vector<Edge>> validGraphEdge = getGraphEdges();
    if (validGraphEdge.find(start) == validGraphEdge.end() || validGraphEdge.find(destination) == validGraphEdge.end()) {
        return;
    }
    if(Graph::BFS(start, destination) == false){
        return;
    }
    priority_queue<string, int> pqueue;
    queue<string> squeue;
    int weight;
    pqueue.push(start, weight);
    bool Pop = true;
    while (!pqueue.empty()) {
        Pop = true;
        for (auto it = graphEdges.begin(); it != graphEdges.end(); ++it) {
            if (it->first == pqueue.front()) {
                pqueue.pop();
                Pop = false;
                for (size_t i = 0; i < (it->second).size(); ++i) {
                    if ((it->second)[i].endAirport == destination) {
                        return;
                    }
                    if((it->second)[i].weight <= (it->first)[i].weight)){
                        pqueue.push((it->second)[i].endAirport, (it->second)[i].weight);
                    }
                }
            } 
        }
        if (Pop == true) {
            pqueue.pop();
        }
    }
    return;
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

unordered_map<string, Graph::LatLong> Graph::getAirportsMap()
{
    return airportsMap;
}

unordered_map<string, vector<Graph::Edge>> Graph::getGraphEdges()
{
    return graphEdges;
}


