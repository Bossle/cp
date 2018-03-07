.PHONY : all check clean install
.SECONDARY :
.SECONDEXPANSION :
all : check install

RM = rm

CXX = g++
BASEFLAGS = -g -O2 -std=c++11 -static
INCLUDEFLAGS = $(addprefix -I,$(shell find include -type d))
WARNINGFLAGS = -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op #-Wshift-overflow=2 -Wduplicated-cond
DEBUGFLAGS = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=undefined -fno-sanitize-recover
CXXFLAGS = $(BASEFLAGS) $(INCLUDEFLAGS) $(WARNINGFLAGS) $(EXTRAFLAGS)

LDFLAGS = $(addprefix -L,$(shell find lib -type d))
LDLIBS = $(patsubst lib%.a,-l%,$(notdir $(shell find lib -name *.a)))

parentDirs = $$(dir $$@)

%/ :
	mkdir -p $@

build/%.d : %.cpp | $(parentDirs)
	$(CXX) -MM $(CXXFLAGS) $< -MT $@ -MT $(addsuffix .o,$(basename $@)) -MF $@

build/%.o : %.cpp build/%.d | $(parentDirs)
	$(CXX) -c $(CXXFLAGS) $< -o $@

bin/% : build/%.o install | $(parentDirs)
	$(CXX) $(LDFLAGS) $< $(LDLIBS) -o $@

clean :
	-$(RM) -r bin build lib

check : $(patsubst %.cpp,bin/%,$(shell find test -type f))

install : lib/libossle.a
lib/libossle.a : $(patsubst %.cpp,build/%.o,$(shell find src -type f)) | $(parentDirs)
	ar cr $@ $?

-include $(shell find build -name *.d)

