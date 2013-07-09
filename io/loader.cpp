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
	matrix = new double[rows*cols];

	for(int i = 0; i < cols; ++i)
	{
		for(int j = 0; j < rows; ++j)
		{
			file_ >> matrix[i*rows + j];
		}
	}
}
