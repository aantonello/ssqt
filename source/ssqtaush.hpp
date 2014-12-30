/**
 * @file
 * Declares the SSAutoSharedT class template.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   dezembro 20, 2014
 * @since  Super Simple for Qt 5 1.2
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTAUSH_HPP_DEFINED__
#define __SSQTAUSH_HPP_DEFINED__

/**
 * Automatic reference counting shared pointer template class.
 * This template class is meant to be used with classes that extends \c
 * SSSharedT template class. The \c SSSharedT template class is used when
 * reference pointer classes are needed. Reference pointer classes are classes
 * intended to be used only as pointers to objects. Pointers to objects are
 * useful for shared content and operations. A shared pointer has a reference
 * counting control. Each object that needs to hold a reference to the pointer
 * calls the SSSharedT::retain() member function. When the pointer is non
 * longer needed the SSSharedT::release() member function is called. When the
 * reference counter reaches zero the pointer is automatically freed from
 * memory.
 *
 * To assist the use of a shared pointer the \c SSAutoSharedT template class
 * was created. It builds a value object. An object meant to be used in the
 * stack. Using its default parametrized constructor or the overloaded
 * operator '=' it retains the pointer of a shared object. When the \c
 * SSAutoSharedT object goes out of scope it releases the pointer to the
 * shared object, enabling it to be freed from memory.
 * @tparam _Ptr The type of shared object. Must extend the \c SSSharedT
 * template class.
 *//* --------------------------------------------------------------------- */
template <typename _Ptr>
class SSAutoSharedT
{
public:
    typedef shared_object _Ptr;

public:
    /** @name Constructors & Destructor */ //@{
    // explicit SSAutoSharedT(shared_object *ptr = NULL);/*{{{*/
    /**
     * Default constructor.
     * @param ptr Pointer to the shared object that extends \c SSSharedT. If
     * this pointer is not \b NULL it will be retained in this operation.
     * @since 1.2
     **/
    explicit SSAutoSharedT(shared_object *ptr = NULL) : m_ptr(ptr) {
        m_ptr = (ptr ? ptr->retain() : ptr);
    }
    /*}}}*/
    // SSAutoSharedT(const SSAutoSharedT<_Ptr> &other);/*{{{*/
    /**
     * Copy constructor.
     * @param other Another \c SSAutoSharedT object of the same type to be
     * copied. The reference count of the internal pointer will be
     * incremented.
     * @since 1.2
     **/
    SSAutoSharedT(const SSAutoSharedT<_Ptr> &other) : m_ptr(other.m_ptr) {
        m_ptr = (other ? other->retain() : NULL);
    }
    /*}}}*/
    // virtual ~SSAutoSharedT();/*{{{*/
    /**
     * Default destructor.
     * Releases the reference of the shared pointer object.
     * @since 1.2
     **/
    virtual ~SSAutoSharedT() {
        if (m_ptr) m_ptr->release();
    }
    /*}}}*/
    //@}
public:
    /** @name Operations */ //@{
    // SSAutoSharedT<_Ptr>& owned(shared_object *ptr);/*{{{*/
    /**
     * Sets or changes the reference pointer object.
     * @param ptr The pointer to be owned by this instance. This pointer is
     * not retained. Can be \b NULL.
     * @returns A reference of \b this object.
     * @remarks This method should be used when the shared pointer is already
     * retained. So this class doesn't retain it again.
     * @since 1.2
     **/
    SSAutoSharedT<_Ptr>& owned(shared_object *ptr) {
        if (m_ptr) m_ptr->release();
        m_ptr = ptr; return *this;
    }
    /*}}}*/
    // bool isNull() const;/*{{{*/
    /**
     * Checks whether the internal shared pointer is valid.
     * @returns \b true when the internal shared pointer is \b NULL. \b false
     * otherwise.
     * @since 1.2
     **/
    bool isNull() const {
        return (m_ptr == NULL);
    }
    /*}}}*/
    //@}
public:
    /** @name Overloaded Operators */ //@{
    // operator bool() const;/*{{{*/
    /**
     * Cast this object to a boolean type.
     * @return \b true when the internal shared pointer is valid. \b false
     * otherwise.
     * @remarks This operator helps to check when the internal pointer is
     * valid or not. It can be used in constructions like this:
     * ~~~~~~~~~~~~~~~{.cpp}
     * SSAutoSharedT<SomeType> autoShared(somePointer);
     * // Then, in another part of the code
     * if (autoShared)
     *     // do something with the SomeType pointer.
     * // The above construction is the same as
     * if (!autoShared.isNull())
     * ~~~~~~~~~~~~~~~
     * @since 1.2
     **/
    operator bool() const {
        return (m_ptr != NULL);
    }
    /*}}}*/
    // bool operator ==(const SSAutoSharedT<_Ptr> &other) const;/*{{{*/
    /**
     * Checks whether this object is equals to \a other.
     * @param other Other object to check for equality.
     * @return \b true when both objects hold references to the same shared
     * pointer. \b false otherwise. The operation also returns \b true when
     * the internal pointer is \b NULL on both objects.
     * @since 1.2
     **/
    bool operator ==(const SSAutoSharedT<_Ptr> &other) const {
        return (m_ptr == other.m_ptr);
    }
    /*}}}*/
    // bool operator ==(shared_object *ptr) const;/*{{{*/
    /**
     * Compare this object with a shared pointer.
     * @param ptr Shared pointer object to compare.
     * @return \b true when this instance has a reference to the passed shared
     * pointer object. \b false otherwise. The operation also returns \b true
     * when the internal pointer and the \a ptr parameter are \b NULL.
     * @remarks Besides checking the internal pointer reference equality this
     * operator also allows for constructions like:
     * ~~~~~~~~~~~~~~~{.cpp}
     * SSAutoSharedT<SomeType> autoShared(somePointer);
     * // Then, in another part of the code
     * if (autoShared == NULL)
     *     // do something when autoShared has no reference.
     * // The above construction is the same as
     * if (autoShared.isNull())
     * ~~~~~~~~~~~~~~~
     * @since 1.2
     **/
    bool operator ==(shared_object *ptr) const {
        return (m_ptr == ptr);
    }
    /*}}}*/
    // SSAutoSharedT<_Ptr>& operator =(shared_object *ptr);/*{{{*/
    /**
     * Assignment operator.
     * @param ptr The shared pointer object to be retained by this instance.
     * Can be \b NULL.
     * @return A reference of \b this object.
     * @remarks The \a ptr pointer is retained by this class.
     * @since 1.2
     **/
    SSAutoSharedT<_Ptr>& operator =(shared_object *ptr) {
        if (m_ptr) m_ptr->release();
        m_ptr = (ptr ? ptr->retain() : ptr);
        return *this;
    }
    /*}}}*/
    // shared_object* operator ->() const;/*{{{*/
    /**
     * Provides access to the internal object.
     * @returns The internal pointer object.
     * @remarks This operator allows access to the internal object pointer
     * data members and functions as of you where using it directly. Example:
     * ~~~~~~~~~~~~~~~{.cpp}
     * SSAutoSharedT<SomeType> autoShared(somePointer);
     * // Then, in another part of the code
     * if (autoShared)
     * {
     *     autoShared->somePointerMemberFunction();
     *     auto var = autoShared->somePointerDataMember;
     * }
     * ~~~~~~~~~~~~~~~
     * @since 1.2
     **/
    shared_object* operator ->() const {
        return m_ptr;
    }
    /*}}}*/
    //@}
protected:
    shared_object *m_ptr;
};

#endif /* __SSQTAUSH_HPP_DEFINED__ */
