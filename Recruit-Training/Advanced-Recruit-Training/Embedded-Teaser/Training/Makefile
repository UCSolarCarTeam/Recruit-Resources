TESTS_DIR = ./Test

SUBCLEAN = $(addsuffix .clean,$(TESTS_DIR))

RUN_TEST = $(addsuffix .test,$(TESTS_DIR))

default: TrainingTest test

TrainingTest:
	cd $(TESTS_DIR)/ && make -j4

$(SUBCLEAN):
	cd $(basename $@) && make clean

clean: $(SUBCLEAN)

$(RUN_TEST):
	cd $(basename $@) && make test

test: $(RUN_TEST)
