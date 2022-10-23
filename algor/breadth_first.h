#ifndef __BFS_H__
#define __BFS_H__
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <climits>
#include "../solution.h"
#include "../board.h"

using namespace std;

class Bfs: public Solution {
private:

    queue<Board> q;

    void push_board_to_queue(Board child_board) {
        q.push(child_board);
    }

    Board generate_child_board(int item, Board parent_board, int i, int direction) {
        Board child_board{parent_board, total_steps};
        if (item == 1) shift_column(child_board.arr, i, direction);
        else shift_row(child_board.arr, i, direction);

        handle_target_board(child_board);
        return child_board;
    }

    void shift_each_line(int item, Board parent_board, int i) {

        // shift to lower side
        for (int k = 1; k>=-1;) {
            total_steps++;
            Board child_board = generate_child_board(item, parent_board, i, k);
            blist.push_back(child_board);
            push_board_to_queue(child_board);
            k -= 2;
        }
    }

    void solve_with_bfs() {

        q.push(blist[0]);

        while (!find_result) {

            int level_size = q.size();
            for (int i=0; i<level_size; ++i) {

                Board curr_board = q.front();
                q.pop();

                // shift columns
                for (int i=0; i<curr_board.get_width(); ++i){
                    shift_each_line(1, curr_board, i);
                }

                // shift rows               
                for (int j=0; j<curr_board.get_heigh(); ++j){
                    shift_each_line(0, curr_board, j);
                }
            }
        }
    }
  

public:
    Bfs(Board starting_board){
        blist.push_back(starting_board);
        total_steps = 0;
        min_steps = INT_MAX;
        find_result = false;
    }

    void search_results() {
        cout << "Searching by bfs ... " << endl;
        solve_with_bfs();
        
    }

    int get_current_queue_size() {
        return q.size();
    }

    void unit_test() {

        vector<vector<int>> arr =  {{1, 0, 0},
                                    {0, 1, 0},
                                    {0, 0, 1}};

        // Board ts_board{3, 3, arr};

        shift_column(arr, 0, -1);
        assert(arr[0][0] == 0);
        assert(arr[1][0] == 0);
        assert(arr[2][0] == 1);
        shift_column(arr, 0, 1);
        assert(arr[0][0] == 1);
        assert(arr[1][0] == 0);
        assert(arr[2][0] == 0);

        shift_row(arr, 2, 1);
        assert(arr[2][0] == 1);
        assert(arr[2][1] == 0);
        assert(arr[2][2] == 0);
        shift_row(arr, 2, -1);
        assert(arr[2][0] == 0);
        assert(arr[2][1] == 0);
        assert(arr[2][2] == 1);

        Board ts_board{3, 3, arr};
        Bfs bfs{ts_board};

        assert(bfs.get_current_blist_size() == 1);
        int original_q_size = get_current_queue_size();
        Board parent_board = bfs.blist[0];
        bfs.shift_each_line(1, parent_board, 2);
        assert(bfs.get_current_queue_size() == original_q_size + 2);
        Board column_child_board = bfs.get_board_in_blist_by_index(1);
        assert(column_child_board.arr[0][2] == 1);
        assert(column_child_board.arr[1][2] == 0);
        assert(column_child_board.arr[2][2] == 0);

        bfs.shift_each_line(0, parent_board, 1);
        assert(bfs.get_current_queue_size() == original_q_size + 4);
        Board row_child_board = bfs.get_board_in_blist_by_index(3);
        assert(row_child_board.arr[1][0] == 0);
        assert(row_child_board.arr[1][1] == 0);
        assert(row_child_board.arr[1][2] == 1);
        
        Bfs bfs2{ts_board};
        bfs2.solve_with_bfs();
        assert(bfs2.get_current_results_size() == 1);
        bfs2.extract_path_for_result();
        assert(bfs2.get_min_steps() == 2);

    }

};

#endif 