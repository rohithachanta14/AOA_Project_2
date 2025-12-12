#ifndef SAT_REDUCTION_H
#define SAT_REDUCTION_H

#include "set_cover_instance.h"

struct ThreeSATFormula {
    int n_variables;
    int n_clauses;
    vector<vector<int>> clauses;
};

SetCoverInstance reduceThreeSATtoSetCover(const ThreeSATFormula& formula);

#endif
