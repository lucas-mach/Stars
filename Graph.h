#include <map>
#include <vector>
#include <string>
#include <tuple>
#include <iostream>
#include <math.h>
using namespace std;

struct Star {
    string name;
    float x;
    float y;
    float z;
    Star(string name, float x, float y, float z) { // Need to add coordinate system to calculate distances between stars
        this->name = name;
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

class Graph {
    map<Star*, map<Star*, double>> adjList; //Maps, a star to its other stars, with the weight(distance)
    map<string, Star*> m;   //maps name of star to corresponding object, created to easily retrieve object data with specified name
    vector<Star*> randomFind;
    int maxConnections = 5; // max amount of star connections 1 star can have
    int count = 0;
    double CalcDistance(Star* first, Star* second) {   // Calculate distance between two stars
        return sqrt(pow((second->x - first->x), 2) + pow((second->y - first->y), 2) + pow((second->z - first->z), 2));
    }

    void RemoveFurthestStar(Star* star, Star* newStar) {    // Erase the Star furthest of the 5 connections if passed in star is smaller
        auto temp = adjList[star].begin();

        for (auto iter = adjList[star].begin(); iter != adjList[star].end(); iter++) {
            if (iter->second > temp->second) {
                temp = iter;
            }
        }
        if (CalcDistance(star, newStar) < adjList[star][temp->first]) { //Replace star
            adjList[star].erase(temp->first);
            adjList[star][newStar] = CalcDistance(star, newStar);
        }
    }

    
    Star* BFS(Star* start, Star* search) {
        // implementing a queue for BFS
        queue<Star*> q;

        // use a set to track visited star
        set<Star*> visitedStar;
        // start with specified star
        q.push(start);
        visitedStar.insert(start);

        while (!q.empty()) {
            Star *currStar = q.front();
            q.pop();

            cout << currStar->name << endl;
            // check is the current star is one of the closest
            if (currStar == search) {
                cout << search->name << endl;
                return currStar;
            }
            // check the adjacent stars
            for (auto it: adjList[currStar]) {
                Star *adjacentStar = it.first;

                // if the adjacent list isn't visitied add it to the queue
                if (visitedStar.find(adjacentStar) == visitedStar.end()) {
                    q.push(adjacentStar);
                    visitedStar.insert(adjacentStar);
                }


            }
        }
        return nullptr;
    }

    Star* HelperDFS(Star* currStar, Star* search, set<Star*> &s) {
        if (s.find(currStar) != s.end()) {  //Star is already in Set
            return nullptr;
        }
        for (auto it = adjList[currStar].begin(); it != adjList[currStar].end(); it++) {
            if (it->first == search) { return currStar;}    //If star found return star
            else {  //Else call Recursive function with next
                s.insert(it->first);
                HelperDFS(it->first, search, s);
            }
        }
    }

    Star* DFS(Star* start, Star* search) {
        set<Star*> set = {};
        return HelperDFS(start, search , set);

    }


public:
    ~Graph() {
        for (auto &pair : adjList) {
            delete pair.first;
        }
    }
    Star* SearchRandomStar() {
        int randint = rand() % count;
        Star* randStar = randomFind[randint];
        auto iter = adjList.begin();
        Star* d = DFS(iter->first, randStar);
        Star* b = BFS(iter->first, randStar);
        cout << randStar->name << " " << d->name << " " << b->name << endl;
        if (d == b) {return d;}
    }

    void AddStar(Star* s) {   // add Star to every other star if the other star has less than "MaxConnection" star connections
                        // if has more than "maxConnection", find the star with the largest distance and replace
        adjList[s] = {};
        count++;
        randomFind.push_back(s);
        // Iterate through all stars
        for (auto iter = adjList.begin(); iter != adjList.end(); iter++) {
            //Connection of iterated Star to new star
            if (iter->second.size() < maxConnections and s->name != iter->first->name) {
                adjList[iter->first][s] = CalcDistance(iter->first, s);
            }

            else if (iter->second.size() >= maxConnections and s->name != iter->first->name) {
                RemoveFurthestStar(iter->first, s);
            }

            //Connection of new star to iterated star

            if (adjList[s].size() < maxConnections and s->name != iter->first->name) {
                adjList[s][iter->first] = CalcDistance(s, iter->first);
            }

            else if (adjList[s].size() >= maxConnections and s->name != iter->first->name){
                RemoveFurthestStar(s, iter->first);
            }
        }

        //if (m.find(s->name) == m.end()) {    // Is not in map
        //    m[s->name] = s;
        //}
    }


    void PrintStarConnections() {
        for (auto iter = adjList.begin(); iter != adjList.end(); iter++) {

            for (auto it = adjList[iter->first].begin(); it != adjList[iter->first].end(); it++) {
                cout << it->first->name << " "<< it->second <<endl;
            }
            cout <<"^ is for star: " <<iter->first->name <<"-----------------" << endl;
        }
    }


};





