#include <iostream>
#include "Graph.h"

using namespace std;

/***
 * 1. Create function to retrieve data from website we found
 * 2. Create Data Structure (Weighted Graph)
 *      - Dijakstra's
 *      - Depth First Search ????
 * 3. Graphical User Interface

***/

int main() {
    Graph g;
    Star s("lucas");
    Star e("bill");
    g.Add(&s, &e);
    cout << g.adjList[&s][&e] << endl;

    return 0;
}
