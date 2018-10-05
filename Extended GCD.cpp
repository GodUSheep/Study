#include<stdio.h>
namespace egcd {
	struct solution {
		int g, u, v;
	};

	solution gcd(int a, int b) {
		int u = 1, w = 0;
		int v = 0, x = 1;
		int q, r, temp;
		while (b != 0) {
			q = a / b;
			r = a % b;

			a = b;
			b = r;

			r = w;
			temp = u - q * w;
			u = r, w = temp;

			r = x;
			temp = v - q * x;
			v = r, x = temp;
		}

		return solution{ a, u, v };
	}
}