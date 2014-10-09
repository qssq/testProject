#include "DataString.h"

DataString::DataString()
{

}

DataString::~DataString()
{

}

void DataString::questionAnDian()
{
	const int m = 3;
	const int n = 2;
	int intArray[m][n] = {3, 2, 3,
						  4, 4, 4};

	for (int i = 0; i < m; i++)
	{
		int min = intArray[i][0];
		int index = 0;
		for (int j = 0; j < n; j++)
		{
			if (min > intArray[i][j])
			{
				min = intArray[i][j];
				index = j;
			}
		}

		bool isMin = true;
		for (int j = 0; j < m; j++)
		{
			if (intArray[j][index] < min)
			{
				isMin = false;
				break;
			}
		}
		if (isMin)
		{
			cout<<"min line : "<<i<<endl;
			cout<<"min column : "<<index<<endl;
			cout<<"min number : "<<min<<endl;
		}
	}
}

void DataString::sparseMatrixTranspose()
{

}

void DataString::showSparseMatrix( const SparseMatrix &sp )
{
	for (int i = 0; i < sp.row; i++)
	{
		for (int j = 0; j < sp.column; j++)
		{
			
		}
	}
}
