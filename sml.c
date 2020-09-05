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

/* ? */
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

int matrix_get_order(SML_MATRIX *mat) {
	if (matrix_is_square(mat))
		return mat->lines;
	else
		return -1;
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

	return true;
}

bool matrix_is_square(SML_MATRIX *mat) {
	if (mat->lines == mat->columns)
		return true;
	else
		return false;
}

bool matrix_is_diagonal(SML_MATRIX *mat) {
	if (matrix_get_order(mat) <= 0)
		return false;

	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			if (i != j && matrix_get(mat, i, j) != 0)
					return false;

	return true;
}

bool matrix_is_identity(SML_MATRIX *mat) {
	if (!matrix_is_diagonal(mat))
		return false;

	for (int i = 0; i < mat->lines; i++)
		if (matrix_get(mat, i, i) != 1)
			return false;

	return true;
}

bool matrix_is_zero(SML_MATRIX *mat) {
	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			if (matrix_get(mat, i, j) != 0)
				return false;

	return true;
}

bool matrix_is_column(SML_MATRIX *mat) {
	if (mat->columns == 1)
		return true;
	else
		return false;
}

bool matrix_is_line(SML_MATRIX *mat) {
	if (mat->lines == 1)
		return true;
	else
		return false;
}

void matrix_transp(SML_MATRIX *mat1, SML_MATRIX *mat2) {
		mat2->lines = mat1->columns;
		mat2->columns = mat1->lines;

		for (int i = 0; i < mat1->lines; i++)
			for (int j = 0; j < mat1->columns; j++)
				matrix_set(mat2, i, j, matrix_get(mat1, j, i));
}

bool matrix_add(SML_MATRIX *mat1, SML_MATRIX * mat2, SML_MATRIX *mat3) {
	matrix_init(mat3, mat1->lines, mat1->columns);

	if (mat1->lines != mat2->lines || mat1->columns != mat2->columns)
		return false;

	for (int i = 0; i < mat1->lines; i++)
		for (int j = 0; j < mat1->columns; j++)
			matrix_set(mat3, i, j, matrix_get(mat1, i, j) + matrix_get(mat2, i, j));

	return true;
}

bool matrix_diff(SML_MATRIX *mat1, SML_MATRIX *mat2, SML_MATRIX *mat3) {
	matrix_init(mat3, mat1->lines, mat1->columns);

	if (mat1->lines != mat2->lines || mat1->columns != mat2->columns)
		return false;

	for (int i = 0; i < mat1->lines; i++)
		for (int j = 0; j < mat1->columns; j++)
			matrix_set(mat3, i, j, matrix_get(mat1, i, j) - matrix_get(mat2, i, j));

	return true;
}

int main() {
	SML_MATRIX mat1, mat2, mat3;
	matrix_init(&mat1, 4, 4);
	matrix_init(&mat2, 4, 4);
	matrix_init(&mat3, 4, 4);
	matrix_fill(&mat1, (int []){
		1, 2, 3, 4,
		8, 7, 6, 5,
		9, 0, 9, 8,
		4, 5, 6, 7
	});
	matrix_fill(&mat2, (int []){
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	});
	matrix_fill(&mat3, (int []){
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	});

	matrix_print(&mat1);
	printf("order: %d\n", matrix_get_order(&mat1));
	printf("is_square: %d\n", matrix_is_square(&mat1));
	printf("is_diagonal: %d\n", matrix_is_diagonal(&mat1));
	printf("is_identity: %d\n", matrix_is_identity(&mat1));
	printf("is_zero: %d\n", matrix_is_zero(&mat1));
	printf("is_column: %d\n", matrix_is_column(&mat1));
	printf("is_line: %d\n", matrix_is_line(&mat1));

	matrix_transp(&mat1, &mat2);
	matrix_print(&mat2);

	matrix_diff(&mat1, &mat2, &mat3);
	matrix_print(&mat3);

	matrix_free(&mat1);
	matrix_free(&mat2);
	matrix_free(&mat3);
}
