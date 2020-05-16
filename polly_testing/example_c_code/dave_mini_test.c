// Trying to distinguish memory-based vs. value-based deps in output of -polly-dependences
/*  
    clang -O3 -S -emit-llvm dave_mini_test.c -o dave_mini_test.s && opt -S -polly-canonicalize dave_mini_test.s > dave_mini_test.preopt.ll && opt -polly-dependences -analyze dave_mini_test.preopt.ll -polly-process-unprofitable > dave_mini_deps-mem.txt
    clang -O3 -S -emit-llvm dave_mini_test.c -o dave_mini_test.s && opt -S -polly-canonicalize dave_mini_test.s > dave_mini_test.preopt.ll && opt -polly-dependences -analyze dave_mini_test.preopt.ll -polly-process-unprofitable -polly-dependences-analysis-type=memory-based > dave_mini_deps-val.txt
    diff dave_mini_deps-mem.txt dave_mini_deps-val.txt

 */

double sample(double A[][10], int N)
{
#pragma scop
	double sum=0;
	double tmp[10];
	for (int i=0; i<N; i++) {
		for (int j=0;j<10; j++) {
			tmp[j] = A[i][j]-sum;
		}
		sum = sum/2;
		for (int j=0;j<10; j++) {
			sum = sum + tmp[j];	// no data-flow to tmp execpt from same i,j (mem. from prev. i too)
		}
	}
	return sum;
#pragma endscop
}

