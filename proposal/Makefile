SRC += title.md
SRC += overview.md
SRC += hardware.md
SRC += extras.md

.PHONY: all pdf tex checkpaperdir clean

all: checkpaperdir pdf tex
    
pdf: $(SRC)
	pandoc -r markdown+simple_tables+table_captions+yaml_metadata_block \
	-s -S --latex-engine=pdflatex --template=$(TEMPLATE) --csl=$(CSL) \
	-V geometry:margin=1in \
	-V fontsize=12pt \
	-V fontfamily=times \
	-V linestretch=1.5 \
	-V documentclass=article \
	-o $(PAPER_BUILD_DIR)/proposal.pdf \
	$(SRC)

tex: $(SRC)
	pandoc -r markdown+simple_tables+table_captions+yaml_metadata_block \
	-s -S --latex-engine=pdflatex --template=$(TEMPLATE) --csl=$(CSL) \
	-V geometry:margin=1in \
	-V fontsize=12pt \
	-V fontfamily=times \
	-V linestretch=1.5 \
	-o $(PAPER_BUILD_DIR)/proposal.tex \
	$(SRC)

checkpaperdir: $(PAPER_BUILD_DIR)

$(PAPER_BUILD_DIR):
	@mkdir -p $@

clean:
	rm -rf $(PAPER_BUILD_DIR)
	
