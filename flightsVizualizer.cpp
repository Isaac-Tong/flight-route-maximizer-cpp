#include "flightsVizualizer.h"

void flightsVizualizer::drawAirportsOnMap(Graph flightRoutes) 
{

}

void flightsVizualizer::printProjection()
{
    //HEATHROW AIPORT LONGITUDE AND LATTITUDE TEST
    double lat = 51.4700;
    double lon = -0.4543;

    //Height and width of the world map
    double height = 2056;
    double width = 2056;

    double x = (lon + 180) * (width / 360);
    double y = (height / 2) - ((width * log(tan((PI / 4) + ((lat * (PI / 180)) / 2)))) / (2 * PI));

    //Create a PNG image based on src/worldmap.png
    cs225::PNG worldMap;
    worldMap.readFromFile("./src/mercator.png");

    for (int i = 0; i < (int)worldMap.height(); ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            cs225::HSLAPixel &heathrowPixel = worldMap.getPixel(x + j, i);
            heathrowPixel.l = 0;
        }
    }

    for (int i = 0; i < (int)worldMap.width(); ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            cs225::HSLAPixel &heathrowPixel = worldMap.getPixel(i, y + j);
            heathrowPixel.l = 0;
        }
    }

    cout << x << " y " << y << endl;

    //Test output
    worldMap.writeToFile("heathrow.png");
}