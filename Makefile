##############################################################################
# Makefile to build or update the build system.
# This makefile uses premake4 for its usage.
##############################################################################

.PHONY: all clean help update docs install-docs

all: debug

##############################################################################
# Local Variables
##############################################################################
MAJOR_VER = 1
MINOR_VER = 3
BUILD_VER = 5
TARGET    = libssqt
TARGETDIR = /c/plx/libs/$(TARGET)-$(MAJOR_VER).$(MINOR_VER)
DEBUGDIR  = $(TARGETDIR)/x86/dbg
RELEASEDIR = $(TARGETDIR)/x86/rel
DEBUGBIN  = bin/build/$(TARGET).a
RELEASEBIN = bin/build/$(TARGET).a
DOCROOT = /cygdrive/f/xampplite/htdocs/docs
DOC_DIST_DIR = $(DOCROOT)/$(TARGET)-$(MAJOR_VER).$(MINOR_VER)

CP = rsync
CPOPTIONS = -vcruptOm --no-o --no-g --delete --delete-excluded --exclude='.*.sw?'

##############################################################################
# Dependencies part
##############################################################################

bin/Makefile : source/ssqt.pro
	@cd bin
	@qmake -makefile ../source/ssqt.pro

$(TARGETDIR) :
	mkdir -p $(TARGETDIR)

$(DEBUGDIR) : $(TARGETDIR)
	@mkdir -p $(DEBUGDIR)

$(RELEASEDIR) : $(TARGETDIR)
	@mkdir -p $(RELEASEDIR)

$(DEBUGBIN) : debug

$(RELEASEBIN) : release


$(DOC_DIST_DIR) :
	@mkdir -p $(DOC_DIST_DIR)

##############################################################################
# Targets
##############################################################################

debug:
	@${MAKE} --no-print-directory -C bin -f Makefile debug 2>&1 | tee build.log

release: bin/Makefile
	@cd bin
	@qmake release

debug-clean:
	@${MAKE} --no-print-directory -C bin -f Makefile debug-clean 2>&1 | tee build.log

release-clean:
	@cd bin
	@qmake release-clean

clean: debug-clean release-clean


help:
	@echo "This is a Makefile utility at top of Qt build system."
	@echo "We have the following targets:"
	@echo ""
	@echo "debug        Builds the debug version of the project"
	@echo "release      Builds the release version of the project"
	@echo "debug-clean  Clean files generated from debug build"
	@echo "release-clean Clean files generated from release build"
	@echo "clean        Clean all current builds and binaries"
	@echo "docs         Build documentation using 'doxygen'"
	@echo "install      Install header files and/or binaries"
	@echo "install-docs Install the documentation in HTML in the Apache path. Notice "
	@echo "             that this target needs the '/f' mount point. It must point to"
	@echo "             the root directory of the XAMPPLITE tool (currently F:)."
	@echo ""


install : $(DEBUGDIR) $(RELEASEDIR) $(DEBUGBIN) $(RELEASEBIN)
	$(CP) $(CPOPTIONS) source/libssqt.h $(TARGETDIR)/
	$(CP) $(CPOPTIONS) source/ssqt*.hpp $(TARGETDIR)/
	$(CP) $(CPOPTIONS) $(DEBUGBIN) $(DEBUGDIR)/
	$(CP) $(CPOPTIONS) $(RELEASEBIN) $(RELEASEDIR)/

docs:
	( cat doxyfile; echo "PROJECT_NUMBER=$(MAJOR_VER).$(MINOR_VER).$(BUILD_VER)" ) | doxygen -

install-docs: $(DOC_DIST_DIR)
	$(CP) $(CPOPTIONS) docs/html/ $(DOC_DIST_DIR)/


