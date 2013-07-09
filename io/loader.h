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

	void load_matrix(double* &vector, int &rows, int &cols);

private:
	std::ifstream file_;
};


#endif /* IO_LOADER_H */
