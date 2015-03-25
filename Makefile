# ============================================================================
# Local Makefile
# ============================================================================

.PHONY: debug debug-install release release-install debug-clean release-clean help docs docs-install

default: debug

# ============================================================================
# Local Variables
# ============================================================================
MAJOR_VERSION = 1
MINOR_VERSION = 3
BUILD_VERSION = 11
VERSION_NUMBER = $(MAJOR_VERSION).$(MINOR_VERSION)

HTDOCS     = /f/xampplite/htdocs/docs
HTDOCS_DIR = $(HTDOCS)/libssqt-$(VERSION_NUMBER)
DIST_DIR   = $(WORKHOME)/libs/libssqt-$(VERSION_NUMBER)
TAGS_DIR   = $(DIST_DIR)/tags

CP = rsync
CPOPTS = -cvruptOm --no-o --no-g --delete --delete-excluded --exclude='.*.sw?'

# ============================================================================
# Targets
# ============================================================================

debug :
	@qmake --no-print-directory -C bin -f Makefile debug

release :
	@qmake --no-print-directory -C bin -f Makefile release

debug-install :
	@qmake --no-print-directory -C bin -f Makefile debug-install

release-install :
	@qmake --no-print-directory -C bin -f Makefile release-install

debug-clean :
	@qmake --no-print-directory -C bin -f Makefile debug-clean

release-clean :
	@qmake --no-print-directory -C bin -f Makefile release-clean

clean : debug-clean release-clean

docs :
	( cat doxyfile; echo "PROJECT_NUMBER=$(VERSION_NUMBER)" ) | doxygen -

docs-clean :
	@rm docs/html/*

docs-install :
	$(CP) $(CPOPTS) docs/html/ $(HTDOCS_DIR)/

$(TAGS_DIR) :
	@mkdir -p $(TAGS_DIR)

tags : $(TAGS_DIR)
	@pmake ctags -t libssqt-$(VERSION_NUMBER)/tags/libssqt.tags

help :
	@echo -e "Makefile targets:\n"\
	      "debug             Builds debug target\n"\
	      "debug-clean       Clean up the debug target files\n"\
	      "debug-install     Installs, building if needed, the debug target\n"\
	      "release           Build the release target\n"\
	      "release-clean     Clean up the debug target files\n"\
	      "release-install   Installs, building if needed, the release target\n"\
	      "clean             Clean up all built targets\n"\
		  "docs              Build the documentation through Doxygen\n"\
		  "docs-clean        Clean up all documentation\n"\
		  "docs-install      Copy documentation in the thumb drive\n"\
		  "tags              Build a tags file in the dist directory"
		

