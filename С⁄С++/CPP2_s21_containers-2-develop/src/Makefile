DIRS := array list map multiset queue set stack vector
COVERAGE_REPORT := coverage_report
RANGEFLAG = 
OS = $(shell uname)

ifeq ($(OS), Darwin)
	RANGEFLAG += --filter range
endif

all: test collect_gcda gcov_report

test:
	for dir in $(DIRS); do \
		make -C $$dir test; \
	done

collect_gcda:
	mkdir -p $(COVERAGE_REPORT)
	mkdir -p $(COVERAGE_REPORT)/tests
	for dir in $(DIRS); do \
		cp $$dir/*.gcno $(COVERAGE_REPORT)/ ; \
		cp $$dir/*.gcda $(COVERAGE_REPORT)/ ; \
		if [ "$(OS)" == "Darwin" ]; then \
			cp $$dir/*.tpp $(COVERAGE_REPORT)/ ; \
			cp $$dir/*.h $(COVERAGE_REPORT)/ ; \
			cp $$dir/tests/*.cpp ../src/$(COVERAGE_REPORT)/tests/ ; \
		fi; \
	done

gcov_report:
	lcov --directory $(COVERAGE_REPORT)/ --capture --output-file $(COVERAGE_REPORT)/coverage.info $(RANGEFLAG)
	lcov --remove $(COVERAGE_REPORT)/coverage.info '/usr/*' --output-file $(COVERAGE_REPORT)/coverage.info 
	genhtml $(COVERAGE_REPORT)/coverage.info --output-directory $(COVERAGE_REPORT)
	if [ "$(OS)" == "Darwin" ]; then \
		open $(COVERAGE_REPORT)/index.html ; \
	fi;

clean:
	for dir in $(DIRS); do \
		make -C $$dir clean; \
	done
	rm -rf $(COVERAGE_REPORT)
