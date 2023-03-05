CC=gcc -std=c++17
LIBS=-lstdc++ -g -lm
LIBS_TEST=-lgtest -pthread -coverage
SOURCES=Tree.cpp main.cpp
TEST_SOURCE=tests.cpp

all: build
	./set

build:
	$(CC) $(SOURCES) $(LIBS) -o set

example:
	$(CC) TreeExample.cpp $(LIBS) -o set
	./set

style:
	clang-format -n --style=google Model/*.cpp Model/*.h Controller/*.cpp Controller/*.h View/*.cpp View/*.h

tests: build_test
	./tests

gcov_report: tests
	mkdir report
	lcov --no-external --directory ./ --capture --output-file report.info
	genhtml report.info --output-directory report
	rm -rf *.gcno *.info *.gcda ./tests
	open report/index.html

clean:
	rm -rf *.o
	rm -rf ./tests report *.gcda *.gcno
	rm -rf s21_matrix_oop.a
	rm -rf SmartCalc

valgrind: build
	valgrind --leak-check=full --tool=memcheck --track-origins=yes ./set

git_:
	git add .
	git commit -m 'dfdf'
	git push
