#ifndef __SOLVER__
#define __SOLVER__

#define PAT_LENGTH 252
#define BONUS_LEVEL 63
#define BONUS_POINT 35
#define RETRY_LIMIT 2

#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <set>
#include <map>

using namespace std;

int pat_probability(vector<int>& pattern){
    int val = pow(6, 5);
    sort(pattern.begin(), pattern.end());
    int cursor = 0;
    int count = 1;
    for (int i=0;i<pattern.size();i++){
        val /= 6;
        val *= i+1;
        if (pattern[i] == cursor){
            count++;
            val /= count;
        } else {
            count = 1;
            cursor = pattern[i];
        }
    }
    return val;
};

vector<int> next_dicepat(vector<int> pattern){
    for (int i=pattern.size()-1;i>=0;i--){
        if (pattern.at(i) != 6){
            pattern.at(i)++;
            for (int j=i+1;j<pattern.size();j++){
                pattern.at(j) = pattern.at(i);
            }
            break;
        }
    }
    return pattern;
};

vector<vector<vector<pair<int, int>>>> make_trans_list(){
    vector<vector<vector<pair<int, int>>>> trans_list(PAT_LENGTH, vector<vector<pair<int, int>>>(0));

    vector<int> pat = {1,1,1,1,0};
    map<vector<int>, int> pat_index_map;
    for (int i=0;i<PAT_LENGTH;i++){
        pat_index_map[pat] = i;
        pat = next_dicepat(pat);
    }

    pat = {1,1,1,1,0};
    for (int i=0;i<PAT_LENGTH;i++){
        set<vector<int>> pat_set;
        pat = next_dicepat(pat);
        trans_list[i].push_back({{i, pow(6, 5)}});
        //cout << "i: " << i << endl;
        for (int j=0;j<(1<<5)-1;j++){
            vector<int> part_pat;
            for (int k=0;k<5;k++){
                if (j & (1<<k)) part_pat.push_back(pat[k]);
            }
            sort(part_pat.begin(), part_pat.end());
            if (pat_set.find(part_pat) != pat_set.end()) continue;
            pat_set.insert(part_pat);

            /*
            cout << "part_pat: ";
            for (auto& a: part_pat){
                cout << a << " ";
            }
            cout << endl;
            */

            vector<pair<int, int>> t_list;

            vector<int> pair_pat(5-part_pat.size(), 1);
            vector<int> end_pat(5-part_pat.size(), 6);
            pair_pat[pair_pat.size()-1] = 0;

            while (pair_pat != end_pat){
                pair_pat = next_dicepat(pair_pat);
                int val = pat_probability(pair_pat);
                vector<int> tmp_pat = pair_pat;
                tmp_pat.insert(tmp_pat.end(), part_pat.begin(), part_pat.end());
                sort(tmp_pat.begin(), tmp_pat.end());
                int index = pat_index_map[tmp_pat];
                t_list.push_back({index, val});
                //cout << "[" << index << ", " << val << "], ";
            }
            trans_list[i].push_back(t_list);
        }
        cout << endl;
    }

    return trans_list;
};

vector<double> init_val(vector<vector<double>>& data_list, vector<vector<int>>& point_list, int rank_bits, int bonus_count){
    int rank_len = point_list.size();
    vector<double> val_list(PAT_LENGTH, 0);
    for (int i=0;i<PAT_LENGTH;i++){
        for (int j=0;j<rank_len;j++){
            if ((1ll<<j) & rank_bits) continue;
            int point = point_list[j][i];
            if (j < 6){
                if (bonus_count < BONUS_LEVEL && bonus_count + point >= BONUS_LEVEL) point += BONUS_POINT;
                val_list[i] = max(val_list[i], data_list[rank_bits+(1ll<<j)][min(BONUS_LEVEL, bonus_count + point)] + point);
            } else {
                val_list[i] = max(val_list[i], data_list[rank_bits+(1ll<<j)][bonus_count] + point);
            }
        }
    }
    return val_list;
};

vector<double> update_val(vector<double>& val_list, vector<vector<vector<pair<int, int>>>>& trans_list){
    vector<double> new_val_list(PAT_LENGTH, 0);
    for (int i=0;i<PAT_LENGTH;i++){
        for (auto& t_list: trans_list[i]){
            double val = 0;
            for (auto& t_pair: t_list){
                int key = t_pair.first;
                int value = t_pair.second;
                val += val_list[key]*value;
            }
            val /= pow(6, 5);
            new_val_list[i] = max(new_val_list[i], val);
        }
    }
    return new_val_list;
};

vector<vector<double>> solve(vector<vector<int>> point_list){
    int rank_len = point_list.size();
    vector<vector<double>> data_list(1ll<<rank_len, vector<double>(BONUS_LEVEL+1, 0));
    vector<vector<vector<pair<int, int>>>> trans_list = make_trans_list();
    for (int i=(1ll<<rank_len)-2;i>=0;i--){
        cout << i << endl;
        for (int j=0;j<BONUS_LEVEL+1;j++){
            vector<double> val_list = init_val(data_list, point_list, i, j);
            for (int k=0;k<RETRY_LIMIT;k++){
                val_list = update_val(val_list, trans_list);
            }
            double val = 0;
            for (auto t_pair: trans_list[0][1]){
                int key = t_pair.first;
                int value = t_pair.second;
                val += val_list[key] * value;
            }
            val /= pow(6, 5);
            cout << val << ", ";
            data_list[i][j] = val;
        }
        cout << endl;
    }
    return data_list;
};
#endif