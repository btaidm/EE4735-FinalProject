mydir := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

## Markdown extension (e.g. md, markdown, mdown).
export MEXT := md

## Location of your working bibliography file
BIB = references.bib

## CSL stylesheet (located in the csl folder of the PREFIX directory).
export CSL := $(mydir)/ieee.csl

export TEMPLATE := $(mydir)/paper.template

