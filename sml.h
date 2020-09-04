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
int matrix_get(SML_MATRIX *mat, int line, int column);
void matrix_set(SML_MATRIX *mat, int line, int column, int value);
void matrix_print(SML_MATRIX *mat);
void matrix_fill(SML_MATRIX *mat, int *array);
bool matrix_is_equal(SML_MATRIX *mat1, SML_MATRIX *mat2);

#endif
