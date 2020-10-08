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

SML_MATRIX *matrix_init_mat(SML_MATRIX *mat, SML_MATRIX *mat_res) {
	if (!matrix_init(mat_res, mat->lines, mat->columns))
		return NULL;

	matrix_copy(mat, mat_res);

	return mat_res;
}

SML_MATRIX *matrix_init_O(SML_MATRIX *mat, int lines, int columns) {
	if (!matrix_init(mat, lines, columns))
		return NULL;

	return false;
}

SML_MATRIX *matrix_init_E(SML_MATRIX *mat, int lines, int columns) {
	if (!matrix_init(mat, lines, columns))
		return NULL;

	for (int k = 0; k < mat->lines && k < mat->columns; k++)
		matrix_set(mat, k, k, 1);

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

void matrix_copy(SML_MATRIX *mat, SML_MATRIX *mat_res) {
	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; i < mat->columns; j++)
			matrix_set(mat_res, i, j, matrix_get(mat, i, j));
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
			if (j <= i)
				j = i;
			else if (matrix_get(mat, i, j))
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

bool matrix_is_lower_unitriangular(SML_MATRIX *mat){
	if (matrix_is_square(mat) == false)
		return false;

	for (int i = 0; i < mat->lines; i++)
		for (int j = 1; j < mat->columns; j++)
			if (j < i)
				j = i;
			else if (i == j && matrix_get(mat, i, j) != 1)
				return false;
			else if (matrix_get(mat, i, j))
				return false;

	return true;
}

bool matrix_is_unitriangular(SML_MATRIX *mat) {
	if (matrix_is_upper_unitriangular(mat) || matrix_is_lower_unitriangular(mat))
		return true;

	return false;
}

bool matrix_is_stepped(SML_MATRIX *mat) {
	int index = -1;

	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			if (matrix_get(mat, i, j)) {
				if (index >= j)
					return false;
				else {
					index = j;
					j = mat->columns;
				}
			}

	return true;
}

bool matrix_is_symmetric(SML_MATRIX *mat) {
	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			if (matrix_get(mat, i, j) != matrix_get(mat, j, i))
				return false;

	return true;
}

bool matrix_is_degenerate(SML_MATRIX *mat) {
	if (!matrix_is_square(mat) || matrix_det(mat))
		return false;

	return true;
}

bool matrix_is_permutation(SML_MATRIX *mat1, SML_MATRIX *mat2) {
	SML_MATRIX tmp1, tmp2;
	bool res = false;

	if (!matrix_is_square(mat1) || !matrix_is_square(mat2))
		return res;

	matrix_mul(mat1, mat2, &tmp1);
	matrix_mul(mat2, mat1, &tmp2);

	if (matrix_is_equal(&tmp1, &tmp2))
		res = true;

	matrix_free(&tmp1);
	matrix_free(&tmp2);

	return res;
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

	if (!matrix_union(mat, mat_res) || !det)
		return false;

	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			matrix_set(mat_res, i, j, matrix_get(mat_res, i, j) / det);

	return true;
}

bool matrix_pow(SML_MATRIX *mat, SML_MATRIX *mat_res, int pow) {
	SML_MATRIX tmp;
	if (!matrix_is_square(mat))
		return false;

	matrix_init_E(&tmp, mat->lines, mat->lines);

	for (int i = 0; i < pow; i++) {
		matrix_mul(&tmp, mat, mat_res);
		matrix_copy(&tmp, mat_res);
	}

	return true;
}

bool matrix_union(SML_MATRIX *mat, SML_MATRIX *mat_res) {
	if (!matrix_is_square(mat))
		return false;

	for (int i = 0; i < mat->lines; i++)
		for (int j = 0; j < mat->columns; j++)
			matrix_set(mat_res, i, j, matrix_alg_complement(mat, j, i));

	return true;
}

bool matrix_perm(SML_MATRIX *mat, int i1, int j1, int i2, int j2) {
	double tmp = matrix_get(mat, i1, j1);

	if (i1 >= mat->lines || i2 >= mat->lines || i1 < 0 || i2 < 0 ||
			j1 >= mat->columns || j2 >= mat->columns || j1 < 0 || j2 < 0)
		return false;

	matrix_set(mat, i1, j1, matrix_get(mat, i2, j2));
	matrix_set(mat, i2, j2, tmp);

	return true;
}

void matrix_perm_lines(SML_MATRIX *mat, int line1, int line2) {
	for (int j = 0; j < mat->columns; j++)
		matrix_perm(mat, line1, j, line2, j);
}

void matrix_perm_columns(SML_MATRIX *mat, int column1, int column2) {
	for (int i = 0; i < mat->lines; i++)
		matrix_perm(mat, i, column1, i, column2);
}

void matrix_mul_line(SML_MATRIX *mat, int line, double k) {
	for (int j = 0; j < mat->columns; j++)
		matrix_set(mat, line, j, matrix_get(mat, line, j) * k);
}

void matrix_mul_column(SML_MATRIX *mat, int column, double k) {
	for (int i = 0; i < mat->lines; i++)
		matrix_set(mat, i, column, matrix_get(mat, i, column) * k);
}

void matrix_add_line(SML_MATRIX *mat, int line1, int line2, double k) {
	for (int j = 0; j < mat->columns; j++)
		matrix_set(mat, line1, j, matrix_get(mat, line1, j) + matrix_get(mat, line2, j) * k);
}

void matrix_add_column(SML_MATRIX *mat, int column1, int column2, double k) {
	for (int i = 0; i < mat->lines; i++)
		matrix_set(mat, i, column1, matrix_get(mat, i, column1) + matrix_get(mat, i, column2) * k);
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
