#ifndef SET_COVER_INSTANCE_H
#define SET_COVER_INSTANCE_H

#include <bits/stdc++.h>
using namespace std;

struct SetCoverInstance {
    int n_elements;
    int n_sets;
    vector<set<int>> sets;
    set<int> universe;
};

struct SetCoverSolution {
    vector<int> selected_sets;
    set<int> covered_elements;
    int cost;
    double approx_ratio;
    long long execution_time_us;
};

#endif
