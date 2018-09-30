#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
const int N = 222;
const int INF = 1022222222;
int fr[N];
int bk[N];
int lev[N];
int used[N];
vector<int> v[N];
void bfs(int n) {
	queue<int> Q;
	for (int i = 1; i <= n; i++) {
		if (!used[i]) {
			Q.push(i);
			lev[i] = 0;
		}
		else
			lev[i] = INF;
	}
	while (!Q.empty()) {
		int cur = Q.front(); Q.pop();
		for (int next : v[cur]) {
			if (bk[next] != -1 && lev[bk[next]] == INF) {
				Q.push(bk[next]);
				lev[bk[next]] = lev[cur] + 1;
			}
		}
	}
}
int dfs(int cur) {
	for (int next : v[cur]) {
		if (bk[next] == -1 || (lev[bk[next]] == lev[cur] + 1 && dfs(bk[next]))) {
			used[cur] = 1;
			fr[cur] = next;
			bk[next] = cur;
			return 1;
		}
	}
	return 0;
}
int main() {
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int temp; scanf("%d", &temp);
		while (temp--) {
			int p; scanf("%d", &p);
			v[i].push_back(p);
		}
	}
	int dap = 0;
	fill(bk, bk + N, -1);
	fill(fr, fr + N, -1);
	while (1) {
		bfs(n);
		int flow = 0;
		for (int i = 1; i <= n; i++) {
			if (!used[i] && dfs(i))flow++;
		}
		if (flow == 0)break;
		dap += flow;
	}
	printf("%d", dap);
}
