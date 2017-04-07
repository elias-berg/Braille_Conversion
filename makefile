# Braille Project Makefile
# Elias Berg
# History:
#   1/20/15 - Recreated makefile with tougher compilation flags.
#   1/24/15 - Added main, parser, and reading list to makefile. Queue removed.
#   2/1/15  - Accomodated new file structure to makefile.
#   4/1/15  - Removed encoder associated files

SRC_PATH=./src
OUT_PATH=./bin
FILES=util.c dictionary.c parser.c reading_list.c main.c
SOURCES=$(FILES:%.c=$(SRC_PATH)/%.c)

CC=gcc
CFLAGS=-Wall -ansi -pedantic -g

build:
	${CC} ${CFLAGS} -I${SRC_PATH} ${SOURCES} -o ${OUT_PATH}/translate.exe

########################################################################## TESTS
TEST_PATH=./tests

tests:	util
	${CC} ${CFLAGS} -I${SRC_PATH} util.o ${TEST_PATH}/dictionary_test.c -o ${OUT_PATH}/dict_test.exe
	${CC} ${CFLAGS} -I${SRC_PATH} util.o ${TEST_PATH}/encoder_test.c -o ${OUT_PATH}/encoder_test.exe
	rm util.o

util:
	${CC} ${CFLAGS} -I${SRC_PATH} ${SRC_PATH}/util.c -c
