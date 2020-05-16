//#include <stdio.h>
//#include <stdlib.h>

void reset_mtx(int row, int col, unsigned int arr[][col]);
void stencil(int row, int col, unsigned int arr[][col]);

const int row = 1000;
const int col = 1000;

int main()
{
	unsigned int arr[row][col];
	reset_mtx(row, col, arr);
	stencil(row, col, arr);
	return 0;
}

void reset_mtx(int row, int col, unsigned int arr[][col])
{
	int i, j;
	for (i = 1; i < row; i++) {
		for (j = 1; j < row; j++){
			arr[i][j] = 500*(i+j); 
		}
	}
}

void stencil(int row, int col, unsigned int arr[][col])
{
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			arr[i][j] = (arr[i-1][j-1] + arr[i-1][j] + arr[i-1][j+1]) / 3;
		}
	}
}
