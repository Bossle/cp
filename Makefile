.PHONY : all clean judge-all dist-all
all : judge-all dist-all
include scripts/base.mk

# TODO: make the $(shell find)s work with weird filenames

include scripts/cpp.mk

clean :
	$(RM) -r bin build dist log judge

judge-all : $(patsubst src/%.cpp,judge/%,$(shell find src -name *.cpp))
	echo 'Finished judging'

judge/% : scripts/run_judge.sh bin/src/%_debug bin/src/% bin/test/$$(*D)/judge_debug test/$$(*D)/*.in test/$$(*D)/*.sol | $(parentDirs)
	$< $(*D) $(*F) $@

dist-all : $(patsubst src/%.cpp,dist/%.cpp,$(shell find src -name *.cpp))
