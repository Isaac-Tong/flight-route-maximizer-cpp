#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../flightsVizualizer.h"
#include "../cs225/PNG.h"
#include <string>
#include <iostream>

using namespace std;

TEST_CASE("Correclty Outputs Two Airports Path", "[vizualizer]") 
{
    string singleRouteDataset = "./tests/sets_to_test/single_path_dataset.txt";
    string twoAirportsDataset = "./tests/sets_to_test/two_airports_dataset.txt";

    Graph graph(singleRouteDataset,twoAirportsDataset);

    flightsVizualizer vizualizer(graph);
    vizualizer.printProjection();

    cs225::PNG actual;
    actual.readFromFile("output.png");

    cs225::PNG expected;  
    expected.readFromFile("./src/mercator.png");

    double endX = 1600.66666667;
    double startX = 1229.08333333;
    double y = 697.96;

    // Draw expected airports.
    for (int i = startX - 1; i < startX; ++i)
    {
        for (int j = y - 1; j < y; ++j)
        {
            cs225::HSLAPixel &pixel = expected.getPixel(i, j);
            pixel.l = 0.5;
            pixel.h = 300;
            pixel.s = 1;
        }
    }

    for (int i = endX - 1; i < endX; ++i)
    {
        for (int j = y - 1; j < y; ++j)
        {
            cs225::HSLAPixel &pixel = expected.getPixel(i, j);
            pixel.l = 0.5;
            pixel.h = 300;
            pixel.s = 1;
        }
    }

    // Draw expected path.
    for (int x = startX; x < endX; ++x) 
    {
        cs225::HSLAPixel &pixel = expected.getPixel(x, (int)y);
        pixel.l = 0.5;
        pixel.h = 35;
        pixel.s = 1;
    }

    expected.writeToFile("./tests/vizualizer_single_path_expected.png");

    REQUIRE(actual == expected);
}
