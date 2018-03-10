.PHONY : all test clean
all : test

INCLUDEDIRS = ../include
LIBDIRS = ../lib
include ../script/cpp.mk

RM = rm

clean :
	-$(RM) -r bin build

test : $(patsubst ./%.cpp,bin/%_debug,$(shell find -name '*.cpp'))
	echo Testing $?
	$(foreach t,$?,$t;)
	gcov -mr $(basename $(shell find build -name '*.o'))

