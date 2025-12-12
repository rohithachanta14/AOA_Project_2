#include "sat_reduction.h"

SetCoverInstance reduceThreeSATtoSetCover(const ThreeSATFormula& formula) {
    SetCoverInstance instance;
    instance.n_elements = 2 * formula.n_variables + formula.n_clauses;
    instance.n_sets = formula.n_clauses;
    instance.sets.resize(instance.n_sets);

    for (int c = 0; c < formula.n_clauses; c++) {
        set<int>& clause_set = instance.sets[c];
        clause_set.insert(2 * formula.n_variables + c);

        for (int literal : formula.clauses[c]) {
            int var = abs(literal) - 1;

            if (literal > 0)
                clause_set.insert(2 * var);
            else
                clause_set.insert(2 * var + 1);
        }

        instance.universe.insert(clause_set.begin(), clause_set.end());
    }

    return instance;
}
