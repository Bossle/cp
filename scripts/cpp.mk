.SECONDARY :
.SECONDEXPANSION :

CXX = g++
BASEFLAGS = -g -O2 -std=c++11 -static
INCLUDEFLAGS = $(addprefix -I,$(shell find include -type d))
WARNINGFLAGS = -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op #-Wshift-overflow=2 -Wduplicated-cond
DEBUGFLAGS = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=undefined -fno-sanitize-recover --coverage
CXXFLAGS = $(BASEFLAGS) $(INCLUDEFLAGS) $(WARNINGFLAGS)
CXXDEBUGFLAGS = $(CXXFLAGS) $(DEBUGFLAGS)

LDFLAGS = -Llib
LDDEBUGFLAGS = $(LDFLAGS) --coverage
LDLIBS = -lossle
LDDEBUGLIBS = -lossle_debug -lubsan

parentDirs = $$(dir $$@)

%/ :
	mkdir -p $@

build/%.d : %.cpp | $(parentDirs)
	$(CXX) -MM $(CXXFLAGS) $< -MT $@ -MT build/$*.o -MT build/$*_debug.o -MF $@

build/%.o : %.cpp build/%.d | $(parentDirs)
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/%_debug.o : %.cpp build/%.d | $(parentDirs)
	$(CXX) -c $(CXXDEBUGFLAGS) $< -o $@

bin/% : build/%.o lib/libossle.a | $(parentDirs)
	$(CXX) $(LDFLAGS) $< $(LDLIBS) -o $@

bin/%_debug : build/%_debug.o lib/libossle_debug.a | $(parentDirs)
	$(CXX) $(LDDEBUGFLAGS) $< $(LDDEBUGLIBS) -o $@

-include $(shell find build -name *.d)

