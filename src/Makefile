TEST_FLAGS= -lgtest_main -pthread -lgtest
GCC= g++ -Wall -Wextra -Werror -std=c++17
GCO= --coverage
VECTOR=vector/*.cc
STACK=stack/*.cc
LIST= list/*.cc
QUEUE=queue/*.cc
AVL=avl_tree/*.cc
MAP=map/*.cc
SET=set/*.cc

FUNC_SRC := $(wildcard */*.h && */*.tpp && */*.cc)

RM_RULE= rm -rf main test *.dSYM report res *.info *.gcda *.gcno

UNAME := $(shell uname)

FILES= $(wildcard *.cc)
OBJ=$(patsubst %.cc,%.o,${FILES})

test: clean
	$(GCC) $(TEST_FLAGS) -g -o test $(VECTOR) $(STACK) $(QUEUE) $(LIST) $(AVL) $(SET) $(MAP)
	./test

clean: style
	$(RM_RULE) 
	cd queue && $(RM_RULE)
	cd list && $(RM_RULE)
	cd vector && $(RM_RULE)
	cd stack && $(RM_RULE)
	cd map && $(RM_RULE)
	cd set && $(RM_RULE)
	cd avl_tree && $(RM_RULE)
	clear

gcov_report: clean
	$(GCC) $(TEST_FLAGS) $(GCO) -o report $(VECTOR) $(STACK) $(QUEUE) $(LIST) $(AVL) $(SET) $(MAP)
	./report
	lcov -c -d . -o coverage.info --ignore-errors mismatch
	lcov -r coverage.info /usr/local/include/gtest 10.3.0 -o filtered_coverage.info
	genhtml filtered_coverage.info --output-directory=res
	open ./res/index.html
	rm -rf *.gcda *.gcno

docker:
	docker build -t my_image .
	docker run -d -p 80:80 --name my_container my_image bash -c "cd /TEST_VALGRIND && make test && valgrind ./test"
	docker logs -f my_container
	docker stop my_container
	docker rm my_container
	docker rmi my_image

style:
	@cp ../materials/linters/.clang-format .
	clang-format -n $(FUNC_SRC) s21_containers.h
	clang-format -i $(FUNC_SRC) s21_containers.h
	@rm -rf .clang-format
