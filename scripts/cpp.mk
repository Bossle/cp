CXX = g++ -std=c++14
INCLUDEFLAGS = -Itemplate
WARNINGFLAGS = -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond
DEBUGFLAGS = -Og -ggdb3 -DCP_DEBUG -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fno-sanitize-recover
RELEASEFLAGS = -static -O2 -fno-optimize-sibling-calls -fno-strict-aliasing -DONLINE_JUDGE -s
CXXFLAGS = $(INCLUDEFLAGS) $(WARNINGFLAGS)

build/%.d : %.cpp | $(parentDirs)
	$(CXX) -MM $(CXXFLAGS) $< -MT $@ -MT bin/$* -MT bin/$*_debug -MF $@

bin/% : %.cpp build/%.d | $(parentDirs)
	$(CXX) $(CXXFLAGS) $(RELEASEFLAGS) $< -o $@

bin/%_debug : %.cpp build/%.d | $(parentDirs)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $< -o $@

build/%.cpp : %.cpp build/%.d | $(parentDirs)
	$(CXX) $(CXXFLAGS) -E -C -fdirectives-only $< -o $@

dist/%.cpp : build/src/%.cpp | $(parentDirs)
	sed -e '/^# / d' -e '1,/^\/\/ END OF STD HEADERS$$/ d' $< |\
	sed '1i#include <bits\/stdc++.h>' | cat -s > $@

-include $(shell find build -name *.d)

