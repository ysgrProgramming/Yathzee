#include "solver.h"
#include <iostream>

using namespace std;

int pat_probability(vector<int>& pattern);

vector<int> next_dicepat(vector<int> pattern);

vector<vector<double>> solve(vector<vector<int>> point_list);

int main(void){
    vector<vector<int>> point_list(6, vector<int>(PAT_LENGTH, 0));
    for (int i=0;i<6;i++){
        point_list[i][0] = 30;
    }
    solve(point_list);
}