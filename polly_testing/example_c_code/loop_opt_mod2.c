// To do: compare value flow in these, using Polly ... this is what you did by hand

int min(int a, int b);
int max(int a, int b);

void stencil_original(int T, int N, double A[][N]);
void stencil_fake_iterator(int T, int N, double A[][N]);
void stencil_fake_iterator_useless(int T, int N, double A[][N]);
void stencil_fake_iterator_wrong(int T, int N, double A[][N]);

inline void body(int t, int i, int N, double A[][N]) {
	A[(t+1)%2][i] = A[t%2][i-1] + A[t%2][i] + A[t%2][i+1] / 3;
}


int main() {};

// some utilities for checking work
int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

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

void stencil_fake_iterator(int T, int N, double A[][N])
{
#pragma scop
	for (int t = 0; t < T; t++) {
		for (int i = 1; i < N-1; i++) {
			body(t, i, N, A);
		}
	}
#pragma endscop
}

void stencil_fake_iterator_useless(int T, int N, double A[][N])
{
#pragma scop
	for (int tb = 0; tb < (T/32); tb++) {
		for (int t = tb*32; t < min(T, 32*tb+31); t++) {  /// this and the above are just the "t" loop from earlier
			for (int ib = 0; ib < (N/32); ib++) {
				for (int i = max(1, 32*ib); i < min(N-1, 32*ib+31); i++) {   /// this and the above the old "i"
					body(t, i, N, A);
				}
			}
		}
	}
#pragma endscop
}

void stencil_fake_iterator_wrong(int T, int N, double A[][N])
{
#pragma scop
	for (int tb = 0; tb < (T/32); tb++) {
		for (int ib = 0; ib < (N/32); ib++) {
			for (int t = tb*32; t < min(T, 32*tb+31); t++) {
				for (int i = max(1, 32*ib); i < min(N-1, 32*ib+31); i++) {
					body(t, i, N, A);
				}
			}
		}
	}
#pragma endscop
}
