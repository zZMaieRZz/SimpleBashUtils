CC=gcc
CC_FLAGS=-c -std=c11 -Wall -Werror -Wextra
BUILD_NAME=s21_grep

all: build

build: s21_grep

rebuild: clean build

s21_grep: s21_grep.o
	${CC} ${BUILD_NAME}.o -o ${BUILD_NAME}

s21_grep.o: s21_grep.c
	${CC} ${BUILD_NAME}.c ${CC_FLAGS} -o ${BUILD_NAME}.o

clean:
	rm -rf ./*.o
	rm -rf ./${BUILD_NAME}

test: t_grep.sh
	./t_grep.sh
