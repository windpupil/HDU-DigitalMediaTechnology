#include "../DataStructure/AMGraph.h"
int main()
{
    AMGraph<int> graph;
    CreateAMGraph(graph);
    // PrimAMGraph(graph);
    KruskalAMGraph(graph);
    return 0;
}