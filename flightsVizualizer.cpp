#include "flightsVizualizer.h"

// CONSTRUCTOR
flightsVizualizer::flightsVizualizer(Graph graph)
{
    this->graph = graph;
    this->worldMap.readFromFile("./src/mercator.png");
}

void flightsVizualizer::drawConnection(double x1, double y1, double x2, double y2, string airportS, string airportE)
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
            cs225::HSLAPixel &targetPixel = worldMap.getPixel(x1, i);
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
            cs225::HSLAPixel &targetPixel = worldMap.getPixel(i, (int)yCoordinate);
            targetPixel.l = 0.5;
            targetPixel.h = 35;
            targetPixel.s = 1;

            // if (i > 2057 || yCoordinate > 2057)
            // {
            //     cout << " x1 "<< x1 << " y1 " << y1 << " x2 " << x2 << "y2" << y2 << airportS << airportE << endl;
            //     continue;
            // }
        }
    }
}

void flightsVizualizer::markAirport(double lat, double lon)
{
    double x = translateXCoordinate(lon);
    double y = translateYCoordinate(lat);

    for (int i = -1; i < 1; ++i)
    {
        for (int j = -1; j < 1; ++j)
        {
            cs225::HSLAPixel &targetPixel = worldMap.getPixel(x + i, y + j);
            targetPixel.l = 0.5;
            targetPixel.h = 300;
            targetPixel.s = 1;
        }
    }
}
double flightsVizualizer::translateXCoordinate(double lon)
{
    double length = 2058;
    return (lon + 180) * (length / 360);
}
double flightsVizualizer::translateYCoordinate(double lat)
{
        double length = 2058;
        return (length / 2) - ((length * log(tan((PI / 4) + ((lat * (PI / 180)) / 2)))) / (2 * PI));
    
}

void flightsVizualizer::printProjection()
{
    //Fetch edgeMap and airportsMap from graph structure
    unordered_map<string, Graph::LatLong> airportsMap = this->graph.getAirportsMap();
    unordered_map<string, vector<Graph::Edge>> edgesMap = this->graph.getGraphEdges();

    unordered_map<string, bool> hasPrinted;

    auto iterator = edgesMap.begin();
    while (iterator != edgesMap.end())
    {
        //Print airport
        string airport = iterator->first;
        double latStart = airportsMap[airport].lat;
        double lonStart = airportsMap[airport].lon;

        //Check if airport has already been printed
        if (hasPrinted.find(airport) == hasPrinted.end())
        {
            //If airport has NOT been printed, print the airport
            markAirport(latStart, lonStart);

            //Mark airport as already printed
            hasPrinted[airport] = true;
        }

        //Draw connections to adjacent airports
        vector<Graph::Edge> adjacentAirports = edgesMap[airport];
        for (size_t i = 0; i < adjacentAirports.size(); ++i)
        {
            double latEnd = airportsMap[adjacentAirports[i].endAirport].lat;
            double lonEnd = airportsMap[adjacentAirports[i].endAirport].lon;
            //Check if airport has already been printed
            if (hasPrinted.find(adjacentAirports[i].endAirport) == hasPrinted.end())
            {
                //If airports has NOT been printed, print the airport
                markAirport(latEnd, lonEnd);

                //Mark airport as already printed
                hasPrinted[adjacentAirports[i].endAirport] = true;
            }

            drawConnection(translateXCoordinate(lonStart), translateYCoordinate(latStart), translateXCoordinate(lonEnd), translateYCoordinate(latEnd), airport, adjacentAirports[i].endAirport);
        }
        iterator++;
    }

    worldMap.writeToFile("output.png");
}