#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../flightsVizualizer.h"
#include "../cs225/PNG.h"
#include <string>
#include <vector>

TEST_CASE("Test Graph Constructor Output", "[Graph]")
{
  
    string fiveRoutesDataset = "./tests/sets_to_test/dijkstra_five_routes.txt";
    string fiveAirportDataset = "./tests/sets_to_test/dijkstra_five_airports.txt";

    Graph graph(fiveRoutesDataset, fiveAirportDataset);
    
    unordered_map<string, Graph::LatLong> airportsMap = graph.getAirportsMap();
    unordered_map<string, vector<Graph::Edge>> graphEdges = graph.getGraphEdges();
  
    std::vector<int> expectedWeights;
    expectedWeights.push_back(graph.weight("AAA", "BBB"));
    expectedWeights.push_back(graph.weight("AAA", "DDD"));
    expectedWeights.push_back(graph.weight("DDD", "BBB"));
    expectedWeights.push_back(graph.weight("DDD", "EEE"));
    expectedWeights.push_back(graph.weight("BBB", "EEE"));
    expectedWeights.push_back(graph.weight("BBB", "CCC"));
    expectedWeights.push_back(graph.weight("EEE", "CCC"));
    int counter = 0;
    for (auto it = graphEdges.begin(); it != graphEdges.end(); ++it)
    {
        for (size_t i = 0; i < (it->second).size(); ++i)
        {
   REQUIRE((it->second)[i].weight == expectedWeights[counter]);
   counter++;
        }
    }
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

TEST_CASE("Invalid Starting Airport Code", "[dijkstra]")
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
