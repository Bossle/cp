CXX = g++
BASEFLAGS = -g -O2 -std=c++14 #-static
INCLUDEFLAGS = -Itemplate
WARNINGFLAGS = -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond
DEBUGFLAGS = -DBOSSLE_DEBUG -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fno-sanitize-recover
CXXFLAGS = $(BASEFLAGS) $(INCLUDEFLAGS) $(WARNINGFLAGS)
CXXDEBUGFLAGS = $(CXXFLAGS) $(DEBUGFLAGS)

build/%.d : %.cpp | $(parentDirs)
	$(CXX) -MM $(CXXFLAGS) $< -MT $@ -MT bin/$* -MT bin/$*_debug -MF $@

bin/% : %.cpp build/%.d | $(parentDirs)
	$(CXX) $(CXXFLAGS) $< -o $@

bin/%_debug : %.cpp build/%.d | $(parentDirs)
	$(CXX) $(CXXDEBUGFLAGS) $< -o $@

-include $(shell find build -name *.d)

