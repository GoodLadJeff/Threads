#include <iostream>
#include <thread>
#include "SimpleThreads.h"
#include "Matrices.h"
#include "Countdown.h"
#include "ExercisePage2.h"
#include "SimpleRestaurant.h"

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

    std::cout << "--------------" << std::endl;

    Thread::Sequencial();
    Thread::ThreadLocal();
    Thread::ThreadGlobal();

	int count = 0;
	std::mutex m;

	std::thread countEven(countdown(&count, 0, m));
	std::thread countOdd(countdown(&count, 1, m));

	countEven.join();
	countOdd.join();

    SimpleRestaurant::PlayService();
}
