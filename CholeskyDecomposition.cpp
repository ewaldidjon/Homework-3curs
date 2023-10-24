#include <iostream>
#include <fstream> //библиотека для работы с файлом
#include <stdlib.h>
#include "Alghoritm.h"
using namespace std;


int main(int argc, char* argv[])
{
    //Обработка входных значений командной строки
    //n - размерность
    //m - количесвто выводимых значений
    //k - номер формулы
    int n = atoi(argv[1]), m = atoi(argv[2]), k = atoi(argv[3]);
    char* file_name = argv[4];
    if(n < m || m < 0 || n == 0 || k < 0 || k > 4) {
        printf("incorrect parameters\n");
        return 1;
    }


    double *A = new double[n*n]; //Выделение памяти для массива, в котором будем хранить нашу матрицу
    Fill(n, A, file_name); //Заполняем этот массив

    MatrixOutput(A, m, n);
    cout << '\n';



    double *b = new double[n];
    double *answer = new double[n];
    b[0] = 6;
    b[1] = 4;

    //У нас есть разложение, теперь надо решить систему R*DRx=b
    //Т.е решаем 3 системы R*y = b, Dx = y, Rk = x, тогда k - решение.
    //solve(A, b, answer, n);

    /*for (int i = 0; i < n; i++) {
        cout << answer[i] << ' ';
    }
    cout << '\n';*/




  double *D = new double[n];
    double *R = new double[n*n];
    double *TR = new double[n*n];
    for (int i = 0; i < n; i++) {
        D[i] = 0;
    }
    for (int i = 0; i <n * n; i++) {
        R[i] = 0;
    }
    for (int i = 0; i <n * n; i++) {
        TR[i] = 0;
    }

    solve(A, b, answer, n);
    for (int i = 0; i < n; i++) {
        cout << answer[i] << ' ';
    }
    cout << '\n';

    D_R_Matrix(n, D, A, R);
    for (int i = 0; i < n*n; i++) {
        cout << R[i] << ' ';
    }
    cout << '\n';
    Transp(R, TR, n);

    double *answer1 = new double[n];
    double *answer2 = new double[n];

    Matrix_Solving_Down(TR, b, n, answer1);
    for (int i = 0; i < n; i++) {
        cout << answer1[i] << ' ';
    }
    cout << '\n';

    Matrix_Solving_Diag(D, answer1, n, answer2);
    Matrix_Solving_UP(R, answer2, n, answer);
    for (int i = 0; i < n; i++) {
        cout << answer[i] << ' ';
    }
    cout << '\n';



    return 0;
}