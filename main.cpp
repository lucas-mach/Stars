#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;


int main() {
    srand(time(NULL));
    fstream file("../HYGData.csv");
    string line;
    Graph starSystem;
    int starCount = 0;
    if (file.is_open()) {

        getline(file, line); // skip header line
        while (getline(file, line)) {
            if (starCount >= 1000) { // cap star count at 120,000
                break;
            }

            istringstream iss(line);
            string col;
            int id;
            string constellation;
            double distFromSun = 0, x = 0, y = 0, z = 0, colorIndex = 0, radialVelocity = 0, vx = 0, vy = 0, vz = 0;

            try {
                getline(iss, col, ',');
                if (!col.empty()) id = stoi(col);

                getline(iss, constellation, ',');

                getline(iss, col, ',');
                if (!col.empty()) distFromSun = stod(col);

                getline(iss, col, ',');
                if (!col.empty()) x = stod(col);

                getline(iss, col, ',');
                if (!col.empty()) y = stod(col);

                getline(iss, col, ',');
                if (!col.empty()) z = stod(col);

                getline(iss, col, ',');
                if (!col.empty()) colorIndex = stod(col);

                getline(iss, col, ',');
                if (!col.empty()) radialVelocity = stod(col);

                getline(iss, col, ',');
                if (!col.empty()) vx = stod(col);

                getline(iss, col, ',');
                if (!col.empty()) vy = stod(col);

                getline(iss, col, ',');
                if (!col.empty()) vz = stod(col);

                if (id == 1 or (x != 0 and y != 0 and z != 0)) {
                    Star *star = new Star(id, constellation, distFromSun, x, y, z, colorIndex, radialVelocity, vx, vy,
                                          vz);
                    //cout << star.name << " " << star.constellation << " " << star.distFromSun << " " <<
                    // star.x << " " << star.y << " " << star.z << " " << star.colorIndex << " " << star.radialVelocity
                    // << " " << star.vx << " " << star.vy << " " << star.vz << endl;
                    starCount++;
                    starSystem.AddStar(star);
                    //cout << "a" << endl;
                }
            }
            catch (const exception &e) {
                cerr << "Error parsing line: " << e.what() << endl;
                continue;
            }
        }
    }
    file.close();
    bool running = true;
    cout << "* . . . * . . * . . . * . .* . . . * . . * . . . * . .* . . . * . . * . . . * . . * ." << endl;
    cout << "* . . . * . . * . . . * . .   Welcome to your HYG Starship!   * . . . * . . * . . . * ."<< endl;
    cout << "* . . . * . . * . . . * . .* . . . * . . * . . . * . .* . . . * . . * . . . * . . * ." << endl;
    string name;
    cout << "                             What's the name of your ship?" << endl;
    cin >> name;

    string spaceship = "                                       .*    *\n"
                       "                      *               .     *    .\n"
                       "                                  .   *   *.    .  *\n"
                       "                              *  ..  *   .  /\\  *\n"
                       "                          .                |--|    . \n"
                       "                                        * /____\\   *\n"
                       "                                     *   |      |  *  .\n"
                       "                                       . |______| *   *\n"
                       "                                       * |_|  |_|  *\n"
                       "                                     .   *v    v   * .  *\n";

    cout << "                                            /\\ \n"
            "                                           |--| \n"
            "                                          /____\\\n"
            "                                         |      |\n"
            "                                         |______|\n"
            "                                         |_|  |_|\n"
            << "                              " << name << " is ready for take off!" << endl;

    cout << endl;
    cout << name << " will traverse the galaxy using a Graph data structure through a BFS and DFS to reach the same random star." << endl;
    cout << "Type \"r\" to get see the statistics of a random star, plus the closest 5 stars to it!" << endl;
    while (running) {


        char x;
        cin >> x;
        if (x == 'e') {
            running = false;
            break;
        }
        if (x == 'r') {
            cout << "Traveling through space and time . . ." << endl;
            cout << spaceship;
            for (int i = 10; i >= 0; --i) {
                cout << "                                          v    v\n";
                this_thread::sleep_for(chrono::milliseconds(10));
                system("cls");
            }

            cout << endl;
            cout << endl;
            starSystem.PrintStarConnections();  // prints a Random Star's stats plus its 5 connections
        }
        cout << endl;
        cout << "                  You can type r again to see a new star, or exit anytime by typing e." << endl;
        cout << "* . . . * . . * . . . * . .* . . . * . . * . . . * . .* . . . * . * . . . * . * * . . . * . . * . * . . *" << endl;


    }

    return 0;
}
