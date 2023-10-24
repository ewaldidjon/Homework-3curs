 #include <iostream>
#include <fstream> //библиотека для работы с файлом
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <stdlib.h>

using namespace std;


 //функция записи чисел из файла в матрицу
    void Fill(int n, double *arr, char *name) {
         ifstream fout(name);
    double number = 0;
    int count = 0;
    while (fout >> number && count < n*n) {
            arr[count] = number;
            count++;
        }
        fout.close();
    }