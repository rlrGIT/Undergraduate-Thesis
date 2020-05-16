#!/bin/bash

echo "Hi Dave, just use <loop_opt_mod2.c> as input for the next prompt.\n" >&2 
echo "To view Polly representations of SCoP's, see the scops.out file" >&2 
echo "To dependencies stored in deps.out and lexically analyzed SCoP's in detected.out"  >&2 

echo "Enter C source code: " >&2
read FILENAME

#convert source to llvm-ir
clang -O1 -S -emit-llvm $FILENAME -o source_conversion.s
 
# unclear about the usage of -O3 for opt, REQUIRED for clang ->llvm ir conversion
#opt needs code in a canonical form - convert it to such (still llvm-ir)
opt -S -polly-canonicalize source_conversion.s > source_code.preopt.ll
#opt -S -polly-dependences-analysis-type=memory-based source_code.preopt.ll > target.ll

#optional info:

#opt -polly-ast -analyze -q source_code.preopt.ll -polly-process-unprofitable > $SCOPS
#opt -view-scops -disable-output source_code.preopt.ll
#opt -view-scops-only -disable-output source_code.preopt.ll

# -analyze no optimization, just analysis
# note that -polly-process-unprofitable will cause opt to also evaluate dependencies that are unlikely to benefit
# from optimization

# show detected scops from source code 
opt -polly-ast -analyze -q source_code.preopt.ll -polly-process-unprofitable > detected.out

# generate polyhedral represenations of scops 
#opt -polly-scops -analyze source_code.preopt.ll -polly-process-unprofitable > scops.out

# generate analysis for scop dependencies
# attempted to use with "value-based as Tobias suggested, but this did not work as expected
opt -polly-dependences -polly-dependences-analysis-type="memory-based" -analyze source_code.preopt.ll -polly-process-unprofitable > deps.out

# useless so far
#opt -polly-ast-print-accesses -analyze source_code.preopt.ll -polly-process-unprofitable 

#opt -polly-scops -analyze source_code.preopt.ll -polly-process-unprofitable > scops.out
#opt -polly-dependences -analyze source_code.preopt.ll -polly-process-unprofitable > deps.out
#opt -polly-ast-print-accesses -show source_code.preopt.ll -polly-process-unprofitable > maybe.out

#cat target.ll
cat detected.out
cat deps.out

echo '\n' >&2

#rm *.ll *.s

echo "\nDone.\n" >&2
