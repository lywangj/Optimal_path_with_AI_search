#ifndef __SOLUTION_H__
#define __SOLUTION_H__
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "board.h"

using namespace std;

class Solution {
private:


public:

    int min_steps;
    int total_steps;
    bool find_result;
    vector<Board> blist;
    vector<Board> results;

    void push_board_to_queue(Board board) {}

    void shift_column(vector<vector<int>>& arr, int col_idx, int direction) {

        int h = arr.size();
        int k = 0;
        int tmp = arr[k % h][col_idx];

        for (int j=0; j<h-1; ++j) {
            arr[(k + h)% h][col_idx] = arr[(k - direction + h)%h][col_idx];
            k -= direction;
        }
        arr[(0 + direction + h) % h][col_idx] = tmp;

    }

    void shift_row(vector<vector<int>>& arr, int row_idx, int direction) {

        int w = arr[0].size();
        int k = 0;
        int tmp = arr[row_idx][k % w];

        for (int i=0; i<w-1; ++i) {
            arr[row_idx][(k + w)% w] = arr[row_idx][(k - direction + w)%w];
            k -= direction;
        }
        arr[row_idx][(0 + direction + w) % w] = tmp;

    }

    void handle_target_board(Board child_board) {

        if (!find_result && check_target_board(child_board.get_width(), child_board.arr)) {
            // put this board to result list
            results.push_back(child_board);
        }
    }

    bool check_target_board(int w, vector<vector<int>> arr) {
        for (int i=0; i<w; ++i) {
            if (arr[0][i] != 1) return false;
        }
        find_result = true;
        return true;
    }

    void extract_path_for_result() {

        Board final_board = results[0];
        int parent_index = final_board.get_parent_index();
        while (parent_index != -1) {

            Board parent_board = blist[parent_index];
            results.push_back(parent_board);
            parent_index = parent_board.get_parent_index();
        }
        min_steps = results.size() - 1;
    }

    void output_result_path() {

        reverse(results.begin(), results.end());
        for (auto b : results) {
            b.print_board();
        }
    }

    void output_result_step() {

        cout << "Minimum steps: " << min_steps << ", ";
        cout << "Total steps: " << total_steps << endl;

    }

    Board get_board_in_blist_by_index(int index) {
        return blist[index];
    }

    int get_min_steps() {
        return min_steps;
    }

    int get_total_steps() {
        return total_steps;
    }

    int get_current_blist_size() {
        return blist.size();
    }

    int get_current_results_size() {
        return results.size();
    }

    void unit_test() {}

    void unit_test_general() {

        vector<vector<int>> arr =  {{1, 1, 0},
                                    {0, 0, 1}};

        assert(!check_target_board(arr[0].size(), arr));

        arr[0][2] = 1;
        assert(check_target_board(arr[0].size(), arr));
    }
};

#endif 