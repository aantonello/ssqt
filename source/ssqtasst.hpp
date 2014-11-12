/**
 * \file
 * Declares assets global functions.
 *
 * \author Alessandro Antonello <aantonello@paralaxe.com.br>
 * \date   novembro 11, 2014
 * \since  Super Simple for Qt 5 1.1
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTASST_HPP_DEFINED__
#define __SSQTASST_HPP_DEFINED__

/**
 * \ingroup ssqt_funs
 * \defgroup ssqt_assets Assets
 * Provides access to application assets.
 * We call assets any resource that are in the application bundle or compiled
 * in the application executable. Assets means resources and this class has
 * some operations to aid find these resources easily.
 * @{ *//* ---------------------------------------------------------------- */
namespace ss {
// QString asset_string(uint resID, size_t size = 1024);/*{{{*/
/**
 * Loads a string from the executable resource.
 * @param resID The identifier of the string in the resource. Despite be an
 * unsigned integer number this value is limited in 16 bits. This limit is
 * imposed by the Windows resource format.
 * @param size Length of the string resource, in characters. Strings are
 * compiled in the resource using UTF-16 encoding. Each character occupies
 * 2 byte in memory. Qt handles Unicode strings natively. So, the returned
 * string will be in Qt's internal encoding. This argument is optional and, if
 * not passed, the default length is 1024 characters. Strings greater than
 * this length needs to have this value passed or it will be loaded truncated.
 * @return If the string is found in the executable resource it is returned in
 * a \c QString object. Otherwise an empty \c QString object is returned.
 * @remarks This operation works only on Windows when a standard resource (rc
 * file) is compiled into the executable. In others operating systems the
 * result will be always an empty \c QString object.
 * @since 1.1
 **/
QString asset_string(uint resID, size_t size = 1024);
/*}}}*/
};
///@} ssqt_assets

#endif /* __SSQTASST_HPP_DEFINED__ */
