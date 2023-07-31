#include <iostream>
#include <cmath> 
#include <utility>
//2x^3 - 9x^2 + 4x + 15 = 0 

double f(double x) { return 2 * x * x * x - 9 * x * x + 4 * x + 15; }
double f_der(double x) { return 6 * x * x - 18 * x + 4; }

std::pair<double, int> dichotomy(double a, double b) {
	double precision = 1e-4;
	int amount = 0;

	double f_a = f(a);
	double c = (a + b) / 2, f_c = f(c);

	while (std::fabs(b - a) > precision) {
		++amount;
		if (f_a * f_c > 0) {
			a = c;
			f_a = f_c;
		}
		else
			b = c;

		c = (a + b) / 2; 
		f_c = f(c);
	}

	double answer = (a + b) / 2;
	return std::make_pair(answer, amount);
}

std::pair <double , int> Newtown(double a, double b, double app) {
	int amount = 1, max_iter = 100000;
	double precision = 1e-4;
	
	double x_i = app - (f(app) / f_der(app)), x_i1 = x_i - (f(x_i) / f_der(x_i));

	while (std::fabs(x_i1 - x_i) > precision) {
		amount += 1;
		if (amount > max_iter)
			return std::make_pair(std::nan(""), 0);

		x_i = x_i1 - (f(x_i1) / f_der(x_i1));
		x_i1 = x_i - (f(x_i) / f_der(x_i));
	}

	double answer = x_i1;
	return std::make_pair(answer, amount);
}

int main() {
	double a_1 = -2, b_1 = 0, app_1 = -1.8;
	std::pair <double, int> answer_1_d = dichotomy(a_1, b_1);
	std::pair<double, int> answer_1_n = Newtown(a_1, b_1, app_1);
	if (answer_1_n.first != answer_1_n.first) {
		std::cout << "Error; Limit reached iter!";
		return 0;
	}

	double a_2 = 1, b_2 = 2.8, app_2 = 2.6;
	std::pair <double, int> answer_2_d = dichotomy(a_2, b_2);
	std::pair<double, int> answer_2_n = Newtown(a_2, b_2, app_2);
	if (answer_2_n.first != answer_2_n.first) {
		std::cout << "Error; Limit reached iter!";
		return 0;
	}
	
	double a_3 = 2.9, b_3 = 4, app_3 = 3.9;
	std::pair <double, int> answer_3_d = dichotomy(a_3, b_3);
	std::pair<double, int> answer_3_n = Newtown(a_3, b_3, app_3);
	if (answer_3_n.first != answer_3_n.first) {
		std::cout << "Error; Limit reached iter!";
		return 0;
	}

	std::cout << "First answer:\n" << "f(-1) = " << f(-1)
			  << "\nMethod dichotomy: answer = " << answer_1_d.first << " (" << answer_1_d.second <<")"
			  << "\nMethod Newton: answer = " << answer_1_n.first << " (" << answer_1_n.second << ")\n";
	
	std::cout << "\nSecond answer:\n" << "f(2.5) = " << f(2.5)
			  << "\nMethod dichotomy: answer = " << answer_2_d.first << " (" << answer_2_d.second << ")"
			  << "\nMethod Newton: answer = " << answer_2_n.first << " (" << answer_2_n.second << ")\n";
	
	std::cout << "\nThird answer:\n" << "f(3) = " << f(3)
			  << "\nMethod dichotomy: answer = " << answer_3_d.first << " (" << answer_3_d.second << ")"
			  << "\nMethod Newton: answer = " << answer_3_n.first << " (" << answer_3_n.second << ")";
	
	return 0;
}