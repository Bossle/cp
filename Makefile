.PHONY : all clean judge
all : judge

include scripts/base.mk
include scripts/cpp.mk

clean :
	$(RM) -r bin build log

judge : $(patsubst src/%.cpp,log/%/success,$(shell find src -name *.cpp))
	echo 'Finished judging'

log/%/success : scripts/run_judge.sh bin/src/%_debug bin/src/% bin/test/$$(*D)/judge_debug test/$$(*D)/*.in test/$$(*D)/*.sol
	$< $(*D) $(*F)

