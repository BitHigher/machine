#include "distance.h"
#include <pthread.h>

extern Parallel *parallel;

struct DISTANCE_THREAD_PARAM
{
	Distance *distance;
	int lstart;
	int lstop;
	int rstart;
	int rstop;
};

Distance::Distance()
{
}

Distance::Distance(HFMatrix<double> left, HFMatrix<double> right)
{
	ASSERT(left.num_rows == right.num_rows);
	left_ = left;
	right_ = right;
}

void Distance::set_left(HFMatrix<double> left)
{
	left_ = left;
}

void Distance::set_right(HFMatrix<double> right)
{
	right_ = right;
}

double Distance::distance(int i, int j)
{
	ASSERT(i >= 0 && i < left_.num_cols);
	ASSERT(j >= 0 && j < right_.num_cols);
	ASSERT(left_.num_rows == right_.num_rows);

	return distance(left_.get_column(i),
					right_.get_column(j),
					left_.num_rows);
}

void* Distance::run_distance_thread(void *p)
{
	DISTANCE_THREAD_PARAM *param = (DISTANCE_THREAD_PARAM*)p;
	
	Distance *distance = param->distance;
	int lstart = param->lstart;
	int lstop = param->lstop;
	int rstart = param->rstart;
	int rstop = param->rstop;

	printf("rstart: %d rstop: %d\n", rstart, rstop);

	for(int i = lstart; i < lstop; ++i)
	{
		for(int j = rstart; j < rstop; ++j)
		{
			distance->result_(i,j) = distance->distance(i, j);
		}
	}

	return NULL;
}

void Distance::distances()
{
	int num_threads = parallel->get_num_threads();
	ASSERT(num_threads > 0);
		
	ASSERT(left_.num_rows == right_.num_rows);
	ASSERT(left_.num_cols > 0 && right_.num_cols > 0);

	if(left_.num_cols != result_.num_rows ||
		right_.num_cols != result_.num_cols)
	{
		result_.resize(left_.num_cols, right_.num_cols);
	}
	
	if(num_threads < 2)
	{
		DISTANCE_THREAD_PARAM param;
		param.distance = this;
		param.lstart = 0;
		param.lstop = left_.num_cols;
		param.rstart = 0;
		param.rstop = right_.num_cols;
		
		run_distance_thread((void*)&param);
	}
	else
	{
		pthread_t *threads = (pthread_t*)malloc((num_threads-1)*
												sizeof(pthread_t));

		DISTANCE_THREAD_PARAM *params = (DISTANCE_THREAD_PARAM*)malloc(
											num_threads * 
											sizeof(DISTANCE_THREAD_PARAM));
		// TODO split left or right ?
		// split right only
		int num_cols = right_.num_cols;
		int step = num_cols/num_threads;
		int t = 0;

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

		for(t = 0; t < num_threads-1; ++t)
		{
			params[t].distance = this;
			params[t].lstart = 0;
			params[t].lstop = left_.num_cols;
			params[t].rstart = step*t;
			params[t].rstop = step*(t+1);

			pthread_create(threads+t, &attr, 
							run_distance_thread,
							(void*)&params[t]);
		}

		params[t].distance = this;
		params[t].lstart = 0;
		params[t].lstop = left_.num_cols;
		params[t].rstart = step*t;
		params[t].rstop = right_.num_cols;

		run_distance_thread(params + t);

		for(t = 0; t < num_threads-1; ++t)
			pthread_join(threads[t], NULL);

		pthread_attr_destroy(&attr);

		free(params);
		free(threads);	
	}
}
