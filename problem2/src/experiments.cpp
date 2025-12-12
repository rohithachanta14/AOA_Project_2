#include <bits/stdc++.h>
#include "set_cover_solver.h"
#include "generators.h"
#include "sat_reduction.h"
using namespace std;

int main() {
    cout << "=============================================================\n";
    cout << "    PROBLEM 2: SET COVER - NP-COMPLETENESS & GREEDY\n";
    cout << "=============================================================\n";

    // Demonstration of reduction
    ThreeSATFormula demo;
    demo.n_variables = 3;
    demo.n_clauses = 3;
    demo.clauses = {{1, -2, 3}, {-1, 2, -3}, {1, 2, 3}};
    
    auto reduced = reduceThreeSATtoSetCover(demo);

    // Experimental analysis
    vector<int> sizes = {10, 20, 50, 100, 200, 500};
    cout << "\nSize,Sets,Cost,LowerBound,Time(us),ApproxRatio\n";

    for (int n : sizes) {
        int m = (int)(1.5 * n);
        auto inst = generateRandomSetCover(n, m, 0.4);

        SetCoverSolver solver(inst);
        auto sol = solver.solveGreedy();
        int lb = solver.calculateLowerBound(inst);

        double ratio = (double)sol.cost / lb;

        cout << n << "," << m << "," << sol.cost << "," << lb << ","
             << sol.execution_time_us << "," << fixed << setprecision(3)
             << ratio << "\n";
    }

    return 0;
}
