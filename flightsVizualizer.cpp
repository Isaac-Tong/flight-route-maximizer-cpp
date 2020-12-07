#include "flightsVizualizer.h"

// CONSTRUCTOR
flightsVizualizer::flightsVizualizer(Graph graph)
{
    this->graph = graph;
    this->worldMap.readFromFile("./src/mercator.png");
}

void flightsVizualizer::drawConnection(Graph::LatLong airport1, Graph::LatLong airport2)
{

}

void flightsVizualizer::markAirport(double lat, double lon)
{
    //Height and width of the world map
    double length = 2058;

    //Calculate x and y of the airport on the worldMap
    double x = (lon + 180) * (length / 360);
    double y = (length / 2) - ((length * log(tan((PI / 4) + ((lat * (PI / 180)) / 2)))) / (2 * PI));

    cout << "x=" << x << "y=" << y;

    for(int i = -3; i < 3; ++i)
    {
        for(int j = -3; j < 3; ++j)
        {
            cs225::HSLAPixel& targetPixel = worldMap.getPixel(x + i, y + j);
            targetPixel.l = 0.5;
            targetPixel.h = 35;
            targetPixel.s = 1;
        }
    }
}

void flightsVizualizer::printProjection()
{
    unordered_map<string, Graph::LatLong> airportsMap = this->graph.getAirportsMap();

    int counter = 0;
    auto iterator = airportsMap.begin();
    while(counter < 100)
    {
        double lat = (iterator->second).lat;
        double lon = (iterator->second).lon;

        // cout << iterator->first << "Long Lat " << (iterator->second).lat << (iterator->second).lon << endl;
        cout << iterator->first; 
        markAirport(lat, lon);
        cout << "lat=" << lat << "long=" << lon << endl;
        iterator++;
        counter++;
    }

    worldMap.writeToFile("heathrow.png");
}