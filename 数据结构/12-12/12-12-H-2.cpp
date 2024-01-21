#include "../DataStructure/ADJList.h"
int main()
{
    AdjListHead *adjListHead = CreateAdjList();
    int visited[MAXSIZE] = {0};
    // DFSAdjList(adjListHead, 0, visited);
    BFSAdjList(adjListHead, 0, visited);
    return 0;
}