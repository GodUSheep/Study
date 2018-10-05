#include<stack>
#include<algorithm>
#include<stdio.h>
using namespace std;
const int N = 1001111;
struct point {
	int x, y;
	int p, q;
	bool operator<(const point &X) {
		if ((long long)q*X.p != (long long)p*X.q)return (long long)q*X.p < (long long)p*X.q;
		if (y != X.y)return y < X.y;
		return x < X.x;
	}
}a[N];
bool ccw(const point &A, const point &B, const point &C) {
	return 1LL * A.x*B.y + 1LL * B.x*C.y + 1LL * C.x*A.y - 1LL * B.x*A.y - 1LL * C.x*B.y - 1LL * A.x*C.y>0;
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &a[i].x, &a[i].y);
	}
	sort(a, a + n);
	for (int i = 1; i < n; i++) {
		a[i].p = a[i].x - a[0].x;
		a[i].q = a[i].y - a[0].y;
	}
	sort(a + 1, a + n);
	stack<int> S;
	S.push(0), S.push(1);
	for (int i = 2; i < n; i++) {
		while (S.size() >= 2) {
			int one = S.top(); S.pop();
			int two = S.top();
			if (ccw(a[two], a[one], a[i])) {
				S.push(one);
				break;
			}
		}
		S.push(i);
	}
	printf("%d\n", S.size());
}