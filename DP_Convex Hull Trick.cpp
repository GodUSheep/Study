//DP[i]=min(j<i){dp[j]+a[i]*b[j]}   (b는 단조감소수열)
//->DP[x=a[i]]=min(j<i){b[j]*x+dp[j]}

//BOJ 4008
#include<stdio.h>
#include<vector>
#include<algorithm>>
using namespace std;

vector<double>X;
vector<pair<long long, long long> > line;
const int N = 1001111;
long long t[N];
long long s[N];
long long dp[N];
long long a, b, c;
double cross(pair<long long, long long> s, pair<long long, long long> e) {
	return 1.0*(e.second - s.second) / (s.first - e.first);
}
void f(pair<long long, long long>cur) {
	while (line.size() >= 2) {
		if (cross(cur, line.back()) >X.back()) {
			break;
		}
		X.pop_back();
		line.pop_back();
	}
	if (!line.empty())
		X.push_back(cross(cur, line.back()));
	line.push_back(cur);
}
long long ret(long long cur) {
	int place = lower_bound(X.begin(), X.end(), (double)cur) - X.begin();
	return line[place].first*cur + line[place].second;
}
int main() {
	int n; scanf("%d", &n);
	scanf("%lld%lld%lld", &a, &b, &c);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &t[i]);
		s[i] = s[i - 1] + t[i];
	}
	long long dap = 0;
	line.push_back(make_pair(0LL, 0LL));
	for (int i = 1; i <= n; i++) {
		dp[i] = ret(s[i]) + a * s[i] * s[i] + b * s[i] + c;
		if (i == 1 || dp[i] > dap)dap = dp[i];
		f(make_pair(-2 * a*s[i], a*s[i] * s[i] - b * s[i] + dp[i]));
	}
	printf("%lld", dap);
}