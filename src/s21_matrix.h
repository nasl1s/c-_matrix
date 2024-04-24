#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

#define EPS 1e-6

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int s21_is_correct(matrix_t *A);
int s21_are_equal(matrix_t *A, matrix_t *B);
void s21_find_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
void s21_find_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
void s21_find_mult_num_matrix(matrix_t *A, double number, matrix_t *result);
void s21_find_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
void s21_find_transpose(matrix_t *A, matrix_t *result);
void s21_fill_minor_for_determinant(matrix_t *A, matrix_t *minor, int x);
void s21_calc_det_for_matrix_3x3_n_large(matrix_t *A, double *result);
void s21_fill_minor_for_complement(matrix_t *A, matrix_t *minor, int i, int j);
void s21_find_complements(matrix_t *A, matrix_t *result);

#endif