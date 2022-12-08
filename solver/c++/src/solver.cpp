#include "solver.h"
#include <iostream>

using namespace std;

int pat_probability(vector<int>& pattern);

vector<int> next_dicepat(vector<int> pattern);

vector<vector<double>> solve(vector<vector<int>> point_list);

int main(void){
    vector<int> pat = {1,1,1,1,1};
    vector<int> end_pat = {6,6,6,6,6};
    vector<vector<vector<pair<int, int>>>> trans_list = make_trans_list();
    int count = 0;
    while (pat != end_pat){
        pat = next_dicepat(pat);
        count ++;
    }
    end_pat = next_dicepat(end_pat);
    cout << count << endl;
}