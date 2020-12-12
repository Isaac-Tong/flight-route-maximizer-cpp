#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../flightsVizualizer.h"
#include "../cs225/PNG.h"
#include <string>

TEST_CASE("Test Graph Constructor Output", "[Graph]")
{
    /*string airportFile = "./tests/sets_to_test/airports_extended_formatted.txt";
    string routesFile = "./tests/sets_to_test/routes_dataset.txt";
    Graph newGraph(routesFile, airportFile);
    string routesFileName = "airports_extended_formatted.txt";
    string airportFileName = "routes_dataset.txt";
  
  
  
    string singleRouteDataset = "./tests/sets_to_test/single_path_dataset.txt";
    string twoAirportsDataset = "./tests/sets_to_test/two_airports_dataset.txt";
    Graph graph(singleRouteDataset, twoAirportsDataset);
    string singleRouteFileName = "single_path_dataset.txt";
    string twoAirportsFileName = "two_airports_dataset.txt";*/
  
    //auto test;
  
    string fiveRoutesDataset = "./tests/sets_to_test/dijkstra_five_routes.txt";
    string fiveAirportDataset = "./tests/sets_to_test/dijkstra_five_airports.txt";

    Graph graph(fiveRoutesDataset, fiveAirportDataset);
    
    graph.getAirportsMap();
    graph.getGraphEdges();
    
    ununordered_map<string, vector<Graph::Edge>> Graph::getGraphEdges()
    {
        return graphEdges;
    }
  
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
  
  
    ifstream output("graphtest.txt");
    string line;
    getline(output, line);
    int expectedDist = graph.weight("AAA", "EEE");
    stringstream actualDisLine(line);
    stringstream expectedDisLine;
    expectedDisLine << expectedDist;
    REQUIRE(actualDisLine.str() == expectedDisLine.str());
  
}

TEST_CASE("Finds Single Path Between Airports", "[BFS]")
{
    string airportFile = "./tests/sets_to_test/airports_extended_formatted.txt";
    string routesFile = "./tests/sets_to_test/routes_dataset.txt";
    Graph newGraph(routesFile, airportFile);
    string startingAirport = "ORD"; //Test Chicago to San Francisco
    string endingAirport = "SFO";

    //requires Unix-like operating system
    
    system("rm bfs_airports_visited.txt");
    REQUIRE(newGraph.BFS(startingAirport, endingAirport) == true);
    string path[2] = {"ORD", "SFO"};
    ifstream bfsFile;
    string line;
    int count = 0;
    //test if file has been written correctly
    bfsFile.open("bfs_airports_visited.txt");
    getline(bfsFile,line);//Skip one line that is designated for console output
    while (getline(bfsFile,line))
    {
      REQUIRE(line == path[count]);
      count++;
    }
    bfsFile.close();
}

TEST_CASE("Invalid Start Airport Code", "[dijkstra]")
{
    string singleRouteDataset = "./tests/sets_to_test/single_path_dataset.txt";
    string twoAirportsDataset = "./tests/sets_to_test/two_airports_dataset.txt";

    Graph graph(singleRouteDataset, twoAirportsDataset);

    string invalidStartCode = "ACB";

    graph.Dijkstra(invalidStartCode, "AAA");

    ifstream dijkstraOutput("DijkstraOutput.txt");
    string line;

    getline(dijkstraOutput, line);
    stringstream actualLine(line);
    REQUIRE(actualLine.str() == "Invalid starting airport code");
}
