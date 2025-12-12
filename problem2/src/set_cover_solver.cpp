#include "set_cover_solver.h"

SetCoverSolver::SetCoverSolver(const SetCoverInstance& inst)
    : instance(inst) {}

SetCoverSolution SetCoverSolver::solveGreedy() {
    auto start = chrono::high_resolution_clock::now();

    SetCoverSolution solution;
    set<int> uncovered = instance.universe;
    vector<bool> used(instance.n_sets, false);

    while (!uncovered.empty()) {
        int best_set = -1, max_coverage = 0;

        for (int i = 0; i < instance.n_sets; i++) {
            if (used[i]) continue;

            int coverage = 0;
            for (int elem : instance.sets[i])
                if (uncovered.count(elem)) coverage++;

            if (coverage > max_coverage) {
                max_coverage = coverage;
                best_set = i;
            }
        }

        if (best_set == -1) break;

        used[best_set] = true;
        solution.selected_sets.push_back(best_set);

        for (int elem : instance.sets[best_set]) {
            uncovered.erase(elem);
            solution.covered_elements.insert(elem);
        }
    }

    solution.cost = solution.selected_sets.size();
    auto end = chrono::high_resolution_clock::now();
    solution.execution_time_us =
        chrono::duration_cast<chrono::microseconds>(end - start).count();

    return solution;
}

int SetCoverSolver::calculateLowerBound(const SetCoverInstance& inst) {
    int max_set = 0;
    for (const auto& s : inst.sets)
        max_set = max(max_set, (int)s.size());

    if (max_set == 0) return inst.universe.size();
    return ceil((double)inst.universe.size() / max_set);
}
