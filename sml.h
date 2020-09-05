#ifndef __SIMPLE_MATRIX_LIBRARY_H_INCLUDED__
#define __SIMPLE_MATRIX_LIBRARY_H_INCLUDED__

typedef struct {
	int *table;
	int lines;
	int columns;
} SML_MATRIX;

void matrix_init(SML_MATRIX *mat, int lines, int columns);
void matrix_free(SML_MATRIX *mat);
void matrix_resize(SML_MATRIX *mat, int lines, int columns);
int matrix_get_pos(SML_MATRIX *mat, int line, int column);
int matrix_get_size(SML_MATRIX *mat);
int matrix_get_order(SML_MATRIX *mat);
int matrix_get(SML_MATRIX *mat, int line, int column);
void matrix_set(SML_MATRIX *mat, int line, int column, int value);
void matrix_print(SML_MATRIX *mat);
void matrix_fill(SML_MATRIX *mat, int *array);
bool matrix_is_equal(SML_MATRIX *mat1, SML_MATRIX *mat2);
bool matrix_is_square(SML_MATRIX *mat);
bool matrix_is_diagonal(SML_MATRIX *mat);
bool matrix_is_identity(SML_MATRIX *mat);
bool matrix_is_zero(SML_MATRIX *mat);
bool matrix_is_column(SML_MATRIX *mat);
bool matrix_is_line(SML_MATRIX *mat);
void matrix_transp(SML_MATRIX *mat1, SML_MATRIX *mat2);
bool matrix_add(SML_MATRIX *mat1, SML_MATRIX * mat2, SML_MATRIX *mat3);
bool matrix_diff(SML_MATRIX *mat1, SML_MATRIX *mat2, SML_MATRIX *mat3);
void matrix_mul_num(SML_MATRIX *mat1, int num, SML_MATRIX *mat2);
bool matrix_mul(SML_MATRIX *mat1, SML_MATRIX *mat2, SML_MATRIX *mat3);

#endif
