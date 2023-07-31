#include <iostream>
#include <fstream>
//y''-4y'-3y=3x^3+6x^2+2x-6; x[–2; –1]; y(–2) = 46; y(–1) = 25

double f(double x) {
	return 3*x*x*x + 6*x*x + 2*x - 6;
}

double** Method_sweep(double a, double b, double y_first, double y_last, double p, double q, int n) {
	const double h = (b - a) / n;
	
	double** answer = new double* [n + 1];
	for (int i = 0; i < n + 1; ++i)
		answer[i] = new double[2];

	answer[0][0] = a; answer[0][1] = y_first;
	answer[n][0] = b; answer[n][1] = y_last;

	for (int i = 1; i < n; ++i) {
		answer[i][0] = answer[i - 1][0] + h;
		answer[i][1] = 0;
	}
	const double A = 1 / (h * h) - p / (2 * h),
				 C = q - 2 / (h * h),
				 B = 1 / (h * h) + p / (2 * h);

	double* D = new double[n - 1];
	D[0] = f(answer[1][0]) - A * answer[0][1];
	for (int i = 1; i < n - 2; ++i)
		D[i] = f(answer[i+1][0]);
	D[n - 2] = f(answer[n - 3][0]) - B * y_last;

	double** u_v = new double* [n - 1];
	for (int i = 0; i < n - 1; ++i)
		u_v[i] = new double[2];

	u_v[0][0] = D[0] / C; u_v[0][1] = -B / C;
	for (int i = 1; i < n - 1; ++i) {
		u_v[i][0] = (D[i] - A * u_v[i - 1][0]) / (A * u_v[i - 1][1] + C);
		u_v[i][1] = (- B) / (A * u_v[i - 1][1] + C);
	}
	
	//size matrix = n-1!!!!!!!!!!!!!!!!
	answer[n - 1][1] = (D[n - 2] - A * u_v[n - 3][0]) / (A * u_v[n - 3][1] + C);
	for (int i = n - 2; i > 0; --i)
		answer[i][1] = u_v[i][0] + u_v[i][1] * answer[i + 1][1];

	for (int i = 0; i < n-1; ++i)
		delete[] u_v[i];
	delete[] u_v;
	delete[] D;

	return answer;
}

int main() {
	const double a = -2, b = -1, 
				 y_first = 46, y_last = 25, 
				 p = -4, q = -3;
	
	const int n = 20;

	double** answer = new double* [n + 1];
	for (int i = 0; i < n + 1; ++i)
		answer[i] = new double[2];

	answer = Method_sweep(a, b, y_first, y_last, p, q, n);
	
	std::ofstream fout("answer.txt");
	fout << "X\tY\n";
	for (int i = 0; i < n + 1; ++i) {
		for (int j = 0; j < 2; ++j)
			fout << answer[i][j] << "\t";
		fout << "\n";
	}
	fout.close();
	
	for (int i = 0; i < 2; ++i)
		delete[] answer[i];
	delete[] answer;

	return 0;
}