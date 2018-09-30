#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

struct MaximumFlow {
	struct edge {
		int to, c, f, rev;
		edge(int to, int c) :to(to), c(c), f(0) {}
	};

	int N, S, E;
	int INF = 2011111111;

	vector<int> work;
	vector<int> level;
	vector<vector<edge> > v;

	MaximumFlow(int N, int S, int E) :N(N), S(S), E(E) {
		work.resize(N);
		level.resize(N);
		v.resize(N);
	}

	void add_edge(int s, int e, int c) {
		v[s].emplace_back(e, c);
		v[e].emplace_back(s, 0);
		v[s].back().rev = v[e].size() - 1;
		v[e].back().rev = v[s].size() - 1;
	}
	queue<int> Q;
	bool bfs(void) {
		for (int i = 0; i < N; i++)level[i] = -1;
		level[S] = 0;
		Q.push(S);
		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto next : v[cur]) {
				if (level[next.to] == -1 && next.c - next.f > 0) {
					level[next.to] = level[cur] + 1;
					Q.push(next.to);
				}
			}
		}
		return level[E] != -1;
	}

	int dfs(int cur, int des, int cf) {
		if (cur == des)return cf;
		for (int &i = work[cur]; i< v[cur].size(); i++) {
			auto &next = v[cur][i];
			if (level[next.to] == level[cur] + 1 && next.c - next.f > 0) {
				int nf = dfs(next.to, des, min(cf, next.c - next.f));
				if (nf > 0) {
					next.f += nf;
					v[next.to][next.rev].f -= nf;
					return nf;
				}
			}
		}
		return 0;
	}
	int flow() {
		int dap = 0;
		while (bfs()) {
			for (int i = 0; i < N; i++)work[i] = 0;
			while (1) {
				int tf = dfs(S, E, INF);
				if (tf == 0)break;
				dap += tf;
			}
		}
		return dap;
	}
};