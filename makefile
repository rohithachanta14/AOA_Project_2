# ============================================================
# Global Makefile for Analysis of Algorithms - Project 2
# Compatible with Windows + Linux
# ============================================================

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -Wshadow -pedantic

# Detect platform (Windows or Unix)
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(subst /,\,$1) mkdir $(subst /,\,$1)
else
    MKDIR = mkdir -p $1
endif

# ============================================================
# Problem 1 Paths
# ============================================================
P1_SRC = problem1/src
P1_BUILD = problem1/build
P1_BIN = $(P1_BUILD)/reviewer_experiments

P1_SOURCES = \
    $(P1_SRC)/reviewer_assignment.cpp \
    $(P1_SRC)/experiments.cpp

P1_HEADERS = \
    $(P1_SRC)/reviewer_assignment.h \
    $(P1_SRC)/mcmf.h

# ============================================================
# Problem 2 Paths
# ============================================================
P2_SRC = problem2/src
P2_BUILD = problem2/build
P2_BIN = $(P2_BUILD)/setcover_experiments

P2_SOURCES = \
    $(P2_SRC)/set_cover_solver.cpp \
    $(P2_SRC)/sat_reduction.cpp \
    $(P2_SRC)/generators.cpp \
    $(P2_SRC)/experiments.cpp

P2_HEADERS = \
    $(P2_SRC)/set_cover_instance.h \
    $(P2_SRC)/set_cover_solver.h \
    $(P2_SRC)/sat_reduction.h \
    $(P2_SRC)/generators.h

# ============================================================
# Default Target (build everything)
# ============================================================
all: problem1 problem2


# ============================================================
# Build Problem 1
# ============================================================
problem1: $(P1_BIN)

$(P1_BIN): $(P1_SOURCES) $(P1_HEADERS)
	$(call MKDIR,$(P1_BUILD))
	$(CXX) $(CXXFLAGS) $(P1_SOURCES) -o $(P1_BIN)

run1: $(P1_BIN)
	$(P1_BIN)


# ============================================================
# Build Problem 2
# ============================================================
problem2: $(P2_BIN)

$(P2_BIN): $(P2_SOURCES) $(P2_HEADERS)
	$(call MKDIR,$(P2_BUILD))
	$(CXX) $(CXXFLAGS) $(P2_SOURCES) -o $(P2_BIN)

run2: $(P2_BIN)
	$(P2_BIN)


# ============================================================
# Clean (removes all compiled output)
# ============================================================
clean:
	rm -rf $(P1_BUILD) $(P2_BUILD)


# ============================================================
# Phony Targets
# ============================================================
.PHONY: all problem1 problem2 run1 run2 clean
