#include <string>
#include <unordered_map> 

using namespace std;
class Graph 
{

public:
    Graph(string fileName);
    
private:
    class Edges 
    {
        string startAirport;
        string endAirport;
        string airlineCode;
    };

    struct LatLong 
    {
        double lat; // latitude
        double lon; // longitude
    };

    void translateDataToGraph(string fileName);

    unordered_map<string, LatLong> airports;
};