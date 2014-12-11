# ============================================================================
# Static Library Qt Project File
# ============================================================================

# QtCore and QtGui are defaults
QT        += widgets sql
TEMPLATE   = lib
CONFIG    += staticlib
TARGET     = ssqt
VERSION    = 1.2
DESTDIR    = build

# If others include directories are needed:
# INCLUDEPATH +=

# If others libraries are needed:
# LIBS += -L/lib/path -llibrary_name

CONFIG(debug, debug|release) {
  # Instalation folder for debugging
  target.path = $$(WORKHOME)/libs/libssqt-$$VERSION/x86/dbg
  DEFINES += DEBUG
} else {
  # Instalation folder for release tests
  target.path = $$(WORKHOME)/libs/libssqt-$$VERSION/x86/rel
  DEFINES += NDEBUG
}

headers.path = $$(WORKHOME)/libs/libssqt-$$VERSION

# HEADERS: .h or .hpp files for dependency check {{{
BASE_HEADERS = libssqt.h \
    stdplx.hpp \
    ssqtcmn.hpp \
    ssqterr.hpp \
    ssqtdbg.hpp \
    ssqtasst.hpp \
    ssqtshrd.hpp \
    ssqtxmle.hpp \
    ssqtxmld.hpp

SQL_SUPPORT = sql/column.hpp

DAO_HEADERS = ssqtfld.hpp

GUI_HEADERS = ssqtmnui.hpp \
    ssqtmnup.hpp \
    ssqtmenu.hpp \
    ssqttlbi.hpp \
    ssqttlbr.hpp \
    ssqtmain.hpp \
    ssqtapp.hpp

HEADERS += $$BASE_HEADER $$SQL_SUPPORT $$DAO_HEADERS $$GUI_HEADERS
# HEADERS }}}
# SOURCES: .c or .cpp files to be compiled {{{
BASE_SOURCES = ssqtdbg.cpp \
    ssqtasst.cpp \
    ssqtxmle.cpp \
    ssqtxmld.cpp

SQL_SUPPORT = sql/column.cpp

DAO_SOURCES = ssqtfld.cpp

GUI_SOURCES = ssqtmnui.cpp \
    ssqtmnup.cpp \
    ssqtmenu.cpp \
    ssqttlbi.cpp \
    ssqttlbr.cpp \
    ssqtmain.cpp \
    ssqtapp.cpp

SOURCES += $$BASE_SOURCES $$SQL_SUPPORT $$DAO_SOURCES $$GUI_SOURCES
# SOURCES }}}

headers.files = $$HEADERS
headers.files -= stdplx.hpp

# Instruct the qmake tool to build the path for instalation.
INSTALLS += target
INSTALLS += headers

