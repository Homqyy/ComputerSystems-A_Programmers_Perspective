This directory contains code and the data that can generate the
code profiling results of CS:APP3e Section 5.14.

Files:

options.{c,h}: Library code for processing commandline options
dictionary.c: The full dictionary code, with all of the variants described

shakespeare.txt: The complete works of Shakespeare, as a single text file.

Makefile: Running "make all" creates two tables:
	  stable1.txt: Profiling the generation of 1-gram statistics
	  stable2.txt: Profiling the generation of 2-gram statistics

format.pl: Used to convert the gprof outputs into tabular form