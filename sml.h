#ifndef __SIMPLE_MATRIX_LIBRARY_H_INCLUDED__
#define __SIMPLE_MATRIX_LIBRARY_H_INCLUDED__

typedef struct {
	double *table;
	int lines;
	int columns;
} SML_MATRIX;

SML_MATRIX *matrix_init(SML_MATRIX *mat, int lines, int columns);
void matrix_free(SML_MATRIX *mat);
int matrix_get_pos(SML_MATRIX *mat, int line, int column);
int matrix_get_size(SML_MATRIX *mat);
int matrix_get_order(SML_MATRIX *mat);
double matrix_get(SML_MATRIX *mat, int line, int column);
void matrix_set(SML_MATRIX *mat, int line, int column, double value);
void matrix_print(SML_MATRIX *mat);
void matrix_fill(SML_MATRIX *mat, double *array);
void matrix_fill_rand(SML_MATRIX *mat, int min, int max);
bool matrix_is_equal(SML_MATRIX *mat1, SML_MATRIX *mat2);
bool matrix_is_square(SML_MATRIX *mat);
bool matrix_is_diagonal(SML_MATRIX *mat);
bool matrix_is_identity(SML_MATRIX *mat);
bool matrix_is_zero(SML_MATRIX *mat);
bool matrix_is_column(SML_MATRIX *mat);
bool matrix_is_line(SML_MATRIX *mat);
bool matix_is_upper_triangular(SML_MATRIX *mat);
void matrix_transp(SML_MATRIX *mat, SML_MATRIX *mat_res);
bool matrix_add(SML_MATRIX *mat1, SML_MATRIX * mat2, SML_MATRIX *mat_res);
bool matrix_diff(SML_MATRIX *mat1, SML_MATRIX *mat2, SML_MATRIX *mat_res);
void matrix_mul_num(SML_MATRIX *mat, double num, SML_MATRIX *mat_res);
bool matrix_mul(SML_MATRIX *mat1, SML_MATRIX *mat2, SML_MATRIX *mat_res);
bool matrix_get_minor(SML_MATRIX *mat, SML_MATRIX *mat_res, int line, int column);
double matrix_minor(SML_MATRIX *mat, int line, int column);
double matrix_alg_complement(SML_MATRIX *mat, int line, int column);
double matrix_det(SML_MATRIX *mat);
bool matrix_inverse(SML_MATRIX *mat, SML_MATRIX *mat_res);

#endif
