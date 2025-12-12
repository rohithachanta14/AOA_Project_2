#include <bits/stdc++.h>
#include "mcmf.h"
#include "reviewer_assignment.h"
using namespace std;

struct Experiment {
    int m, n;

    pair<bool, double> run() {
        vector<int> k(m, 3);
        vector<int> c(n, (m * 3) / n + 2);

        int S = 0;
        int paperStart = 1;
        int reviewerStart = paperStart + m;
        int T = reviewerStart + n;
        int N = T + 1;

        MinCostMaxFlow mcmf(N);

        for (int p = 0; p < m; p++)
            mcmf.addEdge(S, paperStart + p, k[p], 0);

        mt19937 rng(42);
        uniform_int_distribution<int> costDist(1, 10);

        for (int p = 0; p < m; p++)
            for (int r = 0; r < n; r++)
                mcmf.addEdge(paperStart + p, reviewerStart + r, 1, costDist(rng));

        for (int r = 0; r < n; r++)
            mcmf.addEdge(reviewerStart + r, T, c[r], 0);

        int K = accumulate(k.begin(), k.end(), 0);

        auto start = chrono::high_resolution_clock::now();
        auto [flow, cost] = mcmf.minCostMaxFlow(S, T, K);
        auto end = chrono::high_resolution_clock::now();

        double ms = chrono::duration<double, milli>(end - start).count();
        return {flow == K, ms};
    }
};

int main() {
    vector<int> paperSizes = {10, 20, 50, 100, 150, 200, 300};
    vector<int> reviewerSizes = {6, 10, 20, 30, 40, 60, 80};

    cout << "papers,reviewers,runtime_ms,feasible\n";

    for (size_t idx = 0; idx < paperSizes.size(); idx++) {
        int m = paperSizes[idx];
        int n = reviewerSizes[idx];

        Experiment ex{m, n};
        auto [ok, ms] = ex.run();

        cout << m << "," << n << "," << ms << "," << ok << "\n";
    }
}
