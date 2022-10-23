#ifndef __BESTFIRST_H__
#define __BESTFIRST_H__
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <climits>
#include "../solution.h"
#include "../board.h"

using namespace std;

bool operator<(const Board& b1, const Board& b2) {
    return (b1.priority + b1.level) > (b2.priority + b2.level);
}

class Best_first: public Solution {
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
        child_board.set_level_to_zero();

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
    Best_first(const Board& starting_board){
        blist.push_back(starting_board);
        total_steps = 0;
        min_steps = INT_MAX;
        find_result = false;
    }

    void search_results() {
        cout << "Searching by best-first ... " << endl;
        solve_with_best_first();
        
    }

    int get_current_queue_size() {
        return pq.size();
    }

    void unit_test() {

        vector<vector<int>> arr =  {{0, 0, 1},
                                    {1, 1, 0},
                                    {0, 0, 0}};

        Board ts_board{3, 3, arr};
        Best_first best{ts_board};

        int original_queue_size = 0;
        best.shift_each_line(1, ts_board, 0);
        assert(best.get_current_queue_size() == original_queue_size + 2);

        Board first_child_board = best.pq.top();
        assert(first_child_board.get_priority() == 1);
        assert(first_child_board.arr[0][0] == 1);

        best.pq.pop();
        Board second_child_board = best.pq.top();
        assert(second_child_board.get_priority() == 2);
        assert(second_child_board.arr[2][0] == 1);


        Best_first best2{ts_board};
        best2.solve_with_best_first();
        assert(best2.get_current_results_size() == 1);
        best2.extract_path_for_result();
        assert(best2.get_min_steps() == 2);
 

    }

};

#endif 