#include <iostream>
#include <cmath>

double series(double x) {	
	double member = (x - 1) / (x + 1);
	double sum = member;
	int max_iter = 10000000;
	double accuracy = 1e-4;

	for (int i = 1; std::fabs(member) > accuracy; ++i) {
		if (i > max_iter) {
			return nan("");
		}
		member *= ((x - 1) / (x + 1)) * ((x - 1) / (x + 1));
		sum += member / (2 * i + 1);
	}

	return 2 * sum;
}

int main() {
	double x = 0;
	std::cout << "Input x:";
	std::cin >> x;

	double series_sum = series(x);
	if (series_sum != series_sum) {
		std::cout << "Error; Exceeded limit iter!";
		return 0;
	}
	
	std::cout << "Series sum = " << series_sum << "\n";
	std::cout << "Ln(" << x << ") = " << std::log(x);

	return 0;
}
