#include <string>
#include <iostream>
#include <vector>

using namespace std;


int main() {
    vector<string> words;
    vector<char> symbols = {'\0', '!', '@', '#', '$', '&', '*'};

    for (string line; getline(cin, line);) {
        words.push_back(line);
    }

    int ctr = 0;

    for (string word1 : words) {
        cerr <<  "\r" << ctr++ << "/" << words.size();
        for (char sym1 : symbols) {
            for (string word2 : words) {
                for (char sym2 : symbols) {
                    for (string word3 : words) {
                        if (sym1 == '\0' && sym2 == '\0') {
                            cout << word1 << word2 << word3 << endl;
                        } else if (sym1 == '\0') {
                            cout << word1 << word2 << sym2 << word3 << endl;
                        } else if (sym2 == '\0') {
                            cout << word1 << sym1 << word2 << word3 << endl;
                        } else {
                            cout << word1 << sym1 << word2 << sym2 << word3 << endl;
                        }
                    }
                }
            }
        }
    }

    return 0;

}
