#include<math.h>
#include<vector>
#include<algorithm>
#include<complex>
using namespace std;

namespace fft {
	typedef std::complex<double> base;
	typedef std::vector<base> vb;
	typedef std::vector<long long> vi;

	const double pi = acos(0)*2.0;

	void fft(vb &a, bool inv) {
		const int n = a.size();
		for (int i = 1, j = 0; i < n; ++i) {
			int bit = (n >> 1);
			for (; j >= bit; bit >>= 1) j -= bit;
			j += bit;
			if (i < j) std::swap(a[i], a[j]);
		}
		for (int len = 2; len <= n; len <<= 1) {
			const int hlen = len >> 1;
			const double ang = pi / hlen * (inv ? -1 : 1);
			const base wlen(cos(ang), sin(ang));
			for (int i = 0; i < n; i += len) {
				base w(1);
				for (int j = 0; j < hlen; ++j) {
					base u = a[i + j], v = a[i + j + hlen] * w;
					a[i + j] = u + v;
					a[i + j + hlen] = u - v;
					w *= wlen;
				}
			}
		}

		if (inv) {
			for (int i = 0; i < n; ++i) a[i] /= n;
		}
	}

	// Assume int is 32bit
	int find_p2(int x) {
		--x;
		x |= (x >> 1);
		x |= (x >> 2);
		x |= (x >> 4);
		x |= (x >> 8);
		x |= (x >> 16);
		return ++x;
	}

	void multiply(const vi &a, const vi &b, vi &res) {
		vb fa(a.begin(), a.end()), fb(b.begin(), b.end());
		const int nz = a.size() + b.size() - 1;
		const int n = find_p2(nz);

		fa.resize(n); fb.resize(n);
		fft(fa, false); fft(fb, false);

		// Multiply results
		for (int i = 0; i < n; ++i) fa[i] *= fb[i];

		fft(fa, true);

		res.resize(nz);
		for (int i = 0; i < nz; ++i) {
			res[i] = (long long)round(fa[i].real());
		}
	}
};