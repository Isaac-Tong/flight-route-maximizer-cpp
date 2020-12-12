#include "../cs225/catch/catch.hpp"
#include "../graph.h"

TEST_CASE("Find path between two airports", "[BFS]")
{
    string airportFile = "./tests/sets_to_test/airports_extended_formatted.txt";
    string routesFile = "./tests/sets_to_test/routes_dataset.txt";
    Graph newGraph(routesFile, airportFile);
    string startingAirport = "CMI"; //Test Willard to San Jose
    string endingAirport = "SJC";

    //requires Unix-like operating system
    
    system("rm bfs_airports_visited.txt");
    REQUIRE(newGraph.BFS(startingAirport, endingAirport) == true);
    string path[3] = {"CMI", "DFW", "SJC"};
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

TEST_CASE("Find path between airports which are completely disconnected", "[BFS]")
{
    //files containing a dummy airport named XYZ with no connections
    string airportFile = "./tests/sets_to_test/airports_modified.txt";
    string routesFile = "./tests/sets_to_test/routes_dataset_modified.txt";
    Graph newGraph(routesFile, airportFile);
    string startingAirport = "XYZ"; //Test a randomly generated airport with no connections to Willard
    string endingAirport = "CMI";

    //requires Unix-like operating system
    system("rm bfs_airports_visited.txt");
    REQUIRE(newGraph.BFS(startingAirport, endingAirport) == false);
    
}
