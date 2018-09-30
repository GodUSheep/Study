//DP[i][j]=min(k<j){DP[i-1][k]+C[k][j]}

//a<b<c<d에 대해
//C[a][c]+C[b][d]<=C[a][d]+C[b][c]
//max면 반대
#include<stdio.h>
const int N = 8088;
long long dp[808][N];
long long a[N];
long long s[N];
long long how(int p, int q) {
	return (s[q] - s[p])*(q - p);
}

void f(int cur, int s, int e, int kl, int kr) {
	if (s > e)return;
	int m = (s + e) / 2;
	dp[cur][m] = 1LL << 61;
	int place = -1;
	for (int i = kl; i <= kr && i < m; i++) {
		if (dp[cur][m] > dp[cur - 1][i] + how(i, m)) {
			dp[cur][m] = dp[cur - 1][i] + how(i, m);
			place = i;
		}
	}
	f(cur, s, m - 1, kl, place);
	f(cur, m + 1, e, place, kr);
}
int main() {
	int n, k; scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
	for (int i = 1; i <= n; i++)
		dp[1][i] = how(0, i);
	for (int i = 2; i <= k; i++)
		f(i, 1, n, 0, n - 1);
	printf("%lld\n", dp[k][n]);
}