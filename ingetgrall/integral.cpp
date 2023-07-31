#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double f(double x, short int flag) {
	switch (flag){
		case 1: {
			return 2 * x * x * x * x - 2 * x * x - 1;
			break;
		}

		case 2: {
			const double exp = 2.718281828459;
			return (pow(exp, x) / (x * x));
		}
		
		default: return 0;
	} 
}
double rectangle(double a, double b, int n, short int flag) {
	double h = (b - a) / n, node = a + h / 2;
	double sum = f(node, flag);

	for (int i = 1; i < n; ++i) {
		node += h;
		sum += f(node, flag);
	}
	
	return h * sum;
}
double trapezoid(double a, double b, int n, short int flag) {
	double sum = 0, h = (b - a) / n;
	double node = a + h;
	for (int i = 1; i < n; ++i) {
		sum += f(node, flag);
		node += h;
	}
	
	return h * ((f(a, flag) + f(b, flag) / 2) + sum);
}

double Sympson(double a, double b, int n, short int flag) {
	const double h = (b - a) / (2 * n);
	double node = a + h;
	double sum_odd = f(node, flag), sum_hon = 0; //нечетное и четное

	for (int i = 3; i < 2 * n; i += 2) {
		node += 2 * h;
		sum_odd += f(node, flag);
	}

	node = a + 2 * h;
	for (int i = 2; i < 2 * n; i += 2) {
		sum_hon += f(node, flag);
		node += 2 * h;
	}

	return (h / 3) * (f(a, flag) + f(b, flag) + 4 * sum_odd + 2 * sum_hon);
}

void answer(
	double r_1, double r_2, double t_1, double t_2, double s_1, double s_2,
	double r_10, double r_20, double t_10, double t_20, double s_10, double s_20);

double a_fault(double answer) { return abs(answer - 4.2); }
double i_fault(double answer) { return abs(a_fault(answer) / answer); }
double a_Runge(double answer_1, double answer_2) { return abs((answer_1 - answer_2) / (2 * 2 * 2 * 2 - 1)); }
double i_Runge(double answer_1, double answer_2) { return abs(a_Runge(answer_1, answer_2) / answer_1); }

double a_e(double answer_1, double answer_2) { return answer_1 + a_Runge(answer_1, answer_2); }

int main() {

	double a_1 = -1, a_2 = -2.2;
	double b_1 = 2, b_2 = -0.5;

	int n_1 = 10, n_2 = 20;
	int n_sym1 = 5, n_sym2 = 10;
	
	short int flag = 1;
	double an_rec_1 = rectangle(a_1, b_1, n_1, flag);
	double an_rec_2 = rectangle(a_1, b_1, n_2, flag);

	double an_tr_1 = trapezoid(a_1, b_1, n_1, flag);
	double an_tr_2 = trapezoid(a_1, b_1, n_2, flag);
	
	double an_sym_1 = Sympson(a_1, b_1, n_sym1, flag);
	double an_sym_2 = Sympson(a_1, b_1, n_sym2, flag);

	flag = 2;
	double an_rec_10 = rectangle(a_2, b_2, n_1, flag);
	double an_rec_20 = rectangle(a_2, b_2, n_2, flag);

	double an_tr_10 = trapezoid(a_2, b_2, n_1, flag);
	double an_tr_20 = trapezoid(a_2, b_2, n_2, flag);

	double an_sym_10 = Sympson(a_2, b_2, n_1, flag);
	double an_sym_20 = Sympson(a_2, b_2, n_2, flag);

	answer(an_rec_1, an_rec_2, an_tr_1, an_tr_2, an_sym_1, an_sym_2, 
		an_rec_10, an_rec_20, an_tr_10, an_tr_20, an_sym_10, an_sym_20);

	return 0;
}

void answer(
	double r_1, double r_2, double t_1, double t_2, double s_1, double s_2,
	double r_10, double r_20, double t_10, double t_20, double s_10, double s_20) {
	ofstream fout("answer.txt");
	fout << "analytically accurate answer (2x^4 - 2x^2 - 1): " << 4.2 << "\n";
	fout << "Method rectangle(10): " << r_1 << "\n"
		<< "absolute fault: " << a_fault(r_1) << '\n'
		<< "inderect fault: " << i_fault(r_1) 
		<< " (" << i_fault(r_1) * 100 << "%)" << "\n";

	fout << "Method trapezoid(10): " << t_1 << "\n"
		<< "absolute fault: " << a_fault(t_1) << '\n'
		<< "inderect fault: " << i_fault(t_1)
		<< " (" << i_fault(t_1) * 100 << "%)" << "\n";

	fout << "Method Sympson's(10): " << s_1 << "\n"
		<< "absolute fault: " << a_fault(s_1) << '\n'
		<< "inderect fault: " << i_fault(s_1)
		<< " (" << a_fault(s_1) * 100 << "%)" << "\n" << "\n" << "\n";

	fout << "For e^x / x^2:\n";

	fout << "Method rectangle(10): " << r_10 << "\n";
	fout << "Method rectangle(20): " << r_20 << "\n";
	fout << "absolute fault: " << a_Runge(r_10, r_20) << "\n";
	fout << "inderect fault: " << i_Runge(r_10, r_20)
		<< "(" << i_Runge(r_10, r_20) << " %)\n"
		<< "approximate expression: " << a_e(r_10, r_20) << "\n";
	fout << "--------------------\n";

	fout << "Method trapezoid(10): " << t_10 << "\n";
	fout << "Method trapezoid(20): " << t_20 << "\n";
	fout << "absolute fault: " << a_Runge(t_10, t_20) << "\n";
	fout << "inderect fault: " << i_Runge(t_10, t_20)
		<< "(" << i_Runge(t_10, t_20) * 100 << " %)\n"
		<< "approximate expression: " << a_e(t_10, t_20) << "\n";
	fout << "--------------------\n";

	fout << "Method Sympson's(10): " << s_10 << "\n";
	fout << "Method Sympson's(20): " << s_20 << "\n";
	fout << "absolute fault: " << a_Runge(s_10, s_20) << "\n";
	fout << "inderect fault: " << i_Runge(s_10, s_20)
		<< "(" << i_Runge(s_10, s_20) * 100 << " %)\n"
		<< "approximate expression: " << a_e(s_10, s_20);;

	fout.close();
}