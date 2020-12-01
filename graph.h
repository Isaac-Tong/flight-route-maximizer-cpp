#include <string>
using namespace std;
class Graph
{
public:
    Graph(string fileName);
    
private:
    void translateDataToGraph(string fileName);
};