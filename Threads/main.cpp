#include <iostream>
#include <thread>
#include "SimpleThreads.h"
#include "Matrices.h"
#include "ExercisePage2.h"

class countdown
{
public:

	countdown(int* countP, int oddEvenP, std::mutex& mutex) :
		count(countP),
		oddEven(oddEvenP),
		m(mutex)
	{

	}

	void operator()() const
	{
		startcount();
	}

private:

	int oddEven;
	int* count;
	std::mutex& m;

	void startcount() const
	{
		while (*count < 1000)
		{
			std::lock_guard<std::mutex> lock(m);
			if (*count % 2 == oddEven)
			{
				std::cout << oddEven << " counts : " << *count << std::endl;
				*count += 1;
			}
		}
	}

};

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
}
