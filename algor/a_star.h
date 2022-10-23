#ifndef __ASTAR_H__
#define __ASTAR_H__
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <climits>
#include "../solution.h"
#include "../board.h"

using namespace std;

class Astar: public Solution {
private:

    priority_queue<Board> pq;


    void push_board_to_queue(Board child_board) {
        pq.push(child_board);
    }

    Board generate_child_board(int item, Board parent_board, int i, int direction) {
        Board child_board{parent_board, total_steps};

        if (item == 1) shift_column(child_board.arr, i, direction);
        else shift_row(child_board.arr, i, direction);
        child_board.set_priority();

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

    void solve_with_best_first() {

        pq.push(blist[0]);

        while (!find_result) {

            Board curr_board = pq.top();
            pq.pop();

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


public:
    Astar(const Board& starting_board){
        blist.push_back(starting_board);
        total_steps = 0;
        min_steps = 0;
        find_result = false;
    }

    void search_results() {
        cout << "Searching by A* search ... " << endl;
        solve_with_best_first();
        
    }

    int get_current_queue_size() {
        return pq.size();
    }

    void unit_test() {

        vector<vector<int>> arr =  {{1, 0, 1},
                                    {0, 1, 0},
                                    {0, 0, 0}};

        Board ts_board{3, 3, arr};
        Astar a_star{ts_board};

        int original_queue_size = 0;
        a_star.shift_each_line(1, ts_board, 1);
        assert(a_star.get_current_queue_size() == original_queue_size + 2);

        Board first_child_board = a_star.pq.top();

        assert(first_child_board.get_priority() == 0);
        assert(first_child_board.get_level() == 1);
        assert(first_child_board.arr[0][0] == 1);
        a_star.pq.pop();

        Board second_child_board = a_star.pq.top();
        assert(second_child_board.get_priority() == 1);
        assert(first_child_board.get_level() == 1);
        assert(second_child_board.arr[2][1] == 1);

    }

};

#endif 