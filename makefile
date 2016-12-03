hw: hw
	gcc -fopenmp -fno-exceptions hw.cc -o hw
clean: 
	rm -f *.o
