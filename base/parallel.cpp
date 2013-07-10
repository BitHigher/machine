#include "common.h"
#include "parallel.h"

#if defined(LINUX)
#include <unistd.h>
#endif

int Parallel::get_num_cpus() const
{
#if defined(LINUX) && defined(_SC_NPROCESSORS_ONLN)
	return sysconf(_SC_NPROCESSORS_ONLN);
#endif
	return 1;
}

void Parallel::set_num_threads(int n)
{
#ifndef HAVE_PTHREAD
	ASSERT(n == 1)
#endif
	num_threads_ = n;
}

int Parallel::get_num_threads() const
{
	return num_threads_;
}
