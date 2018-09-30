#include<stdio.h>
#include<algorithm>
#include<vector>
#include<string.h>
#include<stack>
using namespace std;
int R;
const int N = 10011;
vector<vector<int> > dap;
vector<int> temp;
vector<int> a[N];
int scc[N];
int num[N];
stack<int> S;

int dfs(int here) {
	num[here] = R++;
	int cur = num[here];
	S.push(here);
	for (int there : a[here]) {
		if (num[there] == -1)
			cur = min(cur, dfs(there));
		else if (!scc[there])
			cur = min(cur, num[there]);
	}
	if (cur == num[here]) {
		temp.clear();
		while (!S.empty()) {
			int t = S.top(); S.pop();
			scc[t] = 1;
			temp.push_back(t);
			if (t == here)break;
		}
		sort(temp.begin(), temp.end());
		dap.push_back(temp);
	}
	return cur;
}
int main()
{
	int n, m, i, j;
	scanf("%d%d", &n, &m);
	while (m--) {
		int p, q; scanf("%d%d", &p, &q);
		a[p].push_back(q);
	}
	memset(num, -1, sizeof(num));
	for (i = 1; i <= n; i++) {
		if (num[i] == -1) {
			dfs(i);
		}
	}
	sort(dap.begin(), dap.end());
	printf("%d\n", dap.size());
	for (auto d : dap) {
		for (int j : d)
			printf("%d ", j);
		printf("-1\n");
	}
}


