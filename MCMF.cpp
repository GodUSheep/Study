#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

struct MCMF {
	int N, S, E;
	int INF = 2011111111;
	struct edge {
		int to, c, f, cost, rev;
		edge(int to, int c, int cost) :to(to), c(c), cost(cost), f(0) {}
	};
	vector<vector<edge> > v;
	vector<pair<int, int> > pre;
	vector<int> inQ;
	vector<int> dist;

	MCMF(int N, int S, int E) :N(N), S(S), E(E) {
		v.resize(N);
		pre.resize(N);
		inQ.resize(N);
		dist.resize(N);
	}

	void add_edge(int s, int e, int c, int cost) {
		v[s].emplace_back(e, c, cost);
		v[e].emplace_back(s, 0, -cost);
		v[s].back().rev = v[e].size() - 1;
		v[e].back().rev = v[s].size() - 1;
	}

	pair<int, int> flow() {
		pair<int, int> ret = { 0,0 };
		queue<int> Q;
		while (1) {
			for (int i = 0; i < N; i++) {
				pre[i] = { -1,-1 };
				dist[i] = INF;
				inQ[i] = 0;
			}
			dist[S] = 0;
			Q.push(S);
			while (!Q.empty()) {
				int cur = Q.front(); Q.pop(); inQ[cur] = 0;
				for (int i = 0; i < v[cur].size(); i++) {
					auto &next = v[cur][i];
					if (next.c - next.f > 0 && dist[next.to] > dist[cur] + next.cost) {
						dist[next.to] = dist[cur] + next.cost;
						pre[next.to] = { cur,i };
						if (!inQ[next.to]) {
							inQ[next.to] = 1;
							Q.push(next.to);
						}
					}
				}
			}
			if (pre[E].first == -1)break;
			int tf = INF;
			for (int cur = E; cur != S; cur = pre[cur].first) {
				auto &e = v[pre[cur].first][pre[cur].second];
				tf = min(tf, e.c - e.f);
			}

			for (int cur = E; cur != S; cur = pre[cur].first) {
				auto &e = v[pre[cur].first][pre[cur].second];
				e.f += tf;
				v[e.to][e.rev].f -= tf;
				ret.second += tf * e.cost;
			}
			ret.first += tf;
		}
		return ret;
	}
};