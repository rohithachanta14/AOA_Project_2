#ifndef GENERATORS_H
#define GENERATORS_H

#include "set_cover_instance.h"
#include "sat_reduction.h"

SetCoverInstance generateRandomSetCover(int n_elements, int n_sets,
                                        double density = 0.3, int seed = 42);

ThreeSATFormula generateRandom3SAT(int n_variables, int n_clauses, int seed = 42);

#endif
