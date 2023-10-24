#include <iostream>
#include <fstream> //библиотека для работы с файлом
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <stdlib.h>
#include "SpecialFunctions.h"

using namespace std;



//Напиши функцию, которая решает данную нам систему
//A - матрица системы
//b - правая часть системы
//n - размерность матрицы
//slove - вектор решения
void solve(double *A, double *b, double *answer, int n){
    double *D = new double[n];
    double *R = new double[n*n];
    double *TR = new double[n*n];
    //По умолчанию инициализируем их 0ми
    for (int i = 0; i < n; i++) {
        D[i] = 0;
    }
    for (int i = 0; i <n * n; i++) {
        R[i] = 0;
    }
    for (int i = 0; i <n * n; i++) {
        TR[i] = 0;
    }
    D_R_Matrix(n, D, A, R);
    Transp(R, TR, n);
    double *answer1 = new double[n];
    double *answer2 = new double[n];
    Matrix_Solving_Down(TR, b, n, answer1);
    Matrix_Solving_Diag(D, answer1, n, answer2);
    Matrix_Solving_UP(R, answer2, n, answer);

}