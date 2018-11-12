##
# @author Sargis S Yonan
# @date 11 November 2018
# @brief used for compiling and linking Fielder

# flags
debug_mode=ON
debugger = gdb

exec = fielder

cpp = g++
cpp_options = -std=c++14
cpp_options += -Wall -Wextra -Werror

debug_flag = -g

include_dirs = model

objects = main.o ControlPoint.o

all: build

run: build
	@./$(exec)

gdb: build $(exec_name)
	sudo $(debugger) ./$(exec)

valgrind: build $(exec)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(exec)

clean:
	rm -rf $(objects) $(exec)

build: $(objects)
	$(cpp) $(cc_options) $(objects) -o $(exec)

main.o: main.cc ControlPoint.o
ifdef ($(debug_mode),ON)
	$(cpp) $(debug_flag) $(cpp_options) -DDEBUG_MODE=1 -c main.cc -I $(include_dirs)
else
	$(cpp) $(debug_flag) $(cpp_options) -c main.cc -I $(include_dirs)
endif

ControlPoint.o: model/ControlPoint.cc model/ControlPoint.h
ifdef ($(debug_mode),ON)
	$(cpp) $(debug_flag) $(cpp_options) -DDEBUG_MODE=1 -c model/ControlPoint.cc -I $(include_dirs)
else
	$(cpp) $(debug_flag) $(cpp_options) -c model/ControlPoint.cc -I $(include_dirs)
endif