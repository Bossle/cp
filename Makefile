.PHONY : all clean gcov install install_debug test
all : install install_debug test
	$(MAKE) gcov

include scripts/base.mk
include scripts/cpp.mk

clean :
	-rm -r bin build lib log
	-rm *.gcov

install : lib/libossle.a

lib/libossle.a : $(patsubst %.cpp,build/%.o,$(shell find src -name *.cpp)) | $(parentDirs)
	ar cr $@ $?

install_debug : lib/libossle_debug.a

lib/libossle_debug.a : $(patsubst %.cpp,build/%_debug.o,$(shell find src -name *.cpp)) | $(parentDirs)
	ar cr $@ $?

test : $(patsubst %.in,log/%_success,$(shell find test -name *.in))
	echo 'Finished tests'

log/%_success : scripts/runTest.sh bin/$$(*D)/solver_debug bin/$$(*D)/checker_debug $$*.in | $(parentDirs)
	-$< $*

bin/%/checker_debug :: | $(parentDirs)
	$(shell ln -rs scripts/defaultChecker.sh $@)

gcov : $(shell find build -name *.o)
	gcov -mpr $^

