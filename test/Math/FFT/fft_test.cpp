#define PROBLEM "https://atcoder.jp/contests/atc001/tasks/fft_c"
#include <src/Math/FFT/fft.hpp>

#include <complex>
#include <iostream>
#include <vector>

int main()
{
	int n;
	std::cin >> n;
	std::vector<std::complex<double>> v(n + 1), w(n + 1);
	for (int i = 1; i <= n; ++i)
	{
		std::cin >> v[i] >> w[i];
	}
	auto ans = Convolution(v, w);
	for (int i = 1; i <= 2 * n; ++i)
	{
		std::cout << (long long)(ans[i].real() + 0.1) << std::endl;
	}
}