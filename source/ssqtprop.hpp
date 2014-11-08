/**
 * \file
 * Property template class.
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
#ifndef __SSQTPROP_HPP_DEFINED__
#define __SSQTPROP_HPP_DEFINED__

/**
 * \ingroup ssqt_templates
 * Template class for property like member implementation.
 * \tparam _Type The type of the property. This is the type of the value, like
 * the type of the member variable that will hold the value.
 *//* --------------------------------------------------------------------- */
template <typename _Type>
class property_t
{
public:
    typedef _Type value_type;

public:
    // property_t(void *owner);/*{{{*/
    /**
     * Default constructor.
     * @param owner The instance of the owner class object.
     * @remarks When this constructor is used the functions #getter() and/or
     * #setter() must be called to set the pointer to member functions.
     * Otherwise, the property object will become unusable.
     * @since 1.0
     **/
    property_t(void *owner) : m_owner(owner), set_func(NULL), get_func(NULL)
    { }
    /*}}}*/
    // property_t <class T> (T *owner, value_type (T::*getpfn)(), void (T::*setpfn)(const value_type&));/*{{{*/
    /**
     * Parametrized constructor.
     * @param owner The instance of the owner class object.
     * @param getpfn Pointer to the member function thats *get* the property
     * value.
     * @param setpfn Pointer to the member function thats *set* the property
     * value.
     * @since 1.0
     **/
    template <class T>
    property_t(T* owner, value_type (T::*getpfn)(), void (T::*setpfn)(const value_type&)) :
        m_owner(owner) {
        get_func = &getter_proxy<T, getpfn>;
        set_func = &setter_proxy<T, setpfn>;
    }
    /*}}}*/

public:
    // operator value_type() const;/*{{{*/
    /**
     * Casting operator.
     * Used in constructions like:
     * <pre>
     * value = object.property;
     * </pre>
     * @returns The property value.
     * @remarks When this operator is used the *getter* member function
     * defined will be called. Notice that if no *getter* function was
     * defined, the behavior will be undefined.
     * @since 1.0
     **/
    operator value_type() const {
        return (*get_func)(m_owner);
    }
    /*}}}*/
    // void operator=(const value_type&);/*{{{*/
    /**
     * Assignment operator.
     * This operator is used in constructions like:
     * <pre>
     * object.property = value;
     * </pre>
     * @param v The value to be passed to the *setter* function.
     * @remarks If a *setter* function was not defined, an "Assertion Failed!"
     * will be thrown in debug mode.
     * @since 1.0
     **/
    void operator=(const value_type &v) {
        (*set_func)(m_owner, v);
    }
    /*}}}*/

    // void getter <class T> (value_type (T::*getpfn)());/*{{{*/
    /**
     * Sets the getter function pointer.
     * @tparam T The type of the owner class. This can be suppressed in most
     * of the compilers since the type can be inferred by the passed argument.
     * @param getpfn The member function to call when the value of the
     * property is requested.
     * @since 1.0
     **/
    template <class T> void getter(value_type (T::*getpfn)()) {
        get_func = &getter_proxy<T, getpfn>;
    }
    /*}}}*/
    // void setter <class T> (void (T::*setpfn)(const value_type&));/*{{{*/
    /**
     * Sets the *setter* function pointer.
     * @tparam T The type of the owner class. This can be suppressed in most
     * compilers since the type can be inferred by the passed argument.
     * @param setpfn The member function to call when the value of the
     * property is about to change.
     * @since 1.0
     **/
    template <class T> void setter(void (T::*setpfn)(const value_type&)) {
        set_func = &setter_proxy<T, setpfn>;
    }
    /*}}}*/

private:
    typedef value_type (*getter_pfn)();
    typedef void (*setter_pfn)(const value_type &);

    void *m_owner;
    setter_pfn set_func;
    getter_pfn get_func;

    template <class T, value_type (T::*method)() >
    static value_type getter_proxy(void *owner) {
        T* p = static_cast<T*>(owner);
        return (p->*method)();
    }

    template <class T, void (T::*method)(const value_type&) >
    static void setter_proxy(void *owner, const value_type &val) {
        T* p = static_cast<T*>(owner);
        (p->*method)(val);
    }
};
/* Class documentation {{{ */
/**
 * \example sfprop01.h
 * The example shows how to declare a class with properties using this
 * template.
 * This class template allows constructions like ones offered by C#, C++/CLI
 * or Objective-C languages.
 * Although, on Objective-C, the property keyword is just a syntax sugar. In
 * C++ the only compiler that offers a similarly implementation is the
 * Microsoft C++ compiler with its `__declspec(property)` keyword.
 *
 * The \c property_t template class offers a solution using pointers to member
 * functions. When created, the property object needs to have a pointer to the
 * owner instance (the object that owns the value it self), a pointer to
 * a getter member function that will be called every time the property value
 * should be retrieved. And a pointer to a setter member function that will be
 * called every time the property value should be changed. The template
 * implementation will hold these three pointers to achieve what it is intended
 * to. So, for each property declared, there will be an overhead of 3 members
 * to pointers variables. Since the call to the getter and setter member
 * functions are made by an static template function, the compilers can
 * optimize the execution removing the overhead and producing a direct call to
 * the getter and setter member functions in the owner class. This is really
 * a fact when compiling in release mode. A good compiler will remove any
 * unnecessary code, since all types to members are known at compile time.
 *
 * The declaration shown in the example is simple and will not interfere with
 * code insight and others tools. The property is clearly only a member
 * variable as it should appear.
 *
 * \include sfprop01.cpp
 * When constructing the class you need to pass the instance pointer to the
 * property member variable constructor. As shown in the above example. Off
 * course, in the previous example there is no point to have a property
 * declared like that if we don't need any processing in a getter or setter
 * functions.
 *
 * \include sfprop02.h
 * The above example has a more clever implementation. It uses the property
 * `count` to return the size of the private list. Also, in the constructor,
 * we did not pass the member pointer. We pass that using the `getter()`
 * function and leave the setter with no definition. So we created a read only
 * property. See below:
 *
 * \include sfprop2.cpp
 * Unfortunately, when someone try to set the value of the `count` property,
 * the compiler will not issue an error nor warning. Instead of that the
 * overloaded `operator =` will issue an "Assertion Failed!" when compiled in
 * debug mode.
 **/
/* }}} Class documentation */

#endif /* __SSQTPROP_HPP_DEFINED__ */
