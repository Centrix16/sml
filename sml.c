#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "sml.h"

SML_MATRIX *matrix_init(SML_MATRIX *mat, int lines, int columns) {
	if (lines <= 0 || columns <= 0)
		return NULL;

	mat->lines = lines;
	mat->columns = columns;
	mat->table = malloc(matrix_get_size(mat) * sizeof(double));

	if (mat->table == NULL)
		return NULL;

	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			matrix_set(mat, i, j, 0.);

	return mat;
}

void matrix_free(SML_MATRIX *mat) {
	mat->lines = 0;
	mat->columns = 0;
	free(mat->table);
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

double matrix_get(SML_MATRIX *mat, int line, int column) {
	return mat->table[matrix_get_pos(mat, line, column)];
}

void matrix_set(SML_MATRIX *mat, int line, int column, double value) {
	mat->table[matrix_get_pos(mat, line, column)] = value;
}

void matrix_print(SML_MATRIX *mat) {
	for (int i = 0; i < mat->lines; i++) {
		for (int j = 0; j < mat->columns; j++)
			printf("%g ", matrix_get(mat, i, j));
		printf("\n");
	}
}

void matrix_fill(SML_MATRIX *mat, double *array) {
	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++) 
			matrix_set(mat, i, j, array[matrix_get_pos(mat, i, j)]);
}

void matrix_fill_rand(SML_MATRIX *mat, int min, int max) {
	srand(time(NULL));

	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			matrix_set(mat, i, j, rand() % (max - min + 1) + min);
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

bool matrix_is_upper_triangular(SML_MATRIX *mat){
	if (matrix_is_square(mat) == false)
		return false;

	for (int i = 1; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			if (j >= i) {
				i++;
				j = 0;
			} else if (matrix_get(mat, i, j))
				return false;

	return true;
}

bool matrix_is_lower_triangular(SML_MATRIX *mat){
	if (matrix_is_square(mat) == false)
		return false;

	for (int i = 0; i < mat->lines; i++)
		for (int j = 1; j < mat->columns; j++)
			if (j <= i) {
				j = i;
			} else if (matrix_get(mat, i, j))
				return false;

	return true;
}

bool matrix_is_triangular(SML_MATRIX *mat) {
	if (matrix_is_upper_triangular(mat) || matrix_is_lower_triangular(mat))
		return true;

	return false;
}

bool matrix_is_upper_unitriangular(SML_MATRIX *mat){
	if (matrix_is_square(mat) == false)
		return false;

	for (int i = 1; i < mat->lines; i++)
			for (int j = 0; j < mat->columns; j++)
				if (j > i) {
					i++;
					j = 0;
				} else if (i == j && matrix_get(mat, i, j) != 1)
					return false;
				else if (matrix_get(mat, i, j))
					return false;

	return true;
}

void matrix_transp(SML_MATRIX *mat, SML_MATRIX *mat_res) {
		mat_res->lines = mat->columns;
		mat_res->columns = mat->lines;

		for (int i = 0; i < mat->lines; i++)
			for (int j = 0; j < mat->columns; j++)
				matrix_set(mat_res, i, j, matrix_get(mat, j, i));
}

bool matrix_add(SML_MATRIX *mat1, SML_MATRIX * mat2, SML_MATRIX *mat_res) {
	matrix_init(mat_res, mat1->lines, mat1->columns);

	if (mat1->lines != mat2->lines || mat1->columns != mat2->columns)
		return false;

	for (int i = 0; i < mat1->lines; i++)
		for (int j = 0; j < mat1->columns; j++)
			matrix_set(mat_res, i, j, matrix_get(mat1, i, j) + matrix_get(mat2, i, j));

	return true;
}

bool matrix_diff(SML_MATRIX *mat1, SML_MATRIX *mat2, SML_MATRIX *mat_res) {
	matrix_init(mat_res, mat1->lines, mat1->columns);

	if (mat1->lines != mat2->lines || mat1->columns != mat2->columns)
		return false;

	for (int i = 0; i < mat1->lines; i++)
		for (int j = 0; j < mat1->columns; j++)
			matrix_set(mat_res, i, j, matrix_get(mat1, i, j) - matrix_get(mat2, i, j));

	return true;
}

void matrix_mul_num(SML_MATRIX *mat, double num, SML_MATRIX *mat_res) {
	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			matrix_set(mat_res, i, j, matrix_get(mat, i, j) * num);
}

bool matrix_mul(SML_MATRIX *mat1, SML_MATRIX *mat2, SML_MATRIX *mat_res) {
	matrix_init(mat_res, mat1->lines, mat2->columns);

	if (mat1->columns != mat2->lines)
		return false;

	for (int i = 0; i < mat_res->lines; i++)
		for (int j = 0; j < mat_res->columns; j++)
			for (int k = 0; k < mat1->columns; k++)
				matrix_set(mat_res, i, j, matrix_get(mat_res, i, j) + matrix_get(mat1, i, k) * matrix_get(mat2, k, j));

	return true;
}

bool matrix_get_minor(SML_MATRIX *mat, SML_MATRIX *mat_res, int line, int column) {
	if (mat->lines <= 1 || mat->columns <= 1 || !matrix_is_square(mat) || line < 0 || column < 0)
			return false;

	matrix_init(mat_res, mat->lines - 1, mat->columns -1);

	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			if (i < line && j < column)
				matrix_set(mat_res, i, j, matrix_get(mat, i, j));
			else if (i < line && j > column)
				matrix_set(mat_res, i, j - 1, matrix_get(mat, i, j));
			else if (i > line && j < column)
				matrix_set(mat_res, i - 1, j, matrix_get(mat, i, j));
			else if (i > line && j > column)
				matrix_set(mat_res, i - 1, j - 1, matrix_get(mat, i, j));

	return true;
}

double matrix_minor(SML_MATRIX *mat, int line, int column) {
	SML_MATRIX tmp;
	double res = 0;

	matrix_get_minor(mat, &tmp, line, column);

	res = matrix_det(&tmp);

	matrix_free(&tmp);

	return res;
}

double matrix_alg_complement(SML_MATRIX *mat, int line, int column) {
	return matrix_minor(mat, line, column) * pow(-1, line + column);
}

double matrix_det(SML_MATRIX *mat) {
	double det = 0.;

	if (matrix_get_order(mat) == -1)
		return 0;
	else if (matrix_get_order(mat) == 1)
		return matrix_get(mat, 0, 0);
	else
		for (int j = 0, i = 0; j < mat->columns; j++)
			det += matrix_get(mat, i, j) * matrix_alg_complement(mat, i, j);

	return det;
}

bool matrix_inverse(SML_MATRIX *mat, SML_MATRIX *mat_res) {
	double det = matrix_det(mat);

	if (det == 0)
		return false;

	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			matrix_set(mat_res, i, j, matrix_alg_complement(mat, j, i) / det);

	return true;
}



int main() {
	SML_MATRIX mat1, mat2;
	matrix_init(&mat1, 4, 4);
	matrix_fill(&mat1, (double []) {
		1., 2., 0., -1.,
		3., 1., 4., 1.,
		-2., 3., 0., 1.,
		-1., -3., 2., 1.
	});
	matrix_init(&mat2, 4, 4);

	// matrix_fill_rand(&mat1, 1, 5);

	matrix_inverse(&mat1, &mat2);

	matrix_print(&mat2);

	matrix_free(&mat1);
	matrix_free(&mat2);
}
