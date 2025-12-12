#include "generators.h"

SetCoverInstance generateRandomSetCover(int n_elements, int n_sets,
                                        double density, int seed) {
    SetCoverInstance instance;
    instance.n_elements = n_elements;
    instance.n_sets = n_sets;
    instance.sets.resize(n_sets);

    mt19937 rng(seed);
    bernoulli_distribution dist(density);

    for (int i = 0; i < n_sets; i++)
        for (int j = 0; j < n_elements; j++)
            if (dist(rng))
                instance.sets[i].insert(j), instance.universe.insert(j);

    for (int elem = 0; elem < n_elements; elem++) {
        bool found = false;
        for (const auto& s : instance.sets)
            if (s.count(elem)) found = true;

        if (!found) {
            int random_set = rng() % n_sets;
            instance.sets[random_set].insert(elem);
        }
        instance.universe.insert(elem);
    }

    return instance;
}

ThreeSATFormula generateRandom3SAT(int n_variables, int n_clauses, int seed) {
    ThreeSATFormula formula;
    formula.n_variables = n_variables;
    formula.n_clauses = n_clauses;
    formula.clauses.resize(n_clauses);

    mt19937 rng(seed);
    uniform_int_distribution<> var_dist(1, n_variables);
    bernoulli_distribution sign_dist(0.5);

    for (int i = 0; i < n_clauses; i++) {
        set<int> vars;
        while (vars.size() < 3)
            vars.insert(var_dist(rng));

        for (int v : vars)
            formula.clauses[i].push_back(sign_dist(rng) ? v : -v);
    }

    return formula;
}
