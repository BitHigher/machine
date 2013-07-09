#include "hfmatrix.h"
#include "../base/common.h"
#include "../math/hfmath.h"

#include <stdlib.h>
#include <lapacke.h>
#include <cblas.h>


/** test print matrix **/
void print_matrix(const char *desc, int m, int n, double *a, int lda)
{
	int i, j;
	printf("\n %s\n", desc);
	for(i = 0; i < m; ++i)
	{
		for(j = 0; j < n; ++j)
			printf(" %6.6f", a[i+j*lda]);
		printf("\n");
	}
}

template<class T>
HFMatrix<T>::HFMatrix()
: matrix(NULL), num_rows(0), num_cols(0)
{
}

template<class T>
HFMatrix<T>::HFMatrix(T *m, int nrows, int ncols)
: matrix(m), num_rows(nrows), num_cols(ncols)
{
}

template<class T>
void HFMatrix<T>::save(Saver &saver)
{
	saver.save_matrix(matrix, num_rows, num_cols);
}

template<class T>
void HFMatrix<T>::load(Loader &loader)
{
	loader.load_matrix(matrix, num_rows, num_cols);
}

template<class T>
T* HFMatrix<T>::get_column(int index)
{
	ASSERT(index >= 0 && index < num_cols);
	return matrix+(index*num_rows);
}

/*
 * pseudo inverse of matrix 
 */
template<class T>
double* HFMatrix<T>::pinv(double *matrix, int rows, int cols)
{
	lapack_int m, n, lda, ldu, ldvt, info;
	char jobu = 'A';
	char jobvt = 'A';
	m = rows;
	n = cols;
	lda = rows;
	ldu = rows;
	ldvt = cols;
	int ssize = HFMath::min(m, n);

	double *s = (double*)malloc(sizeof(double)*ssize);
	double *u = (double*)malloc(sizeof(double)*m*m);
	double *vt = (double*)malloc(sizeof(double)*n*n);
	double *sb = (double*)malloc(sizeof(double)*(ssize-1));

	info = LAPACKE_dgesvd(LAPACK_COL_MAJOR, jobu, jobvt, m, n, 
						matrix, lda, s, u, ldu, vt, ldvt, sb);

	ASSERT(info == 0);

	print_matrix("Singular values", 1, n, s, 1);
	print_matrix("Left singular vectors(stored columnwise)", m, n, u, ldu);
	print_matrix("Left singular vectors(stored rowwise)", n, n, vt, ldvt);



	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < ssize; ++j)
			vt[i*n+j] = vt[i*n+j]/s[j];
	
	}

	double *result = (double*)malloc(m*n*sizeof(double));
	cblas_dgemm(CblasColMajor, CblasTrans, CblasTrans, n, m,
				n, 1.0, vt, ldvt, u, ldu, 0, result, n);

	

	free(s);
	free(u);
	free(vt);
	free(sb);

	return result;
}

template class HFMatrix<double>;
