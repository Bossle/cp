.PHONY : all test clean install
all : test install

include scripts/cpp.mk

RM = rm

clean :
	-$(RM) -r bin build lib log

install : lib/libossle.a

lib/libossle.a : $(patsubst %.cpp,build/%.o,$(shell find src -type f)) | $(parentDirs)
	ar cr $@ $?

lib/libossle_debug.a : $(patsubst %.cpp,build/%_debug.o,$(shell find src -type f)) | $(parentDirs)
	ar cr $@ $?

test : $(patsubst %.in,log/%_success,$(shell find test -name *.in))
	echo 'All tests passed'

log/%_success : scripts/runTest.sh bin/$$(*D)/solver_debug bin/$$(*D)/checker_debug $$*.in | $(parentDirs)
	-$< $*

bin/%/checker_debug :: | $(parentDirs)
	$(shell ln -rs scripts/defaultChecker.sh $@)

