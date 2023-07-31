#include <iostream>
#include <utility>
#include <cmath>

//1.5x^4 - x^3 - 3x^2 + 18x + 6
double f(double x){
    return 1.5 * x * x * x * x - x * x * x - 3 * x * x + 18 * x + 6; 
}

std::pair<double, double> Sven(double x0, double h){
    double a = x0 - h, b = x0 + h; //границы отрезка
    double fa = f(a), fx = f(x0), fb = f(b); //значение функций  

    if(!(fa >= fx && fx <= fb)){ 
        if(fa <= fx)
            h = -h; 
        
        double medium_x = x0 + h, f_medium_x = f(medium_x);
        h *= 2;
        double next_x = medium_x+h, f_next_x = f(medium_x);//xi+1
        double last_x = x0;//xi-1
        
        while(f_next_x < f_medium_x){
            h *= 2;
            last_x = medium_x;
            medium_x = next_x;
            f_medium_x = f_next_x;
            next_x += h;
            f_next_x = f(next_x);
        }

        if(h > 0){
            a = last_x;
            b = next_x;
        }

        else{
            a = next_x;
            b = last_x;
        }
    }   

    return std::make_pair(a, b);
}

double Golden_ratio(std::pair<double, double> a_b){
    const double fi = (std::sqrt(5) + 1) / 2;
    const double accuracy = 1e-3;

    double a = a_b.first, b = a_b.second; //границы отрезков
    
    double y = b - (b - a) / fi, f_y = f(y), //первая точка золотого сечения и значение функции в ней
           z = a + (b - a) / fi, f_z = f(z); //вторая точка золотого сечения и значение функции в ней

    while(std::fabs(a - b) > accuracy){    
        if(f_y < f_z){
            b = z;
            z = y;
            f_z = f_y;
            y = b - (b - a) / fi;
            f_y = f(y);
        }

        else{
            a = y;
            y = z;
            f_y = f_z;
            z = a + (b - a) / fi;
            f_z = f(z);
        }
    }

    return (a + b) / 2;
}

int main(){
//    double x = -1.5, h = 0.1; //первый случай, когда мы находим интервал сразу
//    double x = -0.5, h = 0.1; //второй случай, когда точка минимум находится слева, от заданой точки
//    double x = -2, h = 0.01; //третий случай, точка находится справа
//    double x = -10, h = 1; //большая первая точка
//    double x = 0, h = 10; //большой шаг
//    double x = -2, h = 0.4;
    double x = -2, h = 0.7;


    std::pair<double, double> a_b = Sven(x, h);
    std::cout << "[" << a_b.first << " " << a_b.second << "]\n";

    double point_min  = Golden_ratio(a_b);
    std::cout << "Point minimum = " << point_min;
    return 0;
}