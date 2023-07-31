#include <iostream>
#include <utility>
#include <cmath>
//5y^2+16y-12xy+2(x^2)y-2

double f_x_y(double x, double y){
    return 5*y*y+16*y-12*x*y+2*x*x*y-2;
}

double f_x(double x, double y){
    return -12*y + 4*x*y;
}

double f_y(double x, double y){
    return 10*y + 16 - 12*x + 2*x*x; 
}

double lenght_grad(double x, double y){
    return std::sqrt(x*x+y*y);
}

std::pair<double, double> Gradient_dascent(const std::pair<double, double>& x_y, double h, int& count){
    const int max_iteration = 100000;
    const double accurate = 1e-3;

    //старые точки
    double last_x = x_y.first, last_y = x_y.second;
    double last_fun = f_x_y(last_x, last_y);
    double last_der_x = 0, last_der_y = 0;
    double last_gradient = 0;
 
    //новые точки
    double der_x = f_x(last_x, last_y), der_y = f_y(last_x, last_y); //частные производные
    double gradient = lenght_grad(der_x, der_y);
    double x = last_x - h*(der_x / gradient), y = last_y - h*(der_y / gradient); //новые точки
    double fun = f_x_y(x, y);
    int count_rep = 0;
    for(count; gradient > accurate; ++count){
        if(count > max_iteration){
            return std::make_pair(nan(""), nan(""));
        }

        //запоминаем старые точки
        last_x = x;
        last_y = y;
        last_fun = fun;
        last_der_x = der_x;
        last_der_y = der_y;
        last_gradient = gradient;

        //счтитаем новые точки
        x = x - h*(der_x / gradient);
        y = y - h*(der_y / gradient);
        fun = f_x_y(x, y);

        if(fun > last_fun){
            x = last_x;
            y = last_y;
            fun = last_fun;
            der_x = last_der_x;
            der_y = last_der_y;
            last_gradient = gradient;
            h /= 2;
            ++count_rep;
            continue;
        }
        
        der_x = f_x(x, y);
        der_y = f_y(x, y);
        gradient = lenght_grad(der_x, der_y);
    }
    return std::make_pair(x, y);
}

int main(){
    double h = 0.01;
    double x = 2.1, y = 0;
    int count = 0;
    std::pair<double, double> x_y = std::make_pair(x, y);
    
    std::pair<double, double> answer = Gradient_dascent(x_y, h, count);
    if(answer.first != answer.first){
        std::cout << "Error!\nExceeded limit iter!\n" << count << " -> Iteration > Max iteration";
        return 0;
    }

    std::cout << "Answer("<< answer.first << "; " << answer.second << ")\n" << "Iteration = "<< count << "\n";
    
    h = 0.001; x = 2; y = 0; count = 0;
    x_y = std::make_pair(x, y);
    answer = Gradient_dascent(x_y, h, count);
    if(answer.first != answer.first){
        std::cout << "\nError!\nExceeded limit iter!\n" << count << " -> Iteration > Max iteration\n";
    //    return 0;
    }

    h = 0.001; x = -2; y = 0; count = 0;
    x_y = std::make_pair(x, y);
    answer = Gradient_dascent(x_y, h, count);
    if(answer.first != answer.first){
        std::cout << "\nError!\nExceeded limit iter!\n" << count << " -> Iteration > Max iteration";
    //    return 0;
    }

    return 0;
}