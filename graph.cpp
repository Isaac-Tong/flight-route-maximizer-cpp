#include "graph.h"
#include <fstream> 

Graph::Graph(string fileName)
{
    translateDataToGraph(fileName);
}

void Graph::translateDataToGraph(string fileName)
{
    //Key: String of the airport
    //Value: Struct for the longitude and latitude of the airport

    //Key: string of the starting airport
    //Value: Vector of structs of the desintation airports along with data of the airline and equipment. 

    // Vector of edges of structs with start airport (IATA), end airport (IATA), alrine code

    ifstream file(fileName);
    string fileLine;

    while (getline(file, fileLine)) {
        // line contains the current line

    }
}