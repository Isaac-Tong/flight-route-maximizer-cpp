#include "../cs225/catch/catch.hpp"
#include "../graph.h"

TEST_CASE("Finds Shortest Path Between Airports: Small", "[dijkstra]")
{
    string singleRouteDataset = "./tests/sets_to_test/single_path_dataset.txt";
    string twoAirportsDataset = "./tests/sets_to_test/two_airports_dataset.txt";

    Graph graph(singleRouteDataset, twoAirportsDataset);

    graph.Dijkstra("AAA", "BBB");

    int expectedShortestDistance = graph.weight("AAA", "BBB");

    ifstream dijkstraOutput("DijkstraOutput.txt");
    string line;
    getline(dijkstraOutput, line);
    stringstream actualDisLine(line);
    stringstream expectedDisLine;
    expectedDisLine << "SHORTEST DISTANCE: " << expectedShortestDistance;
    REQUIRE(actualDisLine.str() == expectedDisLine.str());

    getline(dijkstraOutput, line);
    stringstream actualPathLine(line);
    REQUIRE(actualPathLine.str() == "SHORTEST PATH: AAA-BBB");

    getline(dijkstraOutput, line);
    getline(dijkstraOutput, line);
    getline(dijkstraOutput, line);
    stringstream actualMove1Line(line);
    REQUIRE(actualMove1Line.str() == "Airport: AAA Distance: 0 Previous Airport: START");

    getline(dijkstraOutput, line);
    stringstream actualMove2Line(line);
    REQUIRE(actualMove2Line.str() ==  "Airport: BBB Distance: 4493 Previous Airport: AAA");
    
}

TEST_CASE("Finds Shortest Path Between Airports: Medium", "[dijkstra]")
{
    string fiveRoutesDataset = "./tests/sets_to_test/dijkstra_five_routes.txt";
    string fiveAirportDataset = "./tests/sets_to_test/dijkstra_five_airports.txt";

    Graph graph(fiveRoutesDataset, fiveAirportDataset);

    graph.Dijkstra("AAA", "EEE");

    int expectedShortestDistance = 0;
    expectedShortestDistance += graph.weight("AAA", "DDD");
    expectedShortestDistance += graph.weight("DDD", "EEE");

    ifstream dijkstraOutput("DijkstraOutput.txt");
    string line;
    getline(dijkstraOutput, line);
    stringstream actualDisLine(line);
    stringstream expectedDisLine;
    expectedDisLine << "SHORTEST DISTANCE: " << expectedShortestDistance;
    REQUIRE(actualDisLine.str() == expectedDisLine.str());

    getline(dijkstraOutput, line);
    stringstream actualPathLine(line);
    REQUIRE(actualPathLine.str() == "SHORTEST PATH: AAA-DDD-EEE");
}

TEST_CASE("Invalid Start Airport Code", "[dijkstra]")
{
    string singleRouteDataset = "./tests/sets_to_test/single_path_dataset.txt";
    string twoAirportsDataset = "./tests/sets_to_test/two_airports_dataset.txt";

    Graph graph(singleRouteDataset, twoAirportsDataset);

    string invalidStartCode = "BCB";

    graph.Dijkstra(invalidStartCode, "BBB");

    ifstream dijkstraOutput("DijkstraOutput.txt");
    string line;

    getline(dijkstraOutput, line);
    stringstream actualLine(line);
    REQUIRE(actualLine.str() == "Invalid starting airport code");
}

TEST_CASE("Invalid End Airport Code Leads to No Path", "[dijkstra]")
{
    string singleRouteDataset = "./tests/sets_to_test/single_path_dataset.txt";
    string twoAirportsDataset = "./tests/sets_to_test/two_airports_dataset.txt";

    Graph graph(singleRouteDataset, twoAirportsDataset);

    string invalidEndCode = "ABC";

    graph.Dijkstra("AAA", invalidEndCode);

    ifstream dijkstraOutput("DijkstraOutput.txt");
    string line;

    getline(dijkstraOutput, line);
    stringstream actualLine(line);
    REQUIRE(actualLine.str() == "No path exists from starting airport to target airport");
}

TEST_CASE("No path exists between start and an existing target airport", "[dijkstra]")
{
    string noPathDataset = "./tests/sets_to_test/dijkstra_no_shortest_path_routes.txt";
    string noPathAirplaneDataset = "./tests/sets_to_test/dijkstra_no_path_airports.txt";

    Graph graph(noPathDataset, noPathAirplaneDataset);

    // There should be no path between BBB and AAA.
    graph.Dijkstra("AAA", "DDD");

    ifstream dijkstraOutput("DijkstraOutput.txt");
    string line;

    getline(dijkstraOutput, line);
    stringstream actualLine(line);
    REQUIRE(actualLine.str() == "No path exists from starting airport to target airport");
}
