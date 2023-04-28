#-------------------------------------------------------
#    Узнаем какая ОС. Присваиваем значение флагов
#-------------------------------------------------------

OS = $(shell uname)
ifeq ("$(OS)", "Linux")
    TEST_FLAGS = -lcheck  -pthread -lrt -lm -lsubunit
    LEAKS_RUN = valgrind ./test
    OPEN = xdg-open
else
    TEST_FLAGS = -lcheck
    LEAKS_RUN = CK_FORK=no leaks -atExit -- ./test
    OPEN = open
endif

FLAGS = -Wall -Wextra -Werror -std=c++17
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

#-------------------------------------------------------
#    Переменная для компилятора
#-------------------------------------------------------

CC = g++

#-------------------------------------------------------
#    Ищем файлы для библиотеки, делаем переменную
#    Переименовываем для объектных файлов
#-------------------------------------------------------

SRCS = $(wildcard *.cc)

#-------------------------------------------------------
#    Переменная которая указывает на наш Makefile
#-------------------------------------------------------

THIS_FILE := $(lastword $(MAKEFILE_LIST))

#-------------------------------------------------------
#    Переменная для создания каталога report
#-------------------------------------------------------

REPORT = @mkdir -p report

#-------------------------------------------------------
#    Цели
#-------------------------------------------------------

all: clean matrix.a

matrix.a: matrix.o
	ar rcs matrix.a matrix.o
	ranlib matrix.a
	@$(MAKE) -f $(THIS_FILE) clean_src

matrix.o:
	g++ -c matrix.cc $(FLAGS)

test: matrix.o
	$(CC) ./tests/Tests.cc matrix.cc -o test -lgtest -pthread -lgmock $(GCOV_FLAGS)
	./test

gcov_report : test
	$(REPORT)
	gcovr -r . --html --html-details -o report/report.html
	@$(MAKE) -f $(THIS_FILE) clean_src
	$(OPEN) ./report/report.html

google_style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.h *.cc **/*.cc
	rm -f .clang-format

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.h *.cc **/*.cc
	rm -f .clang-format

clean_src:
	rm -rf *.o *.gcda *.gcno *.gcov

clean: clean_src
	rm -rf report *.a test .clang-format

.PHONY:
	all test matrix.a clean clean_src google_style clang
