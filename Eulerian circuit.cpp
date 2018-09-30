#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N = 1011;
int map[N][N];
int dg[N];
int n, m;
vector<int> order;//방문순서
void dfs(int p) {
	for (int i = 1; i <= n; i++) {
		while (map[p][i] > 0) {
			map[p][i]--;
			map[i][p]--;
			dfs(i);
		}

	}
	order.push_back(p);
}
bool chk() {
	for (int i = 1; i <= n; i++) {
		dg[i] /= 2;
		if (dg[i] % 2)
			return false;

	}
	return true;
}

int main()
{
	int i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			scanf("%d", &map[i][j]);
			dg[i] += map[i][j];
			dg[j] += map[i][j];
		}
	}
	if (!chk()) {
		printf("-1");
		return 0;
	}
	dfs(1);
	for (i = order.size() - 1; i >= 0; i--)
		printf("%d ", order[i]);
}
