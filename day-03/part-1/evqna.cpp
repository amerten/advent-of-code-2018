#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Rectangle {
    int x, y;
    int w, h;
};

const int GRID_SIZE = 1000;

vector<Rectangle> parse_input(const string& in) {
    istringstream iss(in);
    vector<Rectangle> vec;

    for (string line; getline(iss, line); ) {
        Rectangle rect;
        sscanf(line.c_str(), "#%*d @ %d , %d : %d x %d", &rect.x, &rect.y, &rect.w, &rect.h);
        vec.push_back(rect);
    }

    return vec;
}

int run(const string& in) {
    int grid[GRID_SIZE][GRID_SIZE] = {{0}};

    auto claims = parse_input(in);
    for (auto& c : claims) {
        for (int x = c.x; x < c.x + c.w; x++) {
            for (int y = c.y; y < c.y + c.h; y++) {
                grid[x][y] += 1;
            }
        }
    }

    int overlap = 0;
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            if (grid[x][y] > 1)
                overlap++;
        }
    }
    return overlap;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    clock_t start = clock();
    auto answer = run(string(argv[1]));
    
    cout << "_duration:" << float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC << "\n";
    cout << answer << "\n";
    return 0;
}
