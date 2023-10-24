#include <iostream>
#include <thread>
#include "SimpleThreads.h"
#include "Matrices.h"

void ComputeMatrices()
{
   /* const int row = 2;
    const int column = 2;

    int sum[row][column] = 

    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            sum[i][j] = a[i][j] + b[i][j];*/
}

int main()
{
    std::thread thread_one = std::thread{ HelloWorld() };
    std::thread thread_two = std::thread{ HelloAgainWorld() };

    thread_one.join();
    thread_two.join();

    int mat1[Row1][Column1] = { { 1, 1 },
                                { 2, 2 } };

    int mat2[Row2][Column2] = { { 1, 1 },
                                { 2, 2 } };
    Matrix::mulMat(mat1, mat2);
}
