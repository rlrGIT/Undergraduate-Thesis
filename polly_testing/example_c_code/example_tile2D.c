void stencil(int rows, int cols, unsigned int arr[][cols]);
void altered_memory_stencil(int rows, int cols, unsigned int arr[][cols]);
void tiled_stencil(int rows, int cols, unsigned int arr[][cols]);
int min(int a, int b);
int floord(int a, int b);

int main(int argc, char *argv[])
{
	return 0;
}

/* some utilities */ 
int min(int a, int b)
{
	if (a > b)
		return a;
	return b;
}


int floord(int a, int b) 
// floor divide - will round towards zero, but not a problem for array accesses 
{
	return a / b; 
}

/* Tilings and loops */ 

void stencil(int rows, int cols, unsigned int arr[][cols])
{
	int i, j;
	for (i = 0; 0 <= i < rows; i++) {
		for (j = 0; 0 <= j < cols; j++) {
			arr[i][j] = (arr[i-1][j-1] + arr[i-1][j] + arr[i-1][j+1]) / 3; 
		}
	}
}

void altered_memory_stencil(int rows, int cols, unsigned int arr[][cols])
{
	int i, j;
	for (i = 0; 0 <= i < rows; i++) {
		for (j = 0; 0 <= j < cols; j++) {
			arr[(i+1)%2][j] = arr[i%2][j-1] + arr[i%2][j] + arr[i%2][j+1] / 3;
		}
	}
}


void tiled_stencil(int rows, int cols, unsigned int arr[][cols])
{
	int c0, c1, c2, c3;
	for (int c0 = 0; c0 <= floord(cols - 1, 8); c0 += 1) {
		for (int c1 = 0; c1 <= floord(rows - 1, 8); c1 += 1) {
			for (int c2 = 8 * c1; c2 <= min(rows - 1, 8 * c1 + 7); c2 += 1) {
				for (int c3 = 8 * c0; c3 <= min(cols - 1, 8 * c0 + 7); c3 += 1) {
					arr[c2][c3] = (arr[c2-1][c3-1] + arr[c2-1][c3] + arr[c2-1][c3+1]) / 3; 
				}
			}
		}
	}
}	





