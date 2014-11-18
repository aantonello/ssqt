# ============================================================================
# Static Library Qt Project File
# ============================================================================

# QtCore and QtGui are defaults
QT        += widgets
TEMPLATE   = lib
CONFIG    += staticlib
TARGET     = ssqt
VERSION    = 1.1
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
HEADERS += libssqt.h \
    stdplx.hpp \
    ssqtcmn.hpp \
    ssqterr.hpp \
    ssqtdbg.hpp \
    ssqtxmle.hpp \
    ssqtxmld.hpp \
    ssqtmnui.hpp \
    ssqtmnup.hpp \
    ssqtasst.hpp \
    ssqtapp.hpp
# HEADERS }}}
# SOURCES: .c or .cpp files to be compiled {{{
SOURCES += ssqtdbg.cpp \
    ssqtxmle.cpp \
    ssqtxmld.cpp \
    ssqtmnui.cpp \
    ssqtmnup.cpp \
    ssqtasst.cpp \
    ssqtapp.cpp
# SOURCES }}}

headers.files = $$HEADERS
headers.files -= stdplx.hpp

# Instruct the qmake tool to build the path for instalation.
INSTALLS += target
INSTALLS += headers

