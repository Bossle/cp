.PHONY : all clean judge-all
all : judge-all

include scripts/base.mk
include scripts/cpp.mk

clean :
	$(RM) -r bin build dist log judge

# TODO: make this work with weird filenames
judge-all : $(patsubst src/%.cpp,judge/%,$(shell find src -name *.cpp))
	echo 'Finished judging'

judge/% : scripts/run_judge.sh bin/src/%_debug bin/src/% bin/test/$$(*D)/judge_debug test/$$(*D)/*.in test/$$(*D)/*.sol | $(parentDirs)
	$< $(*D) $(*F) $@

