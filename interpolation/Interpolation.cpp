#include <iostream>
#include <fstream>
#include <vector>

std::vector<double> Sweep(const std::vector<double>& y, double h) {
	const double A = 1,
			  B = 1,
			  C = 4;
	const int n = y.size() - 1;
	
	std::vector<double> m(y.size());
	m[0] = (-11 * y[0] + 18 * y[1] - 9 * y[2] + 2*y[3]) / (6 * h);
	m[y.size() - 1] = (11 * y[n] - 18 * y[n - 1] + 9 * y[n - 2] - 2 * y[n - 3]) / (6 * h);

	std::vector<double> D(n-1);
	D[0] = (3 * (y[2] - y[0])) / h - m[0];
	for (int i = 1; i < n - 2; ++i) {
		D[i] = (3 * (y[i+2] - y[i])) / h;
	}
	D[n-2] = (3 * (y[n] - y[n-2])) / h - m[n];

	std::vector<std::vector<double>> u_v(n - 2, std::vector<double>(2));
	u_v[0][0] = D[0] / C; 
	u_v[0][1] = -B / C;
	for (int i = 1; i < n - 2; ++i) {
		u_v[i][0] = (D[i] - A * u_v[i - 1][0]) / (A * u_v[i - 1][1] + C);
		u_v[i][1] = (-B) / (A * u_v[i - 1][1] + C);
	}
	
	m[n-1] = (D[n - 2] - A * u_v[n - 3][0]) / (A * u_v[n - 3][1] + C);
	for (int i = n - 2; i > 0; --i) {
		m[i] = u_v[i - 1][0] + u_v[i - 1][1] * m[i + 1];
	}
	
	return m;
}

std::vector<std::vector<double>> Splayn(const std::vector<double>& x, const std::vector<double>& y) {
	
	std::vector<std::vector<double>> answer(x.size() - 1, std::vector<double>(2));
	const double h = (x[x.size() - 1] - x[0]) / (x.size()-1);

	std::vector <double> m = Sweep(y, h);
	
	for (int i = 0, j = 1; i < m.size()-1; ++i, ++j) {
		answer[i][0] = (x[j] + x[j - 1]) / 2;
		
		double memb_1 = x[j] - answer[i][0]; //xi-x
		double memb_2 = answer[i][0] - x[j - 1]; //x-xi-1
		double memb_3 = answer[i][0] - x[j]; //x-xi
		
		double a = (memb_1 * memb_1 * (h + 2 * memb_2) / (h * h * h) * y[j - 1]);
		double b = (memb_2 * memb_2 * (h + 2 * memb_1)) / (h * h * h) * y[j];
		double c = (memb_1 * memb_1 * memb_2) / (h * h) * m[j - 1];
		double d = (memb_2 * memb_2 * memb_3) / (h * h) * m[j];

		answer[i][1] = a + b + c + d;
	}

	return answer;
}

int main() {
	std::ifstream fin("input.txt");
	if (!fin) {
		std::cout << "Error!\nFile is not open!";
		return 0;
	}

	std::vector<double> vec_x;
	std::vector<double> vec_y;

	for (double x = 0, y = 0; fin >> x >> y;) {
		vec_x.push_back(x);
		vec_y.push_back(y);
	}
	fin.close();

	std::vector<std::vector<double>> answer = Splayn(vec_x, vec_y);
	
	std::ofstream fout("answer.txt");
	fout << "X\tY\n";
	for (auto x : answer) {
		for (auto y: x)
			fout << y << "\t";
		fout << "\n";
	}

	fout.close();
	return 0;
}