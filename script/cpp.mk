.SECONDARY :
.SECONDEXPANSION :

INCLUDEDIRS ?= include
LIBDIRS ?= lib

CXX = g++
BASEFLAGS = -g -O2 -std=c++11 -static
INCLUDEFLAGS = $(addprefix -I,$(shell find $(INCLUDEDIRS) -type d))
WARNINGFLAGS = -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op #-Wshift-overflow=2 -Wduplicated-cond
DEBUGFLAGS = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=undefined -fno-sanitize-recover --coverage
CXXFLAGS = $(BASEFLAGS) $(INCLUDEFLAGS) $(WARNINGFLAGS) $(EXTRAFLAGS)

LIBPATHS = $(shell find $(LIBDIRS) -name *.a)
LDFLAGS = $(addprefix -L,$(dir $(LIBPATHS)))
LDDEBUGFLAGS = --coverage
LDLIBS = $(patsubst lib%.a,-l%,$(notdir $(LIBPATHS))) -lubsan

parentDirs = $$(dir $$@)

%/ :
	mkdir -p $@

build/%.d : %.cpp | $(parentDirs)
	$(CXX) -MM $(CXXFLAGS) $< -MT $@ -MT build/$*.o -MT build/$*_debug.o -MF $@

build/%.o : %.cpp build/%.d | $(parentDirs)
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%_debug.o : %.cpp build/%.d | $(parentDirs)
	$(CXX) -c $(CXXFLAGS) $(DEBUGFLAGS) $< -o $@

bin/% : build/%.o $(LIBPATHS) | $(parentDirs)
	$(CXX) $(LDFLAGS) $< $(LDLIBS) -o $@

bin/%_debug : build/%_debug.o $(LIBPATHS) | $(parentDirs)
	$(CXX) $(LDFLAGS) $(LDDEBUGFLAGS) $< $(LDLIBS) -o $@

-include $(shell find build -name *.d)

