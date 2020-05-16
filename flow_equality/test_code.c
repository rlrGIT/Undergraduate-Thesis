#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void reset_mtx(int row, int col, unsigned int arr[][col]);
void stencil(int row, int col, unsigned int arr[][col]);
void stencil_mod(int row, int col, unsigned int arr[][col]);
void stencil_mod_no_minus(int row, int col, unsigned int arr[][col]);
void print_m(int row, int col, unsigned int arr[][col]);
bool mtx_cmp(int row, int col, unsigned int a[][col], unsigned int b[][col]);


const int row = 10;
const int col = 10;

int main()
{
	unsigned int arr[row][col] = {0};
	reset_mtx(row, col, arr);
	printf("original: \n");
	print_m(row, col, arr);

	stencil(row, col, arr);
	printf("stenciled: \n");
	print_m(row, col, arr);		

	reset_mtx(row, col, arr);
	stencil_mod(row, col, arr);
	printf("stencil_mod: \n");
	print_m(row, col, arr);

	return 0;
}

bool mtx_cmp(int row, int col, unsigned int arr1[][col], unsigned int arr2[][col])
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			if (arr1[i][j] != arr2[i][j])
				return false;
		}
	}
	return true;
}

void reset_mtx(int row, int col, unsigned int arr[][col])
{
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < row; j++){
			arr[i][j] = i+j; 
		}
	}
}

void stencil(int row, int col, unsigned int arr[][col])
{
	int i, j;
	for (i = 1; i < row; i++) {
		for (j = 1; j < col - 1; j++) {
			arr[i+1][j] = (arr[i][j-1] + arr[i][j] + arr[i][j+1]) / 3;
		}
	}
}

void stencil_mod(int row, int col, unsigned int arr[][col])
{
	int i, j;
	for (i = 1; i < row - 1; i++) {

	for (int c0 = 0; c0 <= floord(N - 1, 8); c0 += 1)
		  for (int c1 = 0; c1 <= floord(T - 1, 8); c1 += 1)
			for (int c2 = 8 * c1; c2 <= min(T - 1, 8 * c1 + 7); c2 += 1)
      for (int c3 = 8 * c0; c3 <= min(N - 1, 8 * c0 + 7); c3 += 1)

        yield(c2, c3)
          for (a, b)
            A[a + 1, b] = (A[a][b-1] + A[a][b] + A[a][b+1]) / 3;
		for (j = 1; j < col - 1; j++) {
			arr[(i+1)%2][j] = (arr[i%2][j-1] + arr[i%2][j] + arr[i%2][j+1]) / 3;
		}
	}
}

void print_m(int row, int col, unsigned int arr[][col])
{
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%u  ", arr[i][j]);
		}
		printf("%c", '\n');
	}
	printf("%c", '\n');
}
