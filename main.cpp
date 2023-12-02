#include <iostream>
#include "Graph.h"

using namespace std;

/***
 * 1. Create function to retrieve data from website we found
 * 2. Create Data Structure (Weighted Graph)
 *      - Dijakstra's
 *      - Bredth First Search ????
 * 3. Graphical User Interface

***/



int main() {
    Graph g;
    Star s("lucas");
    Star e("bill");
    Star a("will");
    Star b("gill");
    Star n("to");
    Star m("ll");
    Star l("lu");
    Star k("b");
    Star j("as");
    Star h("b");
    Star f("bucas");
    Star w("mill");
    g.Add(&s);
    g.Add(&e);
    g.Add(&w);
    g.Add(&f);
    g.Add(&a);
    g.Add(&b);
    g.Add(&n);
    g.Add(&m);
    g.Add(&l);
    g.Add(&k);
    g.Add(&j);


    g.PrintStarConnections();


    return 0;
}
