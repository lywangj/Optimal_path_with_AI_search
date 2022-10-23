#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include "board.h"
#include "solution.h"
#include "algor/breadth_first.h"
#include "algor/best_first.h"
#include "algor/a_star.h"
#include "test.h"

using namespace std;

int main(int argc, char** argv)
{
    // unit_test();
    // integrate_test_basic();
    // integrate_test();
    
    // Read from the text file
    string filename = argv[1];

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    int w;
    int h;

    infile >> w;
    infile >> h;

    vector<vector<int>> grid;
    string line;
    getline(infile, line);

    while (getline(infile, line)) {
        vector<int> row;
        for (char &c : line) {
            int a = c-'0';
            row.push_back(a);
        }
        grid.push_back(row);
    }

    infile.close();
    Board board{w, h, grid};

    Astar a_star{board};
    a_star.search_results();
    a_star.extract_path_for_result();
    a_star.output_result_step();
    a_star.output_result_path();


    return 0;
}

// g++ -g -Wall -o main main.cpp
