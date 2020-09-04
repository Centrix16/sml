#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "sml.h"

void matrix_init(SML_MATRIX *mat, int lines, int columns) {
	mat->lines = lines;
	mat->columns = columns;
	mat->table = malloc(matrix_get_size(mat) * sizeof(int));

	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			matrix_set(mat, i, j, 0);
}

void matrix_free(SML_MATRIX *mat) {
	mat->lines = 0;
	mat->columns = 0;
	free(mat->table);
}

void matrix_resize(SML_MATRIX *mat, int lines, int columns) {
	mat->lines = lines;
	mat->columns = columns;
	mat->table = realloc(mat->table, matrix_get_size(mat));

	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			matrix_set(mat, i, j, 0);
}

int matrix_get_pos(SML_MATRIX *mat, int line, int column) {
	return mat->columns * line + column;
}

int matrix_get_size(SML_MATRIX *mat) {
	return mat->lines * mat->columns;
}

int matrix_get(SML_MATRIX *mat, int line, int column) {
	return mat->table[matrix_get_pos(mat, line, column)];
}

void matrix_set(SML_MATRIX *mat, int line, int column, int value) {
	mat->table[matrix_get_pos(mat, line, column)] = value;
}

void matrix_print(SML_MATRIX *mat) {
	for (int i = 0; i < mat->lines; i++) {
		for (int j = 0; j < mat->columns; j++)
			printf("%d ", matrix_get(mat, i, j));
		printf("\n");
	}
}

void matrix_fill(SML_MATRIX *mat, int *array) {
	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++) 
			matrix_set(mat, i, j, array[matrix_get_pos(mat, i, j)]);
}

bool matrix_is_equal(SML_MATRIX *mat1, SML_MATRIX *mat2) {
	if (mat1->lines != mat2->lines || mat1->columns != mat2->columns)
		return false;

	for (int i = 0; i < mat1->lines; i++)
		for (int j = 0; j < mat1->columns; j++)
			if (matrix_get(mat1, i, j) != matrix_get(mat2, i, j))
				return false;
}

int main() {
	SML_MATRIX mat;
	matrix_init(&mat, 2, 3);
	matrix_fill(&mat, (int []){1, 2, 3, 4, 5, 6});
	matrix_print(&mat);
	printf("test: %d\n", matrix_get_pos(&mat, 1, 2));
	matrix_resize(&mat, 3, 2);
	matrix_fill(&mat, (int []){6, 5, 4, 3, 2, 1});
	matrix_print(&mat);

	SML_MATRIX mat2;
	matrix_init(&mat2, 3, 2);
	matrix_fill(&mat2, (int []){6, 5, 4, 3, 2, 1});
	printf("test: %d\n", (int)(matrix_is_equal(&mat, &mat2) == true));
	matrix_free(&mat2);
	matrix_free(&mat);
}
