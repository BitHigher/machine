#ifndef BASE_PARALLEL_H
#define BASE_PARALLEL_H

/**
 * Manage parallel of computing such threads.
 *
 *
 */

class Parallel
{
public:
	int get_num_cpus() const;
	
	int get_num_threads() const;
	void set_num_threads(int n);

private:
	int num_threads_;

};

#endif /* BASE_PARALLEL_H */
