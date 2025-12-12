#ifndef MCMF_H
#define MCMF_H

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    int cap;
    int cost;
};

struct MinCostMaxFlow {
    int N;
    vector<vector<Edge>> G;
    vector<int> dist, parentV, parentE, potential;

    MinCostMaxFlow(int n)
        : N(n), G(n),
          dist(n), parentV(n), parentE(n), potential(n) {}

    void addEdge(int u, int v, int cap, int cost) {
        Edge a = {v, (int)G[v].size(), cap, cost};
        Edge b = {u, (int)G[u].size(), 0, -cost};
        G[u].push_back(a);
        G[v].push_back(b);
    }

    pair<int, int> minCostMaxFlow(int s, int t, int maxFlow = INT_MAX) {
        int flow = 0, flowCost = 0;
        fill(potential.begin(), potential.end(), 0);

        while (flow < maxFlow) {
            fill(dist.begin(), dist.end(), INT_MAX);
            dist[s] = 0;

            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if (d != dist[u]) continue;

                for (int i = 0; i < (int)G[u].size(); i++) {
                    Edge &e = G[u][i];
                    if (e.cap > 0) {
                        int nd = d + e.cost + potential[u] - potential[e.to];
                        if (nd < dist[e.to]) {
                            dist[e.to] = nd;
                            parentV[e.to] = u;
                            parentE[e.to] = i;
                            pq.push({nd, e.to});
                        }
                    }
                }
            }

            if (dist[t] == INT_MAX) break;

            for (int i = 0; i < N; i++)
                if (dist[i] < INT_MAX)
                    potential[i] += dist[i];

            int addFlow = maxFlow - flow;
            int v = t;

            while (v != s) {
                int u = parentV[v];
                Edge &e = G[u][parentE[v]];
                addFlow = min(addFlow, e.cap);
                v = u;
            }

            v = t;
            while (v != s) {
                int u = parentV[v];
                Edge &e = G[u][parentE[v]];
                e.cap -= addFlow;
                G[v][e.rev].cap += addFlow;
                flowCost += addFlow * e.cost;
                v = u;
            }

            flow += addFlow;
        }

        return {flow, flowCost};
    }
};

#endif
