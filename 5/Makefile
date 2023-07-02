
BASE_INCLUDE = -I ../code/ -I ../code/include

ifdef D_TYPE
	COMBINE_TYPE = $(D_TYPE)
else
	COMBINE_TYPE = INT
endif

ifdef D_OPERATION
	OPERATION = $(D_OPERATION)
else
	OPERATION = PLUS
endif

ifdef D_OPTIMIZE
	OPTIMIZE = $(D_OPTIMIZE)
else
	OPTIMIZE = 0
endif

CFLAGS += -D$(COMBINE_TYPE) -D$(OPERATION) -O$(OPTIMIZE) -g
SUFFIX = $(COMBINE_TYPE)_$(OPERATION)_$(OPTIMIZE)

.PHONY: all clean

all: combine_$(SUFFIX)

combine_$(SUFFIX): combine_$(SUFFIX).o vec_$(SUFFIX).o
	gcc -o combine_$(SUFFIX) combine_$(SUFFIX).o vec_$(SUFFIX).o

combine_$(SUFFIX).o: combine.c
	gcc -c combine.c -o combine_$(SUFFIX).o $(BASE_INCLUDE) -I ../code/opt $(CFLAGS)
	gcc -c combine.c -o combine_$(SUFFIX).S -S $(BASE_INCLUDE) -I ../code/opt $(CFLAGS)

vec_$(SUFFIX).o: ../code/opt/vec.c
	gcc -c ../code/opt/vec.c -o vec_$(SUFFIX).o $(BASE_INCLUDE) $(CFLAGS)

clean:
	rm -f *.o combine_*