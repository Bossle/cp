CXX = g++
BASEFLAGS = -g -O2 -std=c++11 -static
INCLUDEFLAGS = $(addprefix -I,$(shell find include -type d))
WARNINGFLAGS = -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -fmax-errors=5 #-Wshift-overflow=2 -Wduplicated-cond
DEBUGFLAGS = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=undefined -fno-sanitize-recover --coverage
CXXFLAGS = $(BASEFLAGS) $(INCLUDEFLAGS) $(WARNINGFLAGS)
CXXDEBUGFLAGS = $(CXXFLAGS) $(DEBUGFLAGS)

LDFLAGS = -Llib
LDDEBUGFLAGS = $(LDFLAGS) --coverage
LIBS = libossle
LDLIBS = $(patsubst lib%,-l%,$(LIBS))
LDDEBUGLIBS = $(patsubst lib%,-l%_debug,$(LIBS)) -lubsan

build/%.d : %.cpp | $(parentDirs)
	$(CXX) -MM $(CXXFLAGS) $< -MT $@ -MT build/$*.o -MT build/$*_debug.o -MF $@

build/%.o : %.cpp build/%.d | $(parentDirs)
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%_debug.o : %.cpp build/%.d | $(parentDirs)
	$(CXX) -c $(CXXDEBUGFLAGS) $< -o $@

bin/% : build/%.o $(patsubst %,lib/%.a,$(LIBS)) | $(parentDirs)
	$(CXX) $(LDFLAGS) $< $(LDLIBS) -o $@

bin/%_debug : build/%_debug.o $(patsubst %,lib/%_debug.a,$(LIBS)) | $(parentDirs)
	$(CXX) $(LDDEBUGFLAGS) $< $(LDDEBUGLIBS) -o $@

-include $(shell find build -name *.d)

