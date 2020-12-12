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

Graph::Graph(Graph &other)
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
    if (!routeFileIF.is_open()) {
        cout << "Unable to open route file" << endl;
        return;
    }
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
        cout << "Starting Airport: " << it->first << endl;
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

bool Graph::BFS(string startingAirport, string destinationAirport)
{
    unordered_map<string, LatLong> validAirportName = getAirportsMap();
    if (validAirportName.find(startingAirport) == validAirportName.end() || validAirportName.find(destinationAirport) == validAirportName.end())
    {
        return false;
    }
    ofstream bfsAirportsVisited;
    bfsAirportsVisited.open("bfs_airports_visited.txt");
    bfsAirportsVisited << "Start of BFS between " << startingAirport << " and " << destinationAirport << "\n";
    queue<string> queue;
    queue.push(startingAirport);
    unordered_map<string, int> redundantDestAirport;
    bool toPop = true;
    while (!queue.empty())
    {
        toPop = true;
        for (auto it = graphEdges.begin(); it != graphEdges.end(); ++it)
        {
            if (it->first == queue.front())
            {
                bfsAirportsVisited << queue.front() << "\n";
                queue.pop();
                toPop = false;
                for (size_t i = 0; i < (it->second).size(); ++i)
                {
                    if ((it->second)[i].endAirport == destinationAirport)
                    {
                        bfsAirportsVisited << destinationAirport << "\n";
                        return true;
                    }
                    //If the destination airport does not exist in map, add to map and queue of airports that need to be visited.
                    if (redundantDestAirport.find((it->second)[i].endAirport) == redundantDestAirport.end())
                    {
                        queue.push((it->second)[i].endAirport);
                        redundantDestAirport.insert(make_pair((it->second)[i].endAirport, 1));
                    }
                }
            }
        }
        if (toPop == true)
        {
            bfsAirportsVisited << queue.front() << "\n";
            queue.pop();
        }
    }
    return false;
}
void Graph::Dijkstra(string startAirport, string targetAirport)
{
    // Check if startAirport is a vaid airport code
    if (graphEdges.find(startAirport) == graphEdges.end())
    {

        ofstream outputFile;
        outputFile.open("DijkstraOutput.txt");
        outputFile << "Invalid starting airport code" << endl;
        return;
    }

    //Check if there is a route to the airport
    if(!BFS(startAirport, targetAirport))
    {
        ofstream outputFile;
        outputFile.open("DijkstraOutput.txt");
        outputFile << "No path exists from starting airport to target airport" << endl;
        return;
    }
    ofstream outputFile;
    outputFile.open("DijkstraOutput.txt");

    unordered_map<string, pair<int, string>> pathData = DijkstraHelper(startAirport);
    int distance = pathData[targetAirport].first;
    outputFile << "SHORTEST DISTANCE: " << distance << endl;
    
    pair<int, string> currentAirport = pathData[targetAirport];
    vector<string> reverseVector;
    reverseVector.push_back(targetAirport);
    outputFile << "SHORTEST PATH: ";
    while(currentAirport.second != "START")
    {
        reverseVector.insert(reverseVector.begin(), currentAirport.second);
        currentAirport = pathData[currentAirport.second];
    }
    for(size_t i = 0; i < reverseVector.size() - 1; i++)
    {
        outputFile << reverseVector[i] << "-";
    }

    outputFile << reverseVector[reverseVector.size() - 1] <<   endl;

    outputFile << endl;
    outputFile << "DIJKSTRA OUTPUT" << endl;
    for (auto it = pathData.begin(); it != pathData.end(); it++)
    {
        outputFile << "Airport: " << it->first << " Distance: " << it->second.first << " Previous Airport: " << it->second.second << endl;
    }
}

unordered_map<string, pair<int, string>> Graph::DijkstraHelper(string startAirport)
{
    //Initialize hasVisited hash map with all airports and mark as unvisited
    unordered_map<string, bool> hasVisited;
    //Initialize path data with all airports and pair with shortest distance as infinite and empty previous vertex
    unordered_map<string, pair<int, string>> pathData;
    for (auto it = airportsMap.begin(); it != airportsMap.end(); it++)
    {
        hasVisited[it->first] = false;
        pathData[it->first] = {numeric_limits<int>::max(), "000"};
    }

    //Initialize a priority queue
    // Pair: First = Distance from startAirport. Second = airportCode
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> priorityQueue;

    //Insert startAirport into priorityQueue and set distance from startAirport = 0;
    priorityQueue.push({0, startAirport});

    //Set distance and previous vertex of starting aiport
    pathData[startAirport] = {0, "START"};

    while (!priorityQueue.empty())
    {

        // Get the top airport of the priority queue
        pair<int, string> topAirport = priorityQueue.top();
        // Pop the top airport
        priorityQueue.pop();
        // Mark the popped airport as already visited
        hasVisited[topAirport.second] = true;
        
        // Go through topAirport's adjacent airport
        vector<Edge> adjacentAirports = graphEdges[topAirport.second];
        for (auto it = adjacentAirports.begin(); it != adjacentAirports.end(); it++)
        {
            //If have already visited the node before
            if (hasVisited[it->endAirport])
            {
                continue;
            }

            //Calculate potential best weight
            int potentialWeight = topAirport.first + it->weight;

            if (potentialWeight < pathData[it->endAirport].first)
            {
                //Update pathData map
                pathData[it->endAirport].first = potentialWeight;
                pathData[it->endAirport].second = topAirport.second;
            }

            //Add current adjacentAirport to priority queue
            priorityQueue.push({pathData[it->endAirport].first, it->endAirport});
        }
    }
    return pathData;
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
