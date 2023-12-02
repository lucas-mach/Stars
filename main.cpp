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
    fstream file("../HYGData.csv");
    string line;
    Graph starSystem;
    int starCount = 0;
    if (file.is_open()) {

        getline(file, line); // skip header line
        while (getline(file, line)) {
            if (starCount >= 10000) { // cap star count at 120,000
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
                }
            }
            catch (const exception &e) {
                cerr << "Error parsing line: " << e.what() << endl;
                continue;
            }
        }
    }
    file.close();

    starSystem.PrintStarConnections();


    //SFML Window
    //sf::RenderWindow window(sf::VideoMode(800, 600), "STARS");
    //https://www.youtube.com/watch?v=BILAqQ-ZFDA

    return 0;
}
