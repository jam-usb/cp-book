LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "This makefile builds CP Book"
	@echo ""
	@echo "Available commands are:"
	@echo "	make fast		- to build CP Book, quickly (only runs LaTeX once)"
	@echo "	make cpbook		- to build CP Book"
	@echo "	make clean		- to clean up the build process"
	@echo "	make veryclean		- to clean up and remove cpbook.pdf"
	@echo "	make test		- to run all the stress tests in stress-tests/"
	@echo "	make test-compiles	- to test compiling all headers"
	@echo "	make help		- to show this information"
	@echo "	make showexcluded	- to show files that are not included in the doc"
	@echo ""
	@echo "For more information see the file 'doc/README'"

fast: | build
	$(LATEXCMD) content/cpbook.tex </dev/null
	cp build/cpbook.pdf cpbook.pdf

cpbook: test-session.pdf | build
	$(LATEXCMD) content/cpbook.tex && $(LATEXCMD) content/cpbook.tex
	cp build/cpbook.pdf cpbook.pdf

clean:
	cd build && rm -f cpbook.aux cpbook.log cpbook.tmp cpbook.toc cpbook.pdf cpbook.ptc

veryclean: clean
	rm -f cpbook.pdf test-session.pdf

.PHONY: help fast cpbook clean veryclean

build:
	mkdir -p build/

test:
	./doc/scripts/run-all.sh .

test-compiles:
	./doc/scripts/compile-all.sh .

test-session.pdf: content/test-session/test-session.tex content/test-session/chapter.tex | build
	$(LATEXCMD) content/test-session/test-session.tex
	cp build/test-session.pdf test-session.pdf

showexcluded: build
	grep -RoPh '^\s*\\cpbookimport{\K.*' content/ | sed 's/.$$//' > build/headers_included
	find ./content -name "*.h" -o -name "*.py" -o -name "*.java" | grep -vFf build/headers_included
