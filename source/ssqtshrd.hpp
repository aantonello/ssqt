/**
 * @file
 * Declares the SSSharedT template class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   dezembro 10, 2014
 * @since  Super Simple for Qt 5 1.2
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTSHRD_HPP_DEFINED__
#define __SSQTSHRD_HPP_DEFINED__

/**
 * This template implements a shared pointer.
 * It allows pointer of classes to be shared among the application using
 * a reference counting system. This system must be used only in heap
 * allocated instances. Not in stack allocated or temporary objects.
 *
 * When the standard constructor is called the reference count starts at 1.
 * That is, the creator of the instance is its owner. When another object
 * needs to retain the pointer while it is in use it should obtain the pointer
 * through the method #retain() that will increase the reference counting
 * ensuring the object will be available to it.
 *
 * All instances must not be deleted directly. Event by the owner/creator. All
 * classes that have a reference pointer should call the #release() method.
 * The instance will be automatically deleted (deallocated) when the last
 * retained reference calls that method.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
template <class T>
class SSSharedT
{
public:
    /** @name Defined Types */ //@{
    typedef T super;            /**< The super type. */
    //@}
public:
    /** @name Constructor */ //@{
    // SSSharedT();/*{{{*/
    /**
     * Default constructor.
     * Sets the reference count to 1.
     * @since 1.2
     **/
    SSSharedT() : m_refs(1) { }
    /*}}}*/
    //@}
public:
    /** @name Operations */ //@{
    // super* retain();/*{{{*/
    /**
     * Increments the reference count of this instance.
     * @returns \b this instance casted to the super type.
     * @since 1.2
     **/
    super* retain() {
        m_refs++;
        return (super*)this;
    }
    /*}}}*/
    // int release();/*{{{*/
    /**
     * Decreases the reference count of this instance.
     * @returns The number of references remaining.
     * @warning When the result value of this method is equals to or less than
     * zero this instance was deleted and is non longer valid.
     * @since 1.2
     **/
    int release() {
        int refCount = --m_refs;
        if (refCount <= 0)
            delete this;

        return refCount;
    }
    /*}}}*/
    //@}
public:
    /** @name Attributes */ //@{
    // int references() const;/*{{{*/
    /**
     * Retrieves the number of references of this instance.
     * @return An integer with the current number of references.
     * @since 1.2
     **/
    int references() const {
        return m_refs;
    }
    /*}}}*/
    //@}
private:
    int m_refs;                 /**< Holds the refence counting.        */
};

#endif /* __SSQTSHRD_HPP_DEFINED__ */
