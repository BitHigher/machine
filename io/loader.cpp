#include "loader.h"
#include "../base/common.h"


Loader::Loader(const char *filename)
{
	file_.open(filename, std::fstream::in);
	ASSERT(file_.is_open());
}

Loader::~Loader()
{
	if(file_.is_open())
		file_.close();
}

void Loader::load_matrix(double* &matrix, int &rows, int &cols)
{
	ASSERT(file_.is_open());

	file_ >> rows >> cols;
	matrix = (double*)malloc(rows*cols*sizeof(double));

	for(int i = 0; i < cols; ++i)
	{
		for(int j = 0; j < rows; ++j)
		{
			file_ >> matrix[i*rows + j];
		}
	}
}

void Loader::load_vector(int* &vector, int &size)
{
	ASSERT(file_.is_open());

	file_ >> size;
	vector = (int*)malloc(size*sizeof(int));

	for(int i = 0; i < size; ++i)
		file_ >> vector[i];
}

void Loader::load_vector(double* &vector, int &size)
{
	ASSERT(file_.is_open());

	file_ >> size;
	vector = (double*)malloc(size*sizeof(double));

	for(int i = 0; i < size; ++i)
		file_ >> vector[i];
}
