
BASE_INCLUDE = -I ../code/ -I ../code/include

ifdef D_COMBINE_TYPE
	COMBINE_TYPE = $(D_COMBINE_TYPE)
else
	COMBINE_TYPE = INT
endif

ifdef D_OPTIMIZE
	OPTIMIZE = $(D_OPTIMIZE)
else
	OPTIMIZE = 0
endif

.PHONY: all clean

all: combine_$(COMBINE_TYPE)_$(OPTIMIZE)

combine_$(COMBINE_TYPE)_$(OPTIMIZE): combine_$(COMBINE_TYPE)_$(OPTIMIZE).o vec_$(COMBINE_TYPE)_$(OPTIMIZE).o
	gcc -o combine_$(COMBINE_TYPE)_$(OPTIMIZE) combine_$(COMBINE_TYPE)_$(OPTIMIZE).o vec_$(COMBINE_TYPE)_$(OPTIMIZE).o

combine_$(COMBINE_TYPE)_$(OPTIMIZE).o: combine.c
	gcc -c combine.c -o combine_$(COMBINE_TYPE)_$(OPTIMIZE).o $(BASE_INCLUDE) -I ../code/opt -D$(COMBINE_TYPE) -O$(OPTIMIZE)

vec_$(COMBINE_TYPE)_$(OPTIMIZE).o: ../code/opt/vec.c
	gcc -c ../code/opt/vec.c -o vec_$(COMBINE_TYPE)_$(OPTIMIZE).o $(BASE_INCLUDE) -D$(COMBINE_TYPE) -O$(OPTIMIZE)

clean:
	rm -f *.o combine_*