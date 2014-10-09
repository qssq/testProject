#ifndef _DATA_STRING_H_
#define _DATA_STRING_H_

#include <iostream>

using namespace std;

struct SparseNode
{
	int x;
	int y;
	int number;
};

const int gSparseNodeMax = 1024;

struct SparseMatrix
{
	int row;
	int column;
	int count;
	SparseNode data[gSparseNodeMax];
};

class DataString
{
public:
	DataString();
	~DataString();
	void questionAnDian();
	void sparseMatrixTranspose();
private:
	void showSparseMatrix(const SparseMatrix &sp);
};

#endif