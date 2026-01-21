#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <sstream>
#include "D:\education\Lab 7.2_2\Lab 7.2_2.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Function declarations from Lab 7.2_2.cpp
extern void CreateRow(int** a, int row, int col, const int n, const int Low, const int High);
extern void CreateRows(int** a, int row, const int k, const int n, const int Low, const int High);
extern void PrintRow(int** a, int row, int col, const int n);
extern void PrintRows(int** a, int row, const int k, const int n);
extern int RowMin(int** a, int row, int col, const int n);
extern int MaxOfRowMins(int** a, int row, const int k, const int n, int currentMax);

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(Test_CreateRow)
		{
			const int n = 3, Low = 1, High = 1;
			int** a = new int* [1];
			a[0] = new int[n];
			// Fixed seed for deterministic output
			srand(0);
			CreateRow(a, 0, 0, n, Low, High);
			for (int i = 0; i < n; ++i)
				Assert::AreEqual(1, a[0][i]);
			delete[] a[0];
			delete[] a;
		}

		TEST_METHOD(Test_CreateRows)
		{
			const int k = 2, n = 2, Low = 5, High = 5;
			int** a = new int* [k];
			for (int i = 0; i < k; ++i)
				a[i] = new int[n];
			srand(0);
			CreateRows(a, 0, k, n, Low, High);
			for (int i = 0; i < k; ++i)
				for (int j = 0; j < n; ++j)
					Assert::AreEqual(5, a[i][j]);
			for (int i = 0; i < k; ++i)
				delete[] a[i];
			delete[] a;
		}

		TEST_METHOD(Test_PrintRow)
		{
			const int n = 3;
			int** a = new int* [1];
			a[0] = new int[n] { 1, 2, 3 };
			std::stringstream buffer;
			std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
			PrintRow(a, 0, 0, n);
			std::cout.rdbuf(oldCout);
			std::string expected = "    1    2    3\n";
			Assert::AreEqual(expected, buffer.str());
			delete[] a[0];
			delete[] a;
		}

		TEST_METHOD(Test_PrintRows)
		{
			const int k = 2, n = 2;
			int** a = new int* [k];
			a[0] = new int[n] { 1, 2 };
			a[1] = new int[n] { 3, 4 };
			std::stringstream buffer;
			std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
			PrintRows(a, 0, k, n);
			std::cout.rdbuf(oldCout);
			std::string expected = "    1    2\n    3    4\n\n";
			Assert::AreEqual(expected, buffer.str());
			for (int i = 0; i < k; ++i)
				delete[] a[i];
			delete[] a;
		}

		TEST_METHOD(Test_RowMin)
		{
			const int n = 4;
			int** a = new int* [1];
			a[0] = new int[n] { 7, 2, 9, 4 };
			int min = RowMin(a, 0, 0, n);
			Assert::AreEqual(2, min);
			delete[] a[0];
			delete[] a;
		}

		TEST_METHOD(Test_MaxOfRowMins)
		{
			const int k = 3, n = 3;
			int** a = new int* [k];
			a[0] = new int[n] { 5, 2, 8 };   // min = 2
			a[1] = new int[n] { 7, 6, 9 };   // min = 6
			a[2] = new int[n] { 4, 3, 5 };   // min = 3
			int firstMin = RowMin(a, 0, 0, n);
			int result = MaxOfRowMins(a, 1, k, n, firstMin);
			Assert::AreEqual(6, result);
			for (int i = 0; i < k; ++i)
				delete[] a[i];
			delete[] a;
		}
	};
}