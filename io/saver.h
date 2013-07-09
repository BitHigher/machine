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
	
	void save_matrix(double* matrix, int rows, int cols);

private:
	std::ofstream file_;
};

#endif /* IO_SAVER_H */
