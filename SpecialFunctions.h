#include <iostream>
#include <fstream> //библиотека для работы с файлом
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <stdlib.h>

using namespace std;

/*
// функция заполнения файла рандомными действительными числами
 int MatrixCreation () {
    srand(time(nullptr)); // преамбула для double рандомной генерации
    int quantity = 0; //переменная отвечающая за размер матрицы
     cout << ("Введите размер матрицы: ");
     cin >> quantity;     //ввод размерности матрицы
            ofstream fout;    //объявили переменную типа файла для записи в него
            fout.open("myFile.txt");  //открыли файл
            for (int j = 0; j < quantity; j++){                //заполняем текстовый файл
    for (int i = 0; i < quantity; i++) {
        double RandomNumber = static_cast<double>(rand()) / RAND_MAX * 20000 - 10000;  //создание случайного числа
        fout << RandomNumber << " ";  //запись этого числа в файл
    };
    fout << "\n";
        };
        fout.close(); //закрыли файл
        return quantity;
    }
    */


    //функция решения системы для верхнетреугольной симметричной
    void Matrix_Solving_UP(double *UpMatrix, double *condition, int quantity, double *answer) {
        int SUM = 0;
        answer[quantity-1] = condition[quantity - 1]/UpMatrix[quantity*quantity-1];  
        for (int i = quantity-1; i > 0; i--) {
            for (int k = i; k < quantity; k++) {
                SUM = SUM + answer[k] * UpMatrix[quantity*(i-1) + (k)];
            }
            answer[i-1] = (condition[i-1] - SUM)/UpMatrix[quantity*(i-1) + (i-1)];
            SUM = 0;
        }
    }

    //функция решения системы для диагональной матрицы
    void Matrix_Solving_Diag(double *D, double *condition, int quantity, double *answer) {
        double *DiagMatrix = new double[quantity*quantity];
        for (int i = 0; i < quantity*quantity; i++) {
            DiagMatrix[i] = 0;
            };
            for (int i = 0; i < quantity; i++) {
            DiagMatrix[quantity*i + i] = D[i];
            };
        for (int i = 0; i < quantity; i++) {
            if (DiagMatrix[quantity*i + i] > 0) {
                answer[i] = condition[i];
            };
            if (DiagMatrix[quantity*i+i] < 0) {
                answer[i] = -condition[i];
            };
        }
    }


    //функция решения системы для нижнетреугольной симметричной
    void Matrix_Solving_Down(double *DownMatrix, double *condition, int quantity, double *answer) {
        int SUM = 0;
        answer[0] = condition[0] / DownMatrix[0];
        for (int i = 1; i < quantity; i++) {
            for (int k = 0; k < i; k++) {
                SUM = SUM + answer[k] * DownMatrix[quantity*(i) + k];
            }
            answer[i]= (condition[i] - SUM)/DownMatrix[quantity*(i) + (i)];
            SUM = 0;
        }
    }

    //функция записи чисел из файла в матрицу
    void Fill(int quantity, double *arr, char *name) {
         ifstream fout(name);
    double number = 0;
    int count = 0;
    while (fout >> number && count < quantity*quantity) {
            arr[count] = number;
            count++;
        }
        fout.close();
    }


    //функция сигнум
    double sign(double a) {
        if (a > 0) {
            return 1;
        }
            else {
            return -1;
            }
    }


    //Функция, ищущая матрицы для разложения Холецкого
    void D_R_Matrix(int quantity, double *D, double *A, double *R) {
        double SUM1 = 0;
        double SUM2 = 0; 
        D[0] = sign(A[0]); //задали d11
        R[0] = sqrt(A[0]); //задали r11
        for (int j = 2; j < quantity + 1; j++) {
            R[quantity*(1-1) + (j-1)] = A[quantity*(1-1) + (j-1)] / (R[0]*D[0]);
        }; //задали элементы 1j в матрице R
        for (int i = 2; i < quantity + 1; i++) {
            for (int k = 1; k < i; k++) {
                SUM1 = SUM1 + R[quantity*(k-1) + (i-1)] * R[quantity*(k-1) + (i-1)] * D[k-1];
            }; //задаем SUM1
            D[i-1] = sign(A[quantity*(i-1) + (i-1)] - SUM1); //задали dii
            R[quantity*(i-1) + (i-1)] = sqrt(D[i-1] * (A[quantity*(i-1) + (i-1)] - SUM1)); //задали rii
            for (int j = i; j < quantity; j++) {
                for (int k = 1; k < i; k++) {
                    SUM2 = SUM2 +  R[quantity*(k-1) + (i-1)] * R[quantity*(k-1) + (j-1)] * D[k-1];
                }              
                R[quantity*(i-1) + (j-1)] = (A[quantity*(i-1) + (j-1)] - SUM2) / (R[quantity*(i-1) + (i-1)] * D[i-1]);
                SUM2 = 0;
            }
            SUM1 = 0;
            SUM2 = 0;
        };

    }



    //Функция транспонирующая матрицу
    void Transp(double *A, double *AT, int n) {
        for (int i = 0; i < n; i++) {
            for (int k = i; k < n; k++) {
                AT[n*(i) + k] = A[n*k + i];
                AT[n*k + i] = A[n*i + k];
            }
        }

    }

    //функция вывода матрицы
    void MatrixOutput(double *arr, int m, int n){
            for (int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++ ) {
                    cout << arr[m*i + j] << ' ';
                };
                cout << '\n';
            };
        }