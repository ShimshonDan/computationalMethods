#include <iostream>
#include <fstream>
#include <cmath>

int max_element(double** arr, int index, int size){ //поиск максимального элемента в столбце
    double max_elent = arr[index][index];
    int max_index = index;
    for(int i = index; i < size; ++i)
        if(std::abs(max_elent) < std::abs(arr[i][index]))
            max_index = i;

    return max_index;
}

double* method_Gauss(double** arr, int size){
    double** old_arr = new double* [size]; //скопируем массив
    for(int i = 0; i < size; ++i)
        old_arr[i] = new double [size+1];

    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size+1; ++j)
            old_arr[i][j] = arr[i][j];

    double* answer = new double [size];
    for(int i = 0; i < size; ++i){
        int index_max_element = max_element(old_arr, i, size);
        
        if(!(old_arr[index_max_element][i])){
            answer[0] = nan("");
            return answer;
        }

        if(index_max_element != i){
            for(int j = 0; j < size+1; ++j)
                std::swap(old_arr[index_max_element][j], old_arr[i][j]);
            index_max_element = i;
        }
        
        double max = old_arr[index_max_element][index_max_element];
        for(int j = i; j < size+1; ++j)
            old_arr[i][j] /= max;
        
        for(int j = i+1; j < size; ++j){
            double old = old_arr[j][i];
            for(int k = 0; k < size+1; ++k)
                old_arr[j][k] += (old)*(-old_arr[i][k]);
        }
    }
    
    //модифицированная матрица, которая прошла преобразования
    /*
    std::cout << "Modified matrix\n";
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size+1; ++j)
            std::cout << old_arr[i][j] <<" ";     
        std::cout << "\n";
    }
    */
    answer[size-1] = old_arr[size - 1][size];
    double sum = 0;
    int h = 2;
    for(int i = size-2; i >= 0; --i){ 
        for(int j = i+1; j < size; ++j)
            sum += old_arr[i][j] * answer[j];
        answer[i] = old_arr[size-h][size] - sum;
        sum = 0;
        ++h;
    }

    for(int i = 0; i < size; ++i)
        delete[] old_arr[i];
    delete[] old_arr;

    return answer;
}

int find_index_not_null(double** arr, int size, int index){
    int new_index = 0;
    for(int i = 0; i < size; ++i)
        if(arr[i][index])
            if(arr[index][i])
                return i;
}

bool accurate(double* old_arr, double* new_arr, int size){
    const double E = 1e-3;
    for(int i = 0; i < size; ++i)
        if(std::fabs(new_arr[i] - old_arr[i]) > E)
            return false;
    return true;
}

double* method_Seidel(double** arr, int size){
    double** old_arr = new double* [size];
    for(int i = 0; i < size; ++i)
        old_arr[i] = new double [size+1];

    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size+1; ++j)
            old_arr[i][j] = arr[i][j]; 

    for(int i = 0; i < size; ++i)
        if(!old_arr[i][i]){
            int index = find_index_not_null(arr, size, i);
            for(int j = 0; j < size+1; ++j)
                std::swap(old_arr[i][j], old_arr[index][j]);
            }
   
    //измененная матрица, где на главной диагонали нет нулей
    /*
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j)
            std::cout << old_arr[i][j] << " ";
        std::cout << "\n";
    }
    */

    for(int i = 0; i < size; ++i){
        double del = old_arr[i][i];
        old_arr[i][size] /= del;
        for(int j = 0; j < size; ++j)
            old_arr[i][j] = old_arr[i][j] / (-del);

        old_arr[i][i] = 0;
    }

    //преобразованная матрица
    /*
    std::cout << "Modified matrix\n";
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size+1; ++j)
            std::cout << old_arr[i][j] <<" ";     
        std::cout << "\n";
    }
    */
    double* new_answer = new double [size];
    double* old_answer = new double [size];
    for(int i = 0; i < size; ++i){
        new_answer[i] = 0;
        old_answer[i] = 0;
    }

    bool flag = false; 
    const int max_iter = 10000;
    for(int count = 0; !flag; ++count){
        if(count > max_iter){
            new_answer[0] = nan("");
            return new_answer;
        }

        for(int i = 0; i < size; ++i){
            for(int i = 0; i < size; ++i)
                old_answer[i] = new_answer[i];

            double new_sum = 0;
            for(int j = 0; j < i; ++j)
                new_sum += old_arr[i][j]*old_answer[j];
            
            double old_sum = 0;
            for(int j = i; j < size; ++j)
                old_sum += old_arr[i][j]*old_answer[j];

            new_answer[i] = old_arr[i][size] + new_sum + old_sum;
        }

        flag = accurate(old_answer, new_answer, size);
    }

    for(int i = 0; i < size; ++i)
        delete[] old_arr[i];
    delete[] old_answer;
    
    return new_answer;
}

int main(){
    std::ifstream fin("input.txt");
    if(!fin){
        std::cout << "Error!\nCan't open the fail";
        return 0;
    }
   
    int size = 0;
    fin >> size;

    double** arr = new double* [size];
    for(int i = 0; i < size; ++i)
        arr[i] = new double [size+1];

    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size+1; ++j)
            fin >> arr[i][j];
    fin.close();
    
    std::cout << "Size matrix = " << size << "\nMatrix and free member:\n";
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j)
            std::cout << arr[i][j] << "\t";
        std::cout << "| " << arr[i][size]<< "\n";
    }
    
    double* answer_Gauss = new double [size];
    answer_Gauss = method_Gauss(arr, size);
    if(answer_Gauss[0] != answer_Gauss[0]){
        std::cout << "Matrix hasn't answer_Gauss";
        return 0;
    }
    std::cout << "\nMethod Gauss:\n";
    for(int i = 0; i < size; ++i)
        std::cout << "x" << i+1 << " = " << answer_Gauss[i] << "\n";
    delete[] answer_Gauss;

    double* answer_Seidel = new double [size];
    answer_Seidel = method_Seidel(arr, size);
    if(answer_Seidel[0] != answer_Seidel[0]){
        std::cout << "Erorr!\nExceeded limit iter!";
        return 0;
    }
    std::cout << "\nMethod Seidel:\n";
    for(int i = 0; i < size; ++i)
        std::cout << "x" << i+1 << " = " << answer_Seidel[i] << "\n";
    delete[] answer_Seidel;

    for(int i = 0; i < size; ++i)
        delete[] arr[i];
    delete[] arr;
    
    return 0;
}