/*
 * class Loader
 * 
 */

#ifndef IO_LOADER_H
#define IO_LOADER_H

#include <fstream>

class Loader
{
public:
	Loader(const char *filename);
	virtual ~Loader();

	void load_matrix(double* &matrix, int &rows, int &cols);
	void load_vector(int* &vector, int &size);
	void load_vector(double* &vector, int &size);

private:
	std::ifstream file_;
};


#endif /* IO_LOADER_H */
