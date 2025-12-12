#ifndef SET_COVER_SOLVER_H
#define SET_COVER_SOLVER_H

#include "set_cover_instance.h"

class SetCoverSolver {
private:
    SetCoverInstance instance;

public:
    SetCoverSolver(const SetCoverInstance& inst);

    SetCoverSolution solveGreedy();

    static int calculateLowerBound(const SetCoverInstance& inst);
};

#endif
