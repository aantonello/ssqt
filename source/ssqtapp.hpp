/**
 * \file
 * Declares the SSApplication class.
 *
 * \author Alessandro Antonello <aantonello@paralaxe.com.br>
 * \date   novembro 07, 2014
 * \since  Super Simple for Qt 5 1.1
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTAPP_HPP_DEFINED__
#define __SSQTAPP_HPP_DEFINED__

#include <QApplication>
#include <QSharedMemory>

/**
 * \ingroup ssqt_ui
 * An extension of \c QApplication class.
 *//* --------------------------------------------------------------------- */
class SSApplication : public QApplication
{
    Q_OBJECT

public:
    // SSApplication(int &argc, char** argv);/*{{{*/
    /**
     * Default constructor.
     * @param argc Number of arguments in \a argv.
     * @param argv Array of string pointers to command line arguments.
     * @remarks This is the standard way to construct applications in Qt. It
     * has the same arguments of \c QApplication class. The command line
     * arguments are processed and made available through \c
     * QApplication::arguments() function.
     * @note This constructor is inlined.
     * @since 1.0
     **/
    SSApplication(int &argc, char** argv);
    /*}}}*/
    // virtual ~SSApplication();/*{{{*/
    /**
     * Default destructor.
     * @remarks Deallocate all resources used in this application.
     * @note This function is inlined.
     * @since 1.0
     **/
    virtual ~SSApplication();
    /*}}}*/

public:             // Operations
    // bool ensureSingleInstance(const QString &applicationKey);/*{{{*/
    /**
     * Ensures this application has only one instance running.
     * @param applicationKey This is a string to be used to uniquely identify
     * this application. Not the instance. It will be used to name the shared
     * memory object.
     * @return \b true if this is the only instance of the application. \b
     * false otherwise.
     * @remarks The function will create a shared memory object to hold while
     * the application is running. This shared memory will not contain any
     * significant value and will only be used to check if this is the only
     * instance of this application running.
     * @since 1.0
     **/
    bool ensureSingleInstance(const QString &applicationKey);
    /*}}}*/

protected:          // Data Members
    // QSharedMemory *m_shared;/*{{{*/
    /**
     * Shared memory object.
     * Used in the #ensureSingleInstance() function to check when there is
     * another instance of this application running.
     * @since 1.0
     **/
    QSharedMemory *m_shared;
    /*}}}*/
};
/* Inlined Constructor & Destructor {{{ */
/* Default constructor. */
inline SSApplication::SSApplication(int &argc, char** argv) :
    QApplication(argc, argv), m_shared(NULL) { }

/* Default destructor */
inline SSApplication::~SSApplication() {
    if (m_shared != NULL) {
        m_shared->detach();
    }
}
/* }}} Inlined Constructor & Destructor */

#endif /* __SSQTAPP_HPP_DEFINED__ */
