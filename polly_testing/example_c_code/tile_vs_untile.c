#include <stdio.h>
#include <stdlib.h>

int min(int a, int b);
int floord(int a, int b);
void tiled_stencil(int row, int col, int arr[][col]);
void stencil_original(int row, int col, int arr[][col]);
void reset_mtx(int row, int col, int arr[][col]);
void print_m(int row, int col, int arr[][col]);


const int row = 15;
const int col = 15;

int main()
{
	int arr[row][col] = {1};
	reset_mtx(row, col, arr);
	printf("original matrix: \n");
	print_m(row, col, arr);

	stencil_original(row, col, arr);
	printf("Untiled code: \n");
	print_m(row, col, arr);		

	int arr1[row][col] = {1};
	reset_mtx(row, col, arr1);
	tiled_stencil(row, col, arr1);
	printf("Tiled code: \n");
	print_m(row, col, arr1);

	return 0;
}

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int floord(int a, int b) 
// floor divide - will round towards zero, but not a problem for array accesses 
{
	return a / b; 
}

void reset_mtx(int row, int col, int arr[][col])
{
	int i, j;
	for (i = 1; i < row; i++) {
		for (j = 1; j < row; j++){
			arr[i][j] = i; 
		}
	}
}

void print_m(int row, int col, int arr[][col])
{
	int i, j;
	for (i = 1; i < row; i++) {
		for (j = 1; j < col; j++) {
			printf("%d  ", arr[i][j]);
		}
		printf("%c", '\n');
	}
	printf("%c", '\n');
}

/* Tilings and loops */ 
void tiled_stencil(int row, int col, int arr[][col])
{
	int N = row;
	int T = col;

	for (int c0 = 1; c0 < floord(N - 1, 8); c0 += 1) {
		for (int c1 = 1; c1 < floord(T - 1, 8); c1 += 1) {
			for (int c2 = 8 * c1; c2 < min(T - 1, 8 * c1 + 7); c2 += 1) {
				for (int c3 = 8 * c0; c3 < min(N - 1, 8 * c0 + 7); c3 += 1) {
					arr[(c2 + 1)%2][c3] = (arr[c2%2][c3-1] + arr[c2%2][c3] + arr[c2%2][c3+1]);
				}
			}
		}
	}
}

void stencil_original(int T, int N, int arr[][N])
{
	for (int t = 0; t < T; t++) {
		for (int i = 1; i < N; i++) {
			arr[(t+1)%2][i] = (arr[t%2][i-1] + arr[t%2][i] + arr[t%2][i+1]);
		//	arr[t][i] = (arr[t][i-1] + arr[t][i] + arr[t][i+1]) / 3;
		}
	}
}


