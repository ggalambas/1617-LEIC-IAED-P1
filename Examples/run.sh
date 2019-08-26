#!/bin/bash  

gcc -o bla $1 -Wall
shift
for arg in "$@"
do
	echo ""
  	echo "Running $arg"
  	time ./bla < "${arg%.*}".in > "${arg%.*}".out.bla
  	diff -q "${arg%.*}".out "${arg%.*}".out.bla
done

rm *.bla
rm bla
