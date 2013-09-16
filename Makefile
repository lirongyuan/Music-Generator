
all: test_mysort simple-gen freq2wav test_bits

test_mysort: mysort.c test_mysort.c
	gcc -g -o test_mysort mysort.c test_mysort.c

simple-gen: simple-gen.c
	gcc -g -o simple-gen -g simple-gen.c -lm

freq2wav: freq2wav.c
	gcc -g -o freq2wav freq2wav.c -lm

test_bits: test_bits.c bits.c
	gcc -g -o test_bits test_bits.c bits.c

clean:
	rm -f simple-gen test_mysort freq2wav test_bits core *.out total.txt *~




