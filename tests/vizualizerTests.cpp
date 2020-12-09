#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../flightsVizualizer.h"
#include "../cs225/PNG.h"
#include <string>
#include <iostream>

using namespace std;

//HELPER FUNCTION TO CONVERT LATTITUDE AND LONGITUDE TO COORDINATES
double translateXCoordinate(double lon)
{
    double length = 2058;
    return (lon + 180) * (length / 360);
}
double translateYCoordinate(double lat)
{
    double length = 2058;
    return (length / 2) - ((length * log(tan((PI / 4) + ((lat * (PI / 180)) / 2)))) / (2 * PI));
}
//HELPER FUNCTION TO DRAW AIRPORT
void markAirport(double x, double y, cs225::PNG &expected)
{

    for (int i = -1; i < 1; ++i)
    {
        for (int j = -1; j < 1; ++j)
        {
            cs225::HSLAPixel &targetPixel = expected.getPixel(x + i, y + j);
            targetPixel.l = 0.5;
            targetPixel.h = 300;
            targetPixel.s = 1;
        }
    }
}

//HELPER FUNCTION TO PRINT CONNECTIONS
void drawConnection(double x1, double y1, double x2, double y2, cs225::PNG &output)
{
    if (x1 > x2)
    {
        double xTemp = x1;
        double yTemp = y1;

        x1 = x2;
        y1 = y2;

        x2 = xTemp;
        y2 = yTemp;
    }
    //Calculate slope
    double slope = (y2 - y1) / (x2 - x1);
    if (x2 - x1 < 1)
    {
        for (int i = min(y1, y2); i < max(y1, y2); ++i)
        {
            cs225::HSLAPixel &targetPixel = output.getPixel(x1, i);
            targetPixel.l = 0.5;
            targetPixel.h = 35;
            targetPixel.s = 1;
        }
    }
    else
    {
        for (int i = x1; i < x2; i++)
        {
            double yCoordinate = (slope * (i - x1)) + y1;
            cs225::HSLAPixel &targetPixel = output.getPixel(i, (int)yCoordinate);
            targetPixel.l = 0.5;
            targetPixel.h = 35;
            targetPixel.s = 1;
        }
    }
}

TEST_CASE("Correctly Outputs Two Airports Path", "[vizualizer]")
{
    string singleRouteDataset = "./tests/sets_to_test/single_path_dataset.txt";
    string twoAirportsDataset = "./tests/sets_to_test/two_airports_dataset.txt";

    Graph graph(singleRouteDataset, twoAirportsDataset);

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

TEST_CASE("Correctly Outputs 5 Routes From Heathrow Airport", "[vizualizer]")
{
    string routeFile = "./tests/sets_to_test/five_connections_from_heathrow_routes.txt";
    string airportFile = "./tests/sets_to_test/five_connections_from_heathrow_airports.txt";

    Graph graph(routeFile, airportFile);

    flightsVizualizer vizualizer(graph);
    vizualizer.printProjection();

    cs225::PNG actual;
    actual.readFromFile("output.png");

    cs225::PNG expected;
    expected.readFromFile("./src/mercator.png");

    //Longitude and Lattiude of the airports
    double LHRlat = 51.4706;
    double LHRlon = -0.461941;

    double DFWlat = 32.896801;
    double DFWlon = -97.038002;

    double YVRlat = 49.19390106;
    double YVRlon = -123.1839981;

    double AMSlat = 52.308601;
    double AMSlon = 4.76389;

    double PVGlat = 31.14340019;
    double PVGlon = 121.8050003;

    double ORDlat = 41.9786;
    double ORDlon = -87.9048;

    //DRAW AIRPORTS
    markAirport(translateXCoordinate(LHRlon), translateYCoordinate(LHRlat), expected);
    markAirport(translateXCoordinate(DFWlon), translateYCoordinate(DFWlat), expected);
    markAirport(translateXCoordinate(YVRlon), translateYCoordinate(YVRlat), expected);
    markAirport(translateXCoordinate(AMSlon), translateYCoordinate(AMSlat), expected);
    markAirport(translateXCoordinate(PVGlon), translateYCoordinate(PVGlat), expected);
    markAirport(translateXCoordinate(ORDlon), translateYCoordinate(ORDlat), expected);

    //LHR to DFW
    drawConnection(translateXCoordinate(LHRlon), translateYCoordinate(LHRlat), translateXCoordinate(DFWlon), translateYCoordinate(DFWlat), expected);

    //LHR to YVR
    drawConnection(translateXCoordinate(LHRlon), translateYCoordinate(LHRlat), translateXCoordinate(YVRlon), translateYCoordinate(YVRlat), expected);

    //LHR to AMS
    drawConnection(translateXCoordinate(LHRlon), translateYCoordinate(LHRlat), translateXCoordinate(AMSlon), translateYCoordinate(AMSlat), expected);

    //LHR to PVG
    drawConnection(translateXCoordinate(LHRlon), translateYCoordinate(LHRlat), translateXCoordinate(PVGlon), translateYCoordinate(PVGlat), expected);

    //LHR to ORD
    drawConnection(translateXCoordinate(LHRlon), translateYCoordinate(LHRlat), translateXCoordinate(ORDlon), translateYCoordinate(ORDlat), expected);

    expected.writeToFile("./tests/vizualizer_heathrow_expected.png");

    REQUIRE(actual == expected);
}

TEST_CASE("Correctly Outputs Vertical Alignment of Airports", "[vizualizer]")
{
    string routeFile = "./tests/sets_to_test/vertical_alignment_routes.txt";
    string airportFile = "./tests/sets_to_test/vertical_alignment_airports.txt";

    Graph graph(routeFile, airportFile);

    flightsVizualizer vizualizer(graph);
    vizualizer.printProjection();

    cs225::PNG actual;
    actual.readFromFile("output.png");

    cs225::PNG expected;
    expected.readFromFile("./src/mercator.png");

    //Longitude and Lattiude of the airports
    double DENlat = 50.43190002;
    double DENlon = -104.6660004;

    double YQRlat = 39.86169815;
    double YQRlon = -104.6729965;

    //Draw the airport
    markAirport(translateXCoordinate(DENlon), translateYCoordinate(DENlat), expected);
    markAirport(translateXCoordinate(YQRlon), translateYCoordinate(YQRlat), expected);

    //Draw the vertical connection line

    for (double i = translateYCoordinate(DENlat); i < translateYCoordinate(YQRlat); ++i)
    {
        cs225::HSLAPixel &targetPixel = expected.getPixel(translateXCoordinate(DENlon), i);
        targetPixel.l = 0.5;
        targetPixel.h = 35;
        targetPixel.s = 1;
    }

    expected.writeToFile("./tests/vizualizer_heathrow_expected.png");

    REQUIRE(actual == expected);
}