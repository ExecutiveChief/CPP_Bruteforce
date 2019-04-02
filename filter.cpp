#include <iostream>

using namespace std;

int main() {
    for (string line; getline(cin, line);) {
        if (line.size() >= 16) {
            cout << line << endl;
        }
    }

	return 0;
}
