#include<vector>
#include<string>
#include<iostream>

using namespace std;
const int N = 1e6 + 3;
int kmp[N];
vector<int> dap;
string t, p;
int main() {
	getline(cin, t);
	getline(cin, p);

	int i, j = 0, m =t.size(), n = p.size();
	for (i = 1; i < n; i++) {
		while (j > 0 && p[i] != p[j]) 
			j = kmp[j - 1];
		
		if (p[i] == p[j]) 
			kmp[i] = ++j;
	}


	j = 0;
	for (i = 0; i < m; i++) {
		while (j > 0 && t[i] != p[j])
			j = kmp[j - 1];

		if (t[i] == p[j]) {
			if (j == n - 1) {
				dap.push_back(i - j + 1);
				j = kmp[j];
			}
			else
				j++;
		}
	}
	printf("%d\n", dap.size());
	for (int next : dap)
		printf("%d ", next);
}


