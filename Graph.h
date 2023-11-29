#include <map>
#include <vector>
#include <string>
#include <tuple>
#include <iostream>
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
    void Add(Star* s) {   // Add Star to every other star if the other star has less than 5 star connections
                        // If has more than 5, find the star with the largest distance and replace
                        // ****STILL NEED TO ACCOUNT FOR ADDING THE FIRST STAR****

        adjList[s] = {};
        // Iterate through all stars
        for (auto iter = adjList.begin(); iter != adjList.end(); iter++) {
            if (iter->second.size() < 5 and s->name != iter->first->name) {
                adjList[iter->first][s] = CalcDistance(iter->first, s);
            }
            else if (iter->second.size() >= 5 and s->name != iter->first->name) {
                RemoveFurthestStar(iter->first, s);
            }
            if (adjList[s].size() < 5 and s->name != iter->first->name) {
                adjList[s][iter->first] = CalcDistance(s, iter->first);
            }
            else if (adjList[s].size() >= 5 and s->name != iter->first->name){
                RemoveFurthestStar(s, iter->first);
            }
        }

        if (m.find(s->name) == m.end()) {    // Is not in Map
            m[s->name] = s;
        }
    }

    int CalcDistance(Star* first, Star* second) {   //Calculate distance between two stars
        return 0;
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

    void PrintStarConnections() {
        for (auto iter = adjList.begin(); iter != adjList.end(); iter++) {
            for (auto it = adjList[iter->first].begin(); it != adjList[iter->first].end(); it++) {
                cout << it->first->name << endl;
            }
            cout <<"^ is for star: " <<iter->first->name <<"-----------------" << endl;
        }

    }






};





