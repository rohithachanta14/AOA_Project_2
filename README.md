# Analysis of Algorithms - Project 2

## Overview

This project contains implementations and experiments for two algorithm design problems:
- **Problem 1**: Reviewer Assignment using Minimum Cost Maximum Flow (MCMF)
- **Problem 2**: Set Cover Solver with SAT Reduction

## Project Structure

```
.
├── problem1/
│   ├── build/
│   │   ├── reviewer_experiments.exe
│   │   └── experiment_driver.exe
│   ├── data/
│   │   ├── results.csv
│   │   ├── runtime_plot.png
│   │   ├── runtime_plot_log.png
│   │   ├── runtime_plot_log_pretty.png
│   │   └── runtime_plot_pretty.png
│   └── src/
│       ├── mcmf.h
│       ├── reviewer_assignment.cpp
│       ├── reviewer_assignment.h
│       ├── experiments.cpp
│       └── plot_runtime.py
│
├── problem2/
│   ├── build/
│   │   └── setcover_experiments.exe
│   ├── data/
│   │   ├── approximation_chart.png
│   │   ├── complexity_chart.png
│   │   ├── experiment_results.csv
│   │   ├── loglog_chart.png
│   │   └── solution_quality_chart.png
│   └── src/
│       ├── experiments.cpp
│       ├── generators.cpp
│       ├── generators.h
│       ├── problem2_code.cpp
│       ├── sat_reduction.cpp
│       ├── sat_reduction.h
│       ├── set_cover_instance.h
│       ├── set_cover_solver.cpp
│       └── set_cover_solver.h
│
├── README.md
├── LICENSE
└── Makefile
```

## Requirements

- **Compiler**: GCC/G++ with C++17 support
- **Platform**: Windows or Linux
- **Build System**: GNU Make
- **Python** (optional): For generating runtime plots in Problem 1

## Building

### Build All Targets
```bash
make
```
Compiles both Problem 1 and Problem 2 executables.

### Build Problem 1 Only
```bash
make problem1
```
Builds `problem1/build/reviewer_experiments.exe`

### Build Problem 2 Only
```bash
make problem2
```
Builds `problem2/build/setcover_experiments.exe`

## Running Experiments

### Run Problem 1 Experiments
```bash
make run1
```
Executes the reviewer assignment experiments and generates runtime analysis plots.

**Output Files**:
- `problem1/data/results.csv` - Experiment results
- `problem1/data/runtime_plot.png` - Linear scale runtime plot
- `problem1/data/runtime_plot_log.png` - Log scale runtime plot
- `problem1/data/runtime_plot_pretty.png` - Formatted linear plot
- `problem1/data/runtime_plot_log_pretty.png` - Formatted log plot

### Run Problem 2 Experiments
```bash
make run2
```
Executes the set cover solver experiments and generates analysis visualizations.

**Output Files**:
- `problem2/data/experiment_results.csv` - Experiment results
- `problem2/data/approximation_chart.png` - Approximation ratio analysis
- `problem2/data/complexity_chart.png` - Computational complexity visualization
- `problem2/data/loglog_chart.png` - Log-log scale analysis
- `problem2/data/solution_quality_chart.png` - Solution quality metrics

## Compilation Flags

The project uses the following compiler flags:
```
-std=c++17       C++17 standard
-O3              Optimization level 3 (maximum optimization)
-Wall            Enable all standard warnings
-Wextra          Enable extra warnings
-Wshadow         Warn about variable shadowing
-pedantic        Strict standard compliance
```

## Cleaning

Remove all compiled output and build directories:
```bash
make clean
```

## Problem Descriptions

### Problem 1: Reviewer Assignment
Implements reviewer assignment logic using a **Minimum Cost Maximum Flow (MCMF)** algorithm to optimally assign reviewers to papers.

**Key Components**:
- `reviewer_assignment.cpp/h` - Core assignment logic and matching algorithm
- `mcmf.h` - MCMF algorithm implementation
- `experiments.cpp` - Experimental framework for performance analysis
- `plot_runtime.py` - Python script to generate runtime visualizations

**Executables**:
- `reviewer_experiments.exe` - Main experiment runner
- `experiment_driver.exe` - Additional experimental driver

### Problem 2: Set Cover Solver
Solves the **Set Cover** problem with SAT reduction techniques, including approximation algorithms and complexity analysis.

**Key Components**:
- `set_cover_solver.cpp/h` - Core solver implementation and algorithms
- `set_cover_instance.h` - Problem instance representation
- `sat_reduction.cpp/h` - SAT reduction and conversion techniques
- `generators.cpp/h` - Random instance generators for testing
- `problem2_code.cpp` - Additional solver implementations
- `experiments.cpp` - Comprehensive experimental framework

**Executable**:
- `setcover_experiments.exe` - Main experiment and analysis runner

## Makefile Targets

| Target | Description |
|--------|-------------|
| `all` | Build both problem1 and problem2 (default) |
| `problem1` | Build Problem 1 executable |
| `problem2` | Build Problem 2 executable |
| `run1` | Build and run Problem 1 experiments |
| `run2` | Build and run Problem 2 experiments |
| `clean` | Remove all build artifacts and directories |

## Output Files

### Problem 1 Data
- **results.csv** - Numerical experiment data (runtime, input size, etc.)
- **PNG Visualizations** - Runtime performance plots in both linear and log scales

### Problem 2 Data
- **experiment_results.csv** - Detailed experiment metrics and measurements
- **PNG Visualizations** - Multiple analysis charts (approximation, complexity, quality)

## Notes

- Executables are generated in `problem*/build/` directories
- The Makefile automatically creates necessary build directories
- Data and visualization outputs are saved to `problem*/data/` directories
- Cross-platform compatible (automatically handles Windows and Unix-based systems)
- All source files use C++17 standard with strict compilation warnings enabled
