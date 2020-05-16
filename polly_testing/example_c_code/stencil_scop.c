
void stencil_original(int T, int N, double A[][N])
{
#pragma scop
	for (int t = 0; t < T; t++) {
		for (int i = 1; i < N-1; i++) {
			A[(t+1)%2][i] = A[t%2][i-1] + A[t%2][i] + A[t%2][i+1] / 3;
		}
	}
#pragma endscop
}

