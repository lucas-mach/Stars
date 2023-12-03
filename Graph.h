#include <map>
#include <vector>
#include <string>
#include <tuple>
#include <iostream>
#include <math.h>
#include <set>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <chrono>
using namespace std;

struct Star {
    int name;
    string constellation;
    double distFromSun;
    double x, y, z;
    double colorIndex;
    double radialVelocity;
    double vx, vy, vz;


    Star(int name, string constellation, double distFromSun, double x, double y, double z,
         double colorIndex, double radialVelocity, double vx, double vy, double vz) { // Need to add coordinate system to calculate distances between stars
        this->name = name;
        this->constellation = constellation;
        this->distFromSun = distFromSun;
        this->x = x;
        this->y = y;
        this->z = z;
        this->colorIndex = colorIndex;
        this->radialVelocity = radialVelocity;
        this->vx = vx;
        this->vy = vy;
        this->vz = vz;
    }
};

class Graph {
    map<Star*, map<Star*, double>> adjList; // maps, a star to its other stars, with the weight (distance)
    map<string, Star*> m;   // maps name of star to corresponding object, created to easily retrieve object data with specified name
    map<Star*,double> maxDistance;
    vector<Star*> randomFind;
    int maxConnections = 5; // max amount of star connections 1 star can have
    int count = 0;
    double DFStime;
    double BFStime;

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

    
    Star* BFS(Star* s, Star* search) {
        // implementing a queue for BFS
        queue<Star*> q;
        auto iter = adjList.begin();
        // use a set to track visited star
        set<Star*> visitedStar;
        set<Star*> v;
        v.insert(iter->first);
        // start with specified star
        q.push(iter->first);
        visitedStar.insert(iter->first);
        bool run = true;
        while (run) {
            while (!q.empty()) {
                Star *currStar = q.front();
                q.pop();

                //cout << currStar->name << endl;
                // check is the current star is one of the closest
                if (currStar == search) {
                    //cout << search->name << endl;

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
            while (visitedStar.find(iter->first) != visitedStar.end()) {
                iter++;
            }
            visitedStar.clear();
            visitedStar.insert(iter->first);
            v.insert(iter->first);
            q.push(iter->first);

        }


    }

    Star* DFS(Star* st, Star* search) {
        // implementing a stack for BFS
        stack<Star *> s;
        auto iter = adjList.begin();
        // use a set to track visited star
        set<Star *> visitedStar;
        set<Star*> v;   //Set containing looked at initial stars
        v.insert(iter->first);
        // start with specified star
        s.push(iter->first);
        visitedStar.insert(iter->first);
        bool run = true;
        while (run) {   //Outer loop because our graph can be disconnected, meaning check all verticies and their connections
            while (!s.empty()) {
                Star *currStar = s.top();
                s.pop();

                //cout << currStar->name << endl;
                // check is the current star is one of the closest
                if (currStar == search) {
                    //cout << search->name << endl;
                    return currStar;
                }
                // check the adjacent stars
                for (auto it: adjList[currStar]) {
                    Star *adjacentStar = it.first;

                    // if the adjacent list isn't visitied add it to the queue
                    if (visitedStar.find(adjacentStar) == visitedStar.end()) {
                        s.push(adjacentStar);
                        visitedStar.insert(adjacentStar);
                    }
                }
            }
            while (v.find(iter->first) != v.end()) {
                iter++;
            }
            v.insert(iter->first);
            visitedStar.clear();
            visitedStar.insert(iter->first);
            s.push(iter->first);
        }

    }

public:
    ~Graph() {
        for (auto &pair : adjList) {
            delete pair.first;
        }
    }
    Star* SearchRandomStar() {
        using std::chrono::high_resolution_clock;
        using std::chrono::duration_cast;
        using std::chrono::duration;
        using std::chrono::milliseconds;
        int randint = rand() % count;
        //cout << count << endl;

        Star* randStar = randomFind[randint];
        auto iter = adjList.begin();


        auto t1 = high_resolution_clock::now(); //Calculate time taken
        Star* d = DFS(iter->first, randStar);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        DFStime = ms_double.count();


        auto t3 = high_resolution_clock::now(); //Calculate time taken
        Star* b = BFS(iter->first, randStar);
        auto t4 = high_resolution_clock::now();
        duration<double, std::milli> ms_doublee = t4 - t3;
        BFStime = ms_doublee.count();


        if (d == b) {return d;}
    }

    void AddStar(Star* s) { // add Star to every other star if the other star has less than "MaxConnection" star connections
        // if has more than "maxConnection", find the star with the largest distance and replace
        adjList[s] = {};
        count++;
        randomFind.push_back(s);
        // iterate through all stars
        for (auto iter = adjList.begin(); iter != adjList.end(); iter++) {
            // connection of iterated Star to new star
            if (iter->second.size() < maxConnections and s->name != iter->first->name) {
                double dis = CalcDistance(iter->first, s);
                adjList[iter->first][s] = dis;
                maxDistance[s] = dis;
            }
            else if (iter->second.size() >= maxConnections and s->name != iter->first->name and maxDistance[s] >
            CalcDistance(iter->first, s)) {  //THIS ONE
                RemoveFurthestStar(iter->first, s);
            }

            // connection of new star to iterated star

            if (adjList[s].size() < maxConnections and s->name != iter->first->name) {
                adjList[s][iter->first] = CalcDistance(s, iter->first);
            }

            else if (adjList[s].size() >= maxConnections and s->name != iter->first->name){
                RemoveFurthestStar(s, iter->first);
            }

        }
    }


    void PrintStarConnections() {
        Star* s = SearchRandomStar();
        cout <<"BFS time: " <<BFStime << " " << "DFS time: "<<DFStime << endl;
        cout << "Star Name: " <<s->name << endl;
        for (auto iter = adjList[s].begin(); iter != adjList[s].end(); iter++) {
            cout << iter->first->name << " "<< iter->second <<" "<< iter->first->constellation <<endl;
        }
    }


};





