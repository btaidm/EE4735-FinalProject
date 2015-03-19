SRC += title.md
SRC += overview.md
SRC += hardware.md
SRC += extras.md

all: pdf tex

pdf: $(SRC)
	@echo $(TEMPLATE)
	@echo $(CSL)
	@echo $(BUILD_DIR)
	pandoc -r markdown+simple_tables+table_captions+yaml_metadata_block \
	       -s -S --latex-engine=pdflatex --template=$(TEMPLATE) --csl=$(CSL) \
	       -V geometry:margin=1in \
	       -V fontfamily=times \
	       -V linestretch=2 \
	       -o $(BUILD_DIR)/proposal.pdf \
	       $(SRC)

tex: $(SRC)
	@echo $(TEMPLATE)
	@echo $(CSL)
	@echo $(BUILD_DIR)
	pandoc -r markdown+simple_tables+table_captions+yaml_metadata_block \
	       -s -S --latex-engine=pdflatex --template=$(TEMPLATE) --csl=$(CSL) \
	       -V geometry:margin=1in \
	       -V fontfamily=times \
	       -V linestretch=2 \
	       -o $(BUILD_DIR)/proposal.tex \
	       $(SRC)
