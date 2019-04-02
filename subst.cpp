#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

/* Source: https://www.geeksforgeeks.org/power-set/
 * Visited: 20-feb-2018 */
vector<vector<pair<char, char>>> get_powerset(vector<pair<char, char>> all_replacements) {
    vector<vector<pair<char, char>>> powerset;
    auto power_size = (size_t) pow(2, all_replacements.size());

    for (size_t ctr = 0; ctr < power_size; ctr++) {
        vector<pair<char, char>> worklist = vector<pair<char, char>>();
        for (size_t i = 0; i < all_replacements.size(); i++) {

            if(ctr & (1<<i)) {
                pair<char, char> tuple = pair<char, char>(all_replacements.at(i).first, all_replacements.at(i).second);
                worklist.push_back(tuple);
            }
        }
        powerset.push_back(worklist);
    }

    return powerset;
}


int main(int argc, char* argv[]) {
    ifstream myfile;
    myfile.open(argv[1]);
    vector<pair<char, char>> all_replacements;
    string line;

    while (getline(myfile, line)) {
        std::pair<char, char> tuple = std::pair<char, char>(line[0], line[1]);
        all_replacements.push_back((tuple));
    }

    vector<vector<pair<char, char>>> powerset;

    powerset = get_powerset(all_replacements); //TODO

    for (string og_line; getline(cin, og_line);) {
        cout << line << endl;
        for (auto subset : powerset) {
            line = og_line;

            for (char& c : line) {
                for (auto replacement : subset) {
                    if (c == replacement.first) {
                        c = replacement.second;
                    }
                }
            }
            cout << line << endl;
        }
    }

    return 0;
}
