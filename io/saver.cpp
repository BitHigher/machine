#include "saver.h"
#include "../base/common.h"


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
			file_ << matrix[i*cols+j] << ' ';
		}
		file_ << '\n';
	}
}
