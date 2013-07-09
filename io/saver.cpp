#include "saver.h"
#include "../base/common.h"

#include <iostream>

Saver::Saver(const char *filename)
{
	file_.open(filename, std::fstream::out);
	ASSERT(file_.is_open());
}

Saver::~Saver()
{
	if(file_.is_open())
		file_.close();
}

void Saver::save_matrix(double *matrix, int rows, int cols)
{
	ASSERT(file_.is_open());

	file_ << rows << ' ' << cols << '\n';

	for(int i = 0; i < cols; ++i)
	{
		for(int j = 0; j < rows; ++j)
		{
			file_ << matrix[i*rows+j] << ' ';
		}
		file_ << '\n';
	}
}

void Saver::save_vector(double *vector, int size)
{
	ASSERT(file_.is_open());
	
	file_ << size << '\n';
	for(int i = 0; i < size; ++i)
		file_ << vector[i] << ' ';
}

void Saver::save_vector(int *vector, int size)
{
	ASSERT(file_.is_open());
	
	file_ << size << '\n';
	for(int i = 0; i < size; ++i)
		file_ << vector[i] << ' ';
}
