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
class SSMainWnd;

/**
 * \ingroup ssqt_ui
 * An extension of \c QApplication class.
 * It should be used in GUI applications only since \c QApplication class is
 * strict for that matter. The \SSApplication class brings some methods to
 * make some things easy. For example, you can use the #ensureSingleInstance()
 * member function to ensure that you are running a single application
 * instance. Works on every platform. Also there is the #currentApp() static
 * member function that returns a pointer to the current \SSApplication
 * instance. If you don't need to extend the \SSApplication class you can use
 * the ss::App variable that holds the application instance. If you made an
 * application class extension you can write a macro to cast the ss::App
 * variable to your own class type. For example:
 * ~~~~~~~~~~~~
 * #define theApp   ((MyApplicationClass*)ss::App)
 * ~~~~~~~~~~~~
 * Then, somewhere else in your code you use it like that:
 * ~~~~~~~~~~~~
 * theApp->my_really_clever_method();
 * ~~~~~~~~~~~~
 * If you use the SSMainWnd class to construct your main window it will
 * register it self within the SSApplication. Then you can access the class
 * instance through the member function #mainWindow(). Together with the \c
 * currentApp() method or the ss::App variable this allows you to access the
 * main window instance everywhere in your software.
 *//* --------------------------------------------------------------------- */
class SSApplication : public QApplication
{
    Q_OBJECT

public:
    /** @name Constructors & Destructor */ //@{
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
    //@}
public:
    /** @name Static Functions */ //@{
    // static SSApplication* currentApp();/*{{{*/
    /**
     * Retrieves the instance of the running application.
     * This is like the \c QCoreApplication::instance() but cast the result as
     * an SSApplication class pointer.
     * @returns A pointer to the created instance of SSApplication class. If
     * no class was created, the result will be \b NULL.
     * @remarks Notice that this call is valid only when you create an
     * SSApplication instance or extends it. If you use the \c QApplication or
     * \c QCoreApplication directly this function returns \b NULL.
     * @since 1.1
     **/
    static SSApplication* currentApp();
    /*}}}*/
    //@}
public:
    /** @name Operations */ //@{
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
    // SSMainWnd* mainWindow() const;/*{{{*/
    /**
     * Retrieves a pointer to the main application window.
     * @returns Pointer to the created instance of \c SSMainWnd class. If no
     * window was created, this function returns \b NULL.
     * @remarks This function will return a valid pointer only if you use the
     * SSMainWnd class or an extension of it. Otherwise it will return \b
     * NULL.
     * @since 1.1
     **/
    SSMainWnd* mainWindow() const;
    /*}}}*/
    //@}
protected:
    // QSharedMemory *m_shared;/*{{{*/
    /**
     * Shared memory object.
     * Used in the #ensureSingleInstance() function to check when there is
     * another instance of this application running.
     * @since 1.0
     **/
    QSharedMemory *m_shared;
    /*}}}*/
    // SSMainWnd     *m_mainWnd;/*{{{*/
    /**
     * Holds the pointer to the solely main window class.
     * @since 1.1
     **/
    SSMainWnd     *m_mainWnd;
    /*}}}*/

    friend class SSMainWnd;
};
/* Inlined Functions {{{ */
/* }}} Inlined Functions */

/**
 * @defgroup ssqt_ui_vars UI Variables
 * Global variables.
 * There is little need for global variables in a C++ application but, we
 * found some things more useful when they are stored in global entities.
 * Global variables in this library are always inside he "ss" namespace.
 * @{ *//* ---------------------------------------------------------------- */
namespace ss {
    // extern SSApplication *App;/*{{{*/
    /**
     * Pointer to the current instance of the application.
     * It will get set only if you use the \c SSApplication class or extends
     * the \c SSApplication class. All constructors of SSApplication set this
     * global variable if it is not set yet.
     * @note Why a global variable? Access to variables are always faster than
     * a function call. When you need to call SSApplication methods often
     * using one of the static functions or the \c qApp macro the compiler
     * always need to save the current stack and add a new function call,
     * allocating stack space, return value, etc. Is better to build a local
     * variable and use it. Because of this we choose to use a global variable
     * that is just a pointer to the current instance allowing direct access
     * to the object.
     * @since 1.1
     **/
    extern SSApplication *App;
    /*}}}*/
};
///@} ssqt_ui_vars

#endif /* __SSQTAPP_HPP_DEFINED__ */
