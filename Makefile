.PHONY : all test clean install
all : test install

include script/cpp.mk

RM = rm

clean :
	-$(RM) -r bin build lib
	$(MAKE) -C test clean

install : lib/libossle.a lib/libossle_debug.a

lib/libossle.a : $(patsubst %.cpp,build/%.o,$(shell find src -type f)) | $(parentDirs)
	ar cr $@ $?

lib/libossle_debug.a : $(patsubst %.cpp,build/%_debug.o,$(shell find src -type f)) | $(parentDirs)
	ar cr $@ $?

test : install
	$(MAKE) -C test

