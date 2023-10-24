#pragma once

// C++ program to multiply two matrices 

#include <Bits.h>
#include <iostream>
using namespace std;

#define Row1 2
#define Column1 2 
#define Row2 2
#define Column2 2 

namespace Matrix
{
	void mulMat(int mat1[][Column1], int mat2[][Column2])
	{
		int rslt[Row1][Column2];

		cout << "Multiplication of given two matrices is:\n";

		for (int i = 0; i < Row1; i++) {
			for (int j = 0; j < Column2; j++) {
				rslt[i][j] = 0;

				for (int k = 0; k < Row2; k++) {
					rslt[i][j] += mat1[i][k] * mat2[k][j];
				}

				cout << rslt[i][j] << "\t";
			}

			cout << endl;
		}
	}
}
	