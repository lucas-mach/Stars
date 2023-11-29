#include <map>
#include <vector>
#include <string>
#include <tuple>
using namespace std;

class Star {
public:
    string name;
public:
    Star(string name) {
        this->name = name;
    }
};


class Graph {
public:
    map<Star*, map<Star*, int>> adjList; //Maps, a star to its other stars, with the weight(distance)
    map<string, Star*> m;   //maps name of star to corresponding object

public:
    void Add(Star* from, Star* to) {   // Add max 5 connections per node
        this->adjList[from][to] = 5;

        if (m.find(from->name) == m.end()) {    // Is not in Map
            m[from->name] = from;
        }
    }






};





