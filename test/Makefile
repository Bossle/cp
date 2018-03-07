.PHONY : all test clean
all : test

INCLUDEDIRS = ../include
LIBDIRS = ../lib
include ../script/cpp.mk

RM = rm

clean :
	-$(RM) -r bin build

test : $(patsubst ./%.cpp,bin/%,$(shell find -name '*.cpp'))
	echo Testing $?
	$(foreach t,$?,$t;)

