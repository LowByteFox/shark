# SPDX-License-Identifier: Apache-2.0
.POSIX:
PY = python3
TEX = tectonic
TEXFLAGS = -X compile
DOC = isa.pdf

all: pdfs/done $(DOC)

pdfs/done: venv
	. venv/bin/activate && pip install matplotlib
	. venv/bin/activate && $(PY) gen.py

venv:
	$(PY) -m venv venv

.tex.pdf:
	@echo "  TEX   $<"
	@$(TEX) $(TEXFLAGS) $<

clean:
	rm -f $(DOC)

.PHONY:	all clean
.SUFFIXES: .tex .pdf