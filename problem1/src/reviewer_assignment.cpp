#include "reviewer_assignment.h"
#include "mcmf.h"
#include <bits/stdc++.h>
using namespace std;

ReviewerAssignment::ReviewerAssignment(int m_in, int n_in)
    : m(m_in), n(n_in)
{
    k.assign(m, 0);
    c.assign(n, 0);
}

void ReviewerAssignment::addPaperDemand(int i, int demand) {
    k[i] = demand;
}

void ReviewerAssignment::addReviewerCapacity(int j, int cap) {
    c[j] = cap;
}

void ReviewerAssignment::addFeasibleEdge(int i, int j, int cost) {
    feasibleEdges.push_back({i, j, cost});
}

void ReviewerAssignment::solve() {
    int S = 0;
    int paperStart = 1;
    int reviewerStart = paperStart + m;
    int T = reviewerStart + n;
    int N = T + 1;

    MinCostMaxFlow mcmf(N);

    // Source → papers
    for (int p = 0; p < m; p++)
        mcmf.addEdge(S, paperStart + p, k[p], 0);

    // Papers → reviewers
    for (auto &[p, r, w] : feasibleEdges)
        mcmf.addEdge(paperStart + p, reviewerStart + r, 1, w);

    // Reviewers → sink
    for (int r = 0; r < n; r++)
        mcmf.addEdge(reviewerStart + r, T, c[r], 0);

    int K = accumulate(k.begin(), k.end(), 0);
    auto [flow, cost] = mcmf.minCostMaxFlow(S, T, K);

    if (flow != K) {
        cout << "Infeasible assignment.\n";
        return;
    }

    cout << "Minimum total cost = " << cost << "\n";
    cout << "Assignments:\n";

    // Extract assignments
    for (int p = 0; p < m; p++) {
        for (auto &e : mcmf.G[paperStart + p]) {
            if (e.to >= reviewerStart && e.to < reviewerStart + n) {
                int r = e.to - reviewerStart;
                if (e.cap == 0) {
                    cout << "Paper " << p << " assigned to Reviewer " << r << "\n";
                }
            }
        }
    }
}
