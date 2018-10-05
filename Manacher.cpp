#include<stdio.h>
#include<string>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 101111;
char a[N];
string x;
int r[2*N];
int dap() {
	int mx = 0, p = 0;
	int ret = 0;
	for (int i = 0; i < x.size(); i++) {
		if (i <= mx) {
			r[i] = min(r[2 * p - i], mx - i);
		}
		else
			r[i] = 0;
		while (i + r[i] + 1 < x.size() && i - r[i] - 1 >= 0 && x[i + r[i] + 1] == x[i - r[i] - 1])r[i]++;
		if (mx < i + r[i]) {
			mx = i + r[i];
			p = i;
		}
		ret = max(ret, r[i]);
	}
	return ret;
}
int main() {
	scanf("%s", a);
	int l = strlen(a);
	for (int i = 0; i < l; i++) {
		x += '#';
		x += a[i];
	}
	x += '#';
	printf("%d", dap());
}