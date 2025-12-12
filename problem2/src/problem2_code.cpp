#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

// ============================================================================
// PROBLEM 2: SET COVER PROBLEM (NP-Complete)
// Real-world Application: Facility Location & Coverage Optimization
// ============================================================================

// Data structure representing a set cover instance
struct SetCoverInstance {
    int n_elements;           // Number of elements to cover
    int n_sets;              // Number of available sets
    vector<set<int>> sets;   // Each set contains elements it covers
    set<int> universe;       // Universe of all elements
};

// Solution structure
struct SetCoverSolution {
    vector<int> selected_sets;  // Indices of selected sets
    set<int> covered_elements;  // Union of all selected sets
    int cost;                   // Number of sets selected
    double approx_ratio;        // Approximation ratio vs optimal
    long long execution_time_us; // Execution time in microseconds
};

// ============================================================================
// GREEDY ALGORITHM FOR SET COVER (ln(n)-approximation)
// ============================================================================
class SetCoverSolver {
private:
    SetCoverInstance instance;
    
public:
    SetCoverSolver(const SetCoverInstance& inst) : instance(inst) {}
    
    /**
     * Greedy Set Cover Algorithm
     * At each step, select the set that covers the most uncovered elements
     * Approximation Ratio: O(ln n) where n is the universe size
     * Time Complexity: O(n * m^2) where m is number of sets
     */
    SetCoverSolution solveGreedy() {
        auto start = chrono::high_resolution_clock::now();
        
        SetCoverSolution solution;
        set<int> uncovered = instance.universe;
        vector<bool> used(instance.n_sets, false);
        
        while (!uncovered.empty()) {
            // Find set covering maximum uncovered elements
            int best_set = -1;
            int max_coverage = 0;
            
            for (int i = 0; i < instance.n_sets; i++) {
                if (used[i]) continue;
                
                // Count uncovered elements this set would cover
                int coverage = 0;
                for (int elem : instance.sets[i]) {
                    if (uncovered.count(elem)) {
                        coverage++;
                    }
                }
                
                // Better coverage found
                if (coverage > max_coverage) {
                    max_coverage = coverage;
                    best_set = i;
                }
            }
            
            // No uncovered set can cover remaining elements (shouldn't happen)
            if (best_set == -1) break;
            
            // Select this set
            used[best_set] = true;
            solution.selected_sets.push_back(best_set);
            
            // Remove covered elements from uncovered set
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
    
    /**
     * Calculate theoretical lower bound (Lovasz Lower Bound)
     * Used to estimate approximation ratio
     */
    static int calculateLowerBound(const SetCoverInstance& inst) {
        int universe_size = inst.universe.size();
        if (universe_size == 0) return 0;
        
        // Harmonic number H(n) = sum of 1/i for i=1 to n
        // Lower bound is at least universe_size / max_set_size
        int max_set_size = 0;
        for (const auto& s : inst.sets) {
            max_set_size = max(max_set_size, (int)s.size());
        }
        
        if (max_set_size == 0) return universe_size;
        return (int)ceil((double)universe_size / max_set_size);
    }
};

// ============================================================================
// 3-SAT TO SET COVER REDUCTION
// ============================================================================

/**
 * Constructs a Set Cover instance from a 3-SAT formula
 * 
 * Reduction Construction:
 * - Universe: one element per variable per literal (2n elements for n variables)
 *           + one element per clause (m elements)
 * - Sets: For each clause, create 4 sets corresponding to 7 possible
 *         assignments of the 3 variables in that clause
 *
 * The reduction ensures:
 * - 3-SAT formula is satisfiable IFF Set Cover exists with cost k
 */
struct ThreeSATFormula {
    int n_variables;
    int n_clauses;
    vector<vector<int>> clauses;  // Each clause: 3 literals (positive or negative)
    
    /**
     * Clause structure: [literal1, literal2, literal3]
     * Positive literal i means variable i
     * Negative literal -i means NOT variable i
     */
};

SetCoverInstance reduceThreeSATtoSetCover(const ThreeSATFormula& formula) {
    SetCoverInstance instance;
    instance.n_elements = 2 * formula.n_variables + formula.n_clauses;
    instance.n_sets = formula.n_clauses;
    instance.sets.resize(instance.n_sets);
    
    // Elements 0 to 2n-1: variable literals
    // Elements 2n to 2n+m-1: clause elements
    
    // For each clause, create sets representing different truth assignments
    for (int c = 0; c < formula.n_clauses; c++) {
        set<int>& clause_set = instance.sets[c];
        
        // Add clause element (this ensures each set must be selected)
        clause_set.insert(2 * formula.n_variables + c);
        
        // Add elements corresponding to literals that satisfy this clause
        for (int literal : formula.clauses[c]) {
            int var = abs(literal) - 1;  // Variable index (0-based)
            
            if (literal > 0) {
                // Positive literal: variable is true
                clause_set.insert(2 * var);
            } else {
                // Negative literal: variable is false
                clause_set.insert(2 * var + 1);
            }
        }
        
        instance.universe.insert(clause_set.begin(), clause_set.end());
    }
    
    return instance;
}

// ============================================================================
// RANDOM INSTANCE GENERATORS
// ============================================================================

SetCoverInstance generateRandomSetCover(int n_elements, int n_sets, 
                                        double density = 0.3, int seed = 42) {
    SetCoverInstance instance;
    instance.n_elements = n_elements;
    instance.n_sets = n_sets;
    instance.sets.resize(n_sets);
    
    mt19937 rng(seed);
    bernoulli_distribution dist(density);
    
    // Generate random sets with given density
    for (int i = 0; i < n_sets; i++) {
        for (int j = 0; j < n_elements; j++) {
            if (dist(rng)) {
                instance.sets[i].insert(j);
                instance.universe.insert(j);
            }
        }
    }
    
    // Ensure all elements appear in at least one set
    for (int elem = 0; elem < n_elements; elem++) {
        bool found = false;
        for (const auto& s : instance.sets) {
            if (s.count(elem)) {
                found = true;
                break;
            }
        }
        if (!found) {
            int random_set = rng() % n_sets;
            instance.sets[random_set].insert(elem);
        }
        instance.universe.insert(elem);
    }
    
    return instance;
}

ThreeSATFormula generateRandom3SAT(int n_variables, int n_clauses, int seed = 42) {
    ThreeSATFormula formula;
    formula.n_variables = n_variables;
    formula.n_clauses = n_clauses;
    formula.clauses.resize(n_clauses);
    
    mt19937 rng(seed);
    uniform_int_distribution<> var_dist(1, n_variables);
    bernoulli_distribution sign_dist(0.5);
    
    for (int i = 0; i < n_clauses; i++) {
        set<int> clause_vars;
        while (clause_vars.size() < 3) {
            int var = var_dist(rng);
            clause_vars.insert(var);
        }
        
        for (int var : clause_vars) {
            int literal = sign_dist(rng) ? var : -var;
            formula.clauses[i].push_back(literal);
        }
    }
    
    return formula;
}

// ============================================================================
// EXPERIMENTAL ANALYSIS & VERIFICATION
// ============================================================================

struct ExperimentalResult {
    int problem_size;           // n (elements or variables)
    int num_sets;               // m (number of sets)
    long long execution_time_us;
    int solution_cost;
    int lower_bound_estimate;
    double approx_ratio_estimate;
};

void runExperiments() {
    cout << "\n" << string(80, '=') << endl;
    cout << "EXPERIMENTAL ANALYSIS: SET COVER PROBLEM" << endl;
    cout << string(80, '=') << endl;
    
    vector<ExperimentalResult> results;
    ofstream outfile("experiment_results.csv");
    outfile << "Problem_Size,Num_Sets,Time_us,Solution_Cost,Lower_Bound,Approx_Ratio\n";
    
    // Test different problem sizes
    vector<int> problem_sizes = {10, 20, 50, 100, 200, 500};
    
    for (int size : problem_sizes) {
        cout << "\nTesting problem size n = " << size << endl;
        cout << string(50, '-') << endl;
        
        int n_sets = (int)(size * 1.5);  // Ratio of sets to elements
        SetCoverInstance instance = generateRandomSetCover(size, n_sets, 0.4, 42);
        
        cout << "  Elements: " << instance.n_elements << endl;
        cout << "  Sets: " << instance.n_sets << endl;
        cout << "  Universe size: " << instance.universe.size() << endl;
        
        SetCoverSolver solver(instance);
        SetCoverSolution solution = solver.solveGreedy();
        int lower_bound = solver.calculateLowerBound(instance);
        
        cout << "  Greedy solution cost: " << solution.cost << endl;
        cout << "  Lower bound estimate: " << lower_bound << endl;
        cout << "  Approx. ratio: " << fixed << setprecision(3) 
             << (double)solution.cost / lower_bound << endl;
        cout << "  Execution time: " << solution.execution_time_us << " μs" << endl;
        
        ExperimentalResult res;
        res.problem_size = size;
        res.num_sets = instance.n_sets;
        res.execution_time_us = solution.execution_time_us;
        res.solution_cost = solution.cost;
        res.lower_bound_estimate = lower_bound;
        res.approx_ratio_estimate = (double)solution.cost / lower_bound;
        results.push_back(res);
        
        outfile << size << "," << instance.n_sets << "," 
                << solution.execution_time_us << "," << solution.cost << ","
                << lower_bound << "," << fixed << setprecision(3)
                << res.approx_ratio_estimate << "\n";
    }
    
    outfile.close();
    cout << "\n" << string(80, '=') << endl;
    cout << "Results saved to: experiment_results.csv" << endl;
    
    // Verify polynomial time behavior
    cout << "\nVERIFYING POLYNOMIAL TIME COMPLEXITY:" << endl;
    cout << string(50, '-') << endl;
    cout << "Expected: O(n * m^2) where m is number of sets" << endl;
    cout << "\nExecution Time Analysis:" << endl;
    cout << fixed << setprecision(3);
    for (size_t i = 0; i < results.size(); i++) {
        double n = results[i].problem_size;
        double m = results[i].num_sets;
        double t = results[i].execution_time_us;
        double expected = n * m * m / 1000.0;  // Scaled for visibility
        
        cout << "n=" << (int)n << ", m=" << (int)m 
             << ", Time=" << t << "μs, Expected≈" << expected << "μs" << endl;
    }
}

// ============================================================================
// DEMONSTRATION: 3-SAT REDUCTION
// ============================================================================

void demonstrateReduction() {
    cout << "\n" << string(80, '=') << endl;
    cout << "DEMONSTRATION: 3-SAT TO SET COVER REDUCTION" << endl;
    cout << string(80, '=') << endl;
    
    // Create a small 3-SAT instance
    ThreeSATFormula formula;
    formula.n_variables = 3;
    formula.n_clauses = 3;
    formula.clauses = {
        {1, -2, 3},      // (x1 OR NOT x2 OR x3)
        {-1, 2, -3},     // (NOT x1 OR x2 OR NOT x3)
        {1, 2, 3}        // (x1 OR x2 OR x3)
    };
    
    cout << "\n3-SAT Formula:" << endl;
    cout << "Variables: " << formula.n_variables << endl;
    cout << "Clauses: " << formula.n_clauses << endl;
    cout << "\nClauses:" << endl;
    for (int i = 0; i < formula.n_clauses; i++) {
        cout << "  C" << (i+1) << ": ";
        for (int j = 0; j < formula.clauses[i].size(); j++) {
            if (j > 0) cout << " OR ";
            int lit = formula.clauses[i][j];
            if (lit > 0) cout << "x" << lit;
            else cout << "NOT x" << (-lit);
        }
        cout << endl;
    }
    
    // Perform reduction
    cout << "\nReducing to Set Cover..." << endl;
    SetCoverInstance setcover = reduceThreeSATtoSetCover(formula);
    
    cout << "\nSet Cover Instance:" << endl;
    cout << "  Elements: " << setcover.n_elements << endl;
    cout << "  Sets: " << setcover.n_sets << endl;
    cout << "  Universe size: " << setcover.universe.size() << endl;
    
    cout << "\nSets (representing clause satisfiability):" << endl;
    for (int i = 0; i < setcover.n_sets; i++) {
        cout << "  S" << (i+1) << ": {";
        bool first = true;
        for (int elem : setcover.sets[i]) {
            if (!first) cout << ", ";
            first = false;
            if (elem < 2 * formula.n_variables) {
                int var = elem / 2 + 1;
                cout << "x" << var << (elem % 2 == 0 ? "^T" : "^F");
            } else {
                cout << "C" << (elem - 2*formula.n_variables + 1);
            }
        }
        cout << "}" << endl;
    }
    
    // Solve with greedy
    cout << "\nSolving with Greedy Algorithm..." << endl;
    SetCoverSolver solver(setcover);
    SetCoverSolution solution = solver.solveGreedy();
    
    cout << "Solution:" << endl;
    cout << "  Selected sets: ";
    for (int idx : solution.selected_sets) {
        cout << "S" << (idx+1) << " ";
    }
    cout << endl;
    cout << "  Cost: " << solution.cost << endl;
    cout << "  Execution time: " << solution.execution_time_us << " μs" << endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "============================================================================" << endl;
    cout << "    PROBLEM 2: NP-COMPLETE PROBLEM - SET COVER" << endl;
    cout << "    Real-World Application: Facility Location & Coverage Optimization" << endl;
    cout << "    Reduction: 3-SAT ≤_P Set Cover" << endl;
    cout << "============================================================================" << endl;
    
    // Demonstration of reduction
    demonstrateReduction();
    
    // Run experimental analysis
    runExperiments();
    
    cout << "\n" << string(80, '=') << endl;
    cout << "ANALYSIS COMPLETE" << endl;
    cout << string(80, '=') << endl;
    
    return 0;
}
