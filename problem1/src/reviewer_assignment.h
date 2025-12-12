#ifndef REVIEWER_ASSIGNMENT_H
#define REVIEWER_ASSIGNMENT_H

#include <vector>
#include <tuple>

struct ReviewerAssignment {
    int m, n; // number of papers, reviewers
    std::vector<int> k; // paper demands
    std::vector<int> c; // reviewer capacities
    std::vector<std::tuple<int,int,int>> feasibleEdges;

    ReviewerAssignment(int m_in, int n_in);

    void addPaperDemand(int i, int demand);
    void addReviewerCapacity(int j, int cap);
    void addFeasibleEdge(int i, int j, int cost);

    void solve();
};

#endif // REVIEWER_ASSIGNMENT_H