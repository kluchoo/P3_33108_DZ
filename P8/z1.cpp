#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <cassert>
#include <ctime>
#include <omp.h>

#define MATRIX_H 30000
#define MATRIX_W 30000
#define VECTOR_S 30000
#define MULTIPLY_ITER 5

int main()
{
  srand(time(nullptr));

  assert(MATRIX_W == VECTOR_S);

  uint16_t **matrix = new uint16_t *[MATRIX_H];
  for (int i = 0; i < MATRIX_H; i++)
  {
    matrix[i] = new uint16_t[MATRIX_W];
  }

  uint16_t *vector = new uint16_t[VECTOR_S];
  uint16_t *result = new uint16_t[MATRIX_H];

  auto start_fill = std::chrono::high_resolution_clock::now();
#pragma omp parallel for schedule(static)
  for (int i = 0; i < MATRIX_H; i++)
  {
    for (int k = 0; k < MATRIX_W; k++)
    {
      matrix[i][k] = rand() % 100;
    }
  }
#pragma omp parallel for schedule(static)
  for (int i = 0; i < VECTOR_S; i++)
  {
    vector[i] = rand() % 100;
  }
  auto end_fill = std::chrono::high_resolution_clock::now();
  printf("Czas wypełniania danych (równolegle): %llu ms\n",
         std::chrono::duration_cast<std::chrono::milliseconds>(
             end_fill - start_fill)
             .count());

  auto start_par = std::chrono::high_resolution_clock::now();
  for (int iter = 0; iter < MULTIPLY_ITER; iter++)
  {
#pragma omp parallel for schedule(static)
    for (int i = 0; i < MATRIX_H; i++)
    {
      result[i] = 0;
    }
#pragma omp parallel for schedule(static)
    for (int i = 0; i < MATRIX_H; i++)
    {
      for (int k = 0; k < MATRIX_W; k++)
      {
        result[i] += matrix[i][k] * vector[k];
      }
    }
  }
  auto end_par = std::chrono::high_resolution_clock::now();
  printf("Czas mnożenia równoległego (5 razy): %llu ms\n",
         std::chrono::duration_cast<std::chrono::milliseconds>(
             end_par - start_par)
             .count());

  delete[] vector;
  delete[] result;
  for (int i = 0; i < MATRIX_H; i++)
  {
    delete[] matrix[i];
  }
  delete[] matrix;
  return 0;
}
