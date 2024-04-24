#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {  // ++ calloc?
  int response = OK;
  if (rows > 0 && columns > 0 && result != NULL) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)malloc(sizeof(double *) * result->rows);
    for (int i = 0; i < result->rows; ++i) {
      result->matrix[i] = (double *)malloc(sizeof(double) * result->columns);
      if (result->matrix[i] == NULL) {
        response = INCORRECT_MATRIX;
        for (int j = 0; j < i; ++j) {
          free(result->matrix[j]);
        }
        free(result->matrix);
        break;
      }
    }
    for (int i = 0; i < result->rows; ++i) {
      for (int j = 0; j < result->columns; ++j) {
        result->matrix[i][j] = 0.;
      }
    }
  } else {
    response = INCORRECT_MATRIX;
  }
  return response;
}

void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; ++i) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  A->rows = 0;
  A->columns = 0;
}

int s21_is_correct(matrix_t *A) {
  int response = FAILURE;
  if (A && A->matrix && A->rows >= 1 && A->columns >= 1) response = SUCCESS;
  return response;
}

int s21_are_equal(matrix_t *A, matrix_t *B) {
  int response = SUCCESS;
  int diff = 0;
  for (int i = 0; i < A->rows && !diff; ++i) {
    for (int j = 0; j < A->columns && !diff; ++j) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
        diff = 1;
        response = FAILURE;
      }
    }
  }
  return response;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int response = SUCCESS;
  if (!s21_is_correct(A) || !s21_is_correct(B)) {
    response = FAILURE;
  } else {
    if (A->rows == B->rows && A->columns == B->columns) {
      response = s21_are_equal(A, B);
    }
  }
  return response;
}

void s21_find_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int response = OK;
  if (!s21_is_correct(A) || !s21_is_correct(B)) {
    response = INCORRECT_MATRIX;
  } else {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      s21_find_sum_matrix(A, B, result);
    } else {
      response = CALCULATION_ERROR;
    }
  }

  return response;
}

void s21_find_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int response = OK;
  if (!s21_is_correct(A) || !s21_is_correct(B)) {
    response = INCORRECT_MATRIX;
  } else {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      s21_find_sub_matrix(A, B, result);
    } else {
      response = CALCULATION_ERROR;
    }
  }
  return response;
}

void s21_find_mult_num_matrix(matrix_t *A, double number, matrix_t *result) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {  // ?
  int response = OK;
  if (s21_is_correct(A)) {
    s21_create_matrix(A->rows, A->columns, result);
    s21_find_mult_num_matrix(A, number, result);
  } else {
    response = INCORRECT_MATRIX;
  }
  return response;
}

void s21_find_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < B->columns; ++j) {
      result->matrix[i][j] = 0.;
      for (int k = 0; k < A->columns; ++k) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int response = OK;
  if (!s21_is_correct(A) || !s21_is_correct(B)) {
    response = INCORRECT_MATRIX;
  } else {
    if (A->columns == B->rows) {
      s21_create_matrix(A->rows, B->columns, result);
      s21_find_mult_matrix(A, B, result);
    } else {
      response = CALCULATION_ERROR;
    }
  }
  return response;
}

void s21_find_transpose(matrix_t *A, matrix_t *result) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int response = OK;
  if (s21_is_correct(A)) {
    s21_create_matrix(A->columns, A->rows, result);
    s21_find_transpose(A, result);
  } else {
    response = INCORRECT_MATRIX;
  }
  return response;
}

void s21_fill_minor_for_determinant(matrix_t *A, matrix_t *minor, int x) {  // ?
  for (int i = 0; i < A->rows - 1; ++i) {
    for (int j = 0; j < A->columns - 1; ++j) {
      int tmp_j = (j >= x) ? 1 : 0;
      minor->matrix[i][j] = A->matrix[i + 1][j + tmp_j];
    }
  }
}

void s21_calc_det_for_matrix_3x3_n_large(matrix_t *A, double *result) {
  matrix_t minor;
  s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
  for (int x = 0; x < A->columns; ++x) {
    s21_fill_minor_for_determinant(A, &minor, x);
    double minor_det = 0.;
    s21_determinant(&minor, &minor_det);
    *result += A->matrix[0][x] * minor_det * (x % 2 == 0 ? 1 : -1);
  }
  s21_remove_matrix(&minor);
}

int s21_determinant(matrix_t *A, double *result) {
  int response = OK;
  if (!s21_is_correct(A)) {
    response = INCORRECT_MATRIX;
  } else {
    if (A->rows == A->columns) {
      if (A->rows == 1) {
        *result = A->matrix[0][0];
      } else if (A->rows == 2) {
        *result = A->matrix[0][0] * A->matrix[1][1] -
                  A->matrix[0][1] * A->matrix[1][0];
      } else if (A->rows >= 3) {
        *result = 0.;
        s21_calc_det_for_matrix_3x3_n_large(A, result);
      }
    } else {
      response = CALCULATION_ERROR;
    }
  }
  return response;
}

void s21_fill_minor_for_complement(matrix_t *A, matrix_t *minor, int i, int j) {
  int row = 0;
  for (int k = 0; k < A->rows; ++k) {
    if (k == i) {
      continue;
    }
    int col = 0;
    for (int z = 0; z < A->columns; ++z) {
      if (z == j) {
        continue;
      }
      minor->matrix[row][col] = A->matrix[k][z];
      ++col;
    }
    ++row;
  }
}

void s21_find_complements(matrix_t *A, matrix_t *result) {
  matrix_t minor;
  s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      s21_fill_minor_for_complement(A, &minor, i, j);
      double minor_det = 0.;
      s21_determinant(&minor, &minor_det);
      int sign = (i + j) % 2 == 0 ? 1 : -1;
      result->matrix[i][j] = sign * minor_det;
    }
  }
  s21_remove_matrix(&minor);
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int response = OK;
  if (!s21_is_correct(A)) {
    response = INCORRECT_MATRIX;
  } else if (A->rows == 1) {
    response = CALCULATION_ERROR;
  } else {
    double det = 0.;
    response = s21_determinant(A, &det);
    if (!response && (fabs(det - 0) > EPS)) {
      s21_create_matrix(A->rows, A->columns, result);
      s21_find_complements(A, result);
    } else {
      response = CALCULATION_ERROR;
    }
  }
  return response;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int response = OK;
  if (A == NULL || A->matrix == NULL) {
    response = INCORRECT_MATRIX;
  } else {
    double det = 0.;
    s21_determinant(A, &det);
    if (fabs(det - 0) < EPS) {
      response = CALCULATION_ERROR;
    } else if (A->rows == 1) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = 1 / (A->matrix[0][0]);
    } else {
      matrix_t alg_comp = {0};
      s21_calc_complements(A, &alg_comp);
      matrix_t transpose_m = {0};
      s21_transpose(&alg_comp, &transpose_m);
      s21_mult_number(&transpose_m, 1. / det, result);
      s21_remove_matrix(&alg_comp);
      s21_remove_matrix(&transpose_m);
    }
  }
  return response;
}