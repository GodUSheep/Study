//DP[i][j]=min(i<k<j){D[i][k]+D[j][k]}+C[i][j]

//a<b<c<d에 대해
//C[a][c]+C[b][d]<=C[a][d]+C[b][c]
//C[b][c]<C[a][d]
#include<stdio.h>

const int N = 5055;
int a[N];
int s[N];
int l[N][N];
int dp[N][N];

int main() {
	int tc; scanf("%d", &tc);
	while (tc--) {
		int n; scanf("%d", &n);

		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			s[i] = s[i - 1] + a[i];
		}

		for (int i = 1; i <= n; i++) {
			l[i][i + 1] = i;
			dp[i][i + 1] = 0;
		}

		for (int k = 2; k <= n; k++) {
			for (int st = 1; st + k <= n + 1; st++) {
				int ed = st + k;
				dp[st][ed] = 2011111111;
				for (int j = l[st][ed - 1]; j <= l[st + 1][ed]; j++) {
					int cur = s[ed - 1] - s[st - 1] + dp[st][j] + dp[j][ed];
					if (cur < dp[st][ed]) {
						dp[st][ed] = cur;
						l[st][ed] = j;
					}
				}
			}
		}
		printf("%d\n", dp[1][n + 1]);
	}
}