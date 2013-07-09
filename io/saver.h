/*
 * class Saver
 *
 */

#ifndef IO_SAVER_H
#define IO_SAVER_H

#include <fstream>

class Saver
{
public:
	Saver(const char *filename);
	virtual ~Saver();
	
	void save_matrix(double *matrix, int rows, int cols);
	void save_vector(double *vector, int size);
	void save_vector(int *vector, int size);

private:
	std::ofstream file_;
};

#endif /* IO_SAVER_H */
