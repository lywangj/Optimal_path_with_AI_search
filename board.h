#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;


class Board {
private:

    int width;
    int heigh;
    int index;
    int parent;

    int calculate_priority() {
        int y_dir_priority = 0;
        int col[width] = {0};
        for (int j=0; j<heigh; ++j) {
            for (int i=0; i<width; ++i) {
                if (arr[j][i] == 1) {
                    y_dir_priority += min(j, abs(heigh - j));
                    col[i]++;
                }
            }
        }
        return y_dir_priority + calculate_x_dir_priority(col, width);
    }

    int calculate_x_dir_priority(int* col, int w) {

        int step = 0;
        for (int i=0; i<w; ++i) {
            if(col[i] > 1) {
                int index_of_empty_place = find_nearest_empty_space(col, w, i);
                col[i]--;
                col[index_of_empty_place]++;
                step += min((int) abs(i - index_of_empty_place), (int) abs(w + i - index_of_empty_place) % w);
                --i;
            }
        }
        return step;
    }

    int find_nearest_empty_space(int* col, int w, int i) {
        int left = (i - 1 + w)%w, right = (i + 1)%w;
        int dist_to_right = 0, dist_to_left = 0;

        while (col[(left + w) % w] != 0) {
            left--;
            dist_to_left++;
        }    
        while (col[right % w] != 0) {
            right++;
            dist_to_right++;
        }
        if (dist_to_left <= dist_to_right) return (left + w) % w;
        return right % w;
    }

public:
    int priority;
    int level;
    vector<vector<int>> arr;

    Board(int h, int w, vector<vector<int>>& input) {
        width = w;
        heigh = h;
        arr = input;
        parent = -1;
        index = 0;
        priority = calculate_priority();
        level = 0;
    };

    Board(Board parent_board, int curr_index) {
        width = parent_board.get_width();
        heigh = parent_board.get_heigh();
        for (int j=0; j<heigh; ++j) {
            vector<int> row;
            for (int i=0; i<width; ++i) {
                row.push_back(parent_board.arr[j][i]);
            }
            arr.push_back(row);
        }
        parent = parent_board.get_index();
        index = curr_index;
        level = parent_board.get_level() + 1;
    }

    void set_priority() {
        priority = calculate_priority();
    }

    void set_level_to_zero() {
        level = 0;
    }

    int get_heigh() {
        return heigh;
    }

    int get_width() {
        return width;
    }

    int get_index() {
        return index;
    }

    int get_parent_index() {
        return parent;
    }

    int get_priority() {
        return priority;
    }

    int get_level() {
        return level;
    }

    void print_board() {
        cout << "Array " << index << " :" << endl;
        for (int j=0; j<heigh; ++j) {
            for (int i=0; i<width; ++i) {
                cout << arr[j][i] << " ";
            }
            cout << endl;
        }
        cout << endl;
    };

    void unit_test() {

    vector<vector<int>> arr =  {{0, 1, 0},
                                {0, 1, 0},
                                {0, 1, 0}};

    Board ts_b{3, 3, arr};

    int w = 5;
    int col[w] = {3, 0, 0, 2, 0};

    assert(ts_b.find_nearest_empty_space(col, w, 0) == 4);
    assert(ts_b.find_nearest_empty_space(col, w, 1) == 2);
    assert(ts_b.find_nearest_empty_space(col, w, 2) == 1);
    assert(ts_b.find_nearest_empty_space(col, w, 3) == 2);
    assert(ts_b.find_nearest_empty_space(col, w, 4) == 2);

    int col2[w] = {1, 2, 0, 2, 0};
    assert(ts_b.calculate_x_dir_priority(col2, w) == 2);
    assert(col2[1] == 1);
    assert(col2[4] == 1);

    assert(ts_b.calculate_priority() == 4);

    vector<vector<int>> arr2 =  {{0, 0, 0},
                                 {1, 1, 0},
                                 {0, 1, 0}};
    Board ts_b2{3, 3, arr2};
    ts_b2.set_priority();
    assert(ts_b2.get_priority() == 4);

    vector<vector<int>> arr3 =  {{0, 0, 0},
                                 {1, 0, 1},
                                 {0, 1, 0}};
    Board ts_b3{3, 3, arr3};
    ts_b3.set_priority();
    assert(ts_b3.get_priority() == 3);

    vector<vector<int>> arr4 =  {{1, 1, 0},
                                 {0, 1, 0},
                                 {0, 0, 0}};
    Board ts_b4{3, 3, arr4};
    ts_b4.set_priority();
    assert(ts_b4.get_priority() == 2);

    vector<vector<int>> arr5 =  {{0, 1, 1},
                                 {0, 0, 0},
                                 {1, 0, 0}};
    Board ts_b5{3, 3, arr5};
    ts_b5.set_priority();
    assert(ts_b5.get_priority() == 1);

    Board ts_c(ts_b, 1);
    ts_c.set_priority();
    assert(ts_c.get_priority() == 4);
    assert(ts_c.get_level() == 1);


    }

};

#endif 