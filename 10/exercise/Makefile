include ../../common.mk

CSAPP_DIR 	= ../../code
SRC_DIR 	= .
TARGETS 	= 10_2 10_3 10_4 10_5
CFLAGS 		= -I $(CSAPP_DIR)/include

.PHONY: all clean prepare

all: prepare $(TARGETS)

prepare:
	[ -e $(TARGET_DIR) ] || ( mkdir -p $(TARGET_DIR) && cp foobar.txt $(TARGET_DIR) )

%: $(SRC_DIR)/%.c $(TARGET_DIR)/csapp.o
	gcc -o $(TARGET_DIR)/$@ $^ -lpthread $(CFLAGS)

$(TARGET_DIR)/csapp.o: $(CSAPP_DIR)/src/csapp.c
	gcc -c -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(TARGET_DIR)