CC=gcc
CC_FLAGS=-c -Wall -Werror -Wextra -std=c11
BUILD_NAME=s21_cat

all: build

build: s21_cat

rebuild: clean build

s21_cat: s21_cat.o
	${CC} s21_cat.o -o ${BUILD_NAME}

s21_cat.o: s21_cat.c
	${CC} s21_cat.c ${CC_FLAGS} -o s21_cat.o

clean:
	rm -rf ./*.o
	rm -rf ./${BUILD_NAME}

test: t_cat.sh
	./t_cat.sh
