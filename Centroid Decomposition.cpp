#include<stdio.h>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;
const int N = 201111;
map<int, int> M;
vector<pair<int, int> > v[N];
int con[N];
int sz[N];
int k;
int dap = (1 << 30);
int size(int bf, int cur) {
	sz[cur] = 1;
	for (auto x : v[cur]) {
		int next = x.second;
		if (next == bf || con[next])continue;
		sz[cur] += size(cur, next);
	}
	return sz[cur];
}
int cen(int bf, int cur, int half) {
	for (auto x : v[cur]) {
		int next = x.second;
		if (next == bf || con[next])continue;
		if (sz[next] > half)return cen(cur, next, half);
	}
	return cur;
}
void check(int bf, int cur, int len, int dep) {
	if (len > k)return;
	if (M.find(k - len) != M.end()) {
		dap = min(dap, M[k - len] + dep);
	}
	for (auto x : v[cur]) {
		int next = x.second, l = x.first;
		if (next == bf || con[next])continue;
		check(cur, next, len + l, dep + 1);
	}
}

void update(int bf, int cur, int len, int dep) {
	if (len > k)return;
	if (M.find(len) == M.end())M[len] = dep;
	else M[len] = min(M[len], dep);
	for (auto x : v[cur]) {
		int next = x.second, l = x.first;
		if (next == bf || con[next])continue;
		update(cur, next, len + l, dep + 1);
	}
}
void go(int cur) {
	int half = size(-1, cur) / 2;
	int center = cen(-1, cur, half);
	con[center] = 1;
	M.clear(); M[0] = 0;
	for (auto x : v[center]) {
		int next = x.second, l = x.first;
		if (con[next])continue;
		check(center, next, l, 1);
		update(center, next, l, 1);
	}

	for (auto x : v[center]) {
		int next = x.second;
		if (con[next])continue;
		go(next);
	}
}

int main() {
	int n; scanf("%d%d", &n, &k);
	for (int i = 0; i < n - 1; i++) {
		int p, q, r; scanf("%d%d%d", &p, &q, &r);
		v[p].push_back({ r,q });
		v[q].push_back({ r,p });
	}
	go(0);
	if (dap >= (1 << 30)) {
		printf("-1");
	}
	else
		printf("%d", dap);

}