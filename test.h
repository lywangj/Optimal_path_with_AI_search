#ifndef __TEST_H__
#define __TEST_H__
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <chrono>
#include "board.h"
#include "solution.h"
#include "algor/breadth_first.h"
#include "algor/best_first.h"
#include "algor/a_star.h"

using namespace std;
using namespace std::chrono;

bool check_array(int h, int w, vector<vector<int>> arr) {

    int cnt = 0;
    for (int j=0; j<h; ++j) {
        for (int i=0; i<w; ++i) {
            if (arr[j][i] != 0 and arr[j][i] != 1){
                return false;
            }
            cnt += arr[j][i] == 1? 1 : 0;
        }
    }
    return cnt == w;
}

bool check_valid_board(int h, int w, vector<vector<int>> arr) {

    return h > 0 && w > 0 && h == (int) arr.size() && w == (int) arr[0].size() 
        && check_array(h, w, arr);

}
 
void unit_test() {

    vector<vector<int>> arr =  {{1, 0, 0},
                                {0, 1, 0},
                                {0, 0, 1}};

    assert(check_array(3, 3, arr));

    assert(!check_valid_board(0, 0, arr));
    assert(!check_valid_board(4, 4, arr));

    arr[0][0] = 0;
    assert(!check_valid_board(3, 3, arr));
    arr[0][0] = 2;
    assert(!check_valid_board(3, 3, arr));
    arr[0][0] = 1;

    Board ts_board{3, 3, arr};
    ts_board.unit_test();
    
    Solution solution;
    solution.unit_test_general();

    Bfs bfs{ts_board};
    bfs.unit_test();

    Best_first best_first{ts_board};
    best_first.unit_test();

    Astar astar{ts_board};
    astar.unit_test();

}

void integrate_test() {

    vector<vector<int>> arr2 =  {{0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 1},
                                 {0, 1, 1, 0, 0, 1},
                                 {0, 0, 1, 0, 0, 0},
                                 {0, 1, 0, 0, 0, 0}};

    Board ts_board{5, 6, arr2};
    
    Solution solution;

/*
    Bfs bfs{ts_board};
    bfs.search_results();
    bfs.extract_path_for_result();
    bfs.output_result_step();
    bfs.output_result_path();
*/

    Best_first best_first{ts_board};
    best_first.search_results();
    best_first.extract_path_for_result();
    best_first.output_result_step();
    best_first.output_result_path();

    Astar a_star{ts_board};
    a_star.search_results();
    a_star.extract_path_for_result();
    a_star.output_result_step();
    a_star.output_result_path();

}

void integrate_test_basic() {

    vector<vector<int>> arr2 =  {{0, 0, 0, 0},
                                 {0, 0, 0, 1},
                                 {0, 1, 0, 1},
                                 {0, 1, 0, 0}};

    Board ts_board{4, 4, arr2};
    
    Solution solution;

    auto start1 = high_resolution_clock::now();
    Bfs bfs{ts_board};
    bfs.search_results();
    bfs.extract_path_for_result();
    bfs.output_result_step();
    bfs.output_result_path();
    auto stop1 = high_resolution_clock::now();

    auto duration1 = duration_cast<microseconds>(stop1 - start1);
 
    cout << "Time taken by breadth first search: "
         << duration1.count() << " microseconds" << endl;

    // Best_first best_first{ts_board};
    // best_first.search_results();
    // best_first.extract_path_for_result();
    // best_first.output_result_step();
    // best_first.output_result_path();

    auto start2 = high_resolution_clock::now();
    Astar a_star{ts_board};
    a_star.search_results();
    a_star.extract_path_for_result();
    a_star.output_result_step();
    a_star.output_result_path();
    auto stop2 = high_resolution_clock::now();

    auto duration2 = duration_cast<microseconds>(stop2 - start2);
 
    cout << "Time taken by A* search: "
         << duration2.count() << " microseconds" << endl;
}

#endif 