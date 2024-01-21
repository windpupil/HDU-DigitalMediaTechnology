#include "../DataStructure/AMGraph.h"
int main()
{
    AMGraph<int> graph;
    CreateAMGraph(graph);
    int visited[MAXSIZE]={0};
    // DFSAMGraph(graph, 0, visited);
    BFSAMGraph(graph, 0, visited);
    return 0;
}