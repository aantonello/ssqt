/**
 * \file
 * Error codes declaration.
 *
 * \author Alessandro Antonello <aantonello@paralaxe.com.br>
 * \date   novembro 10, 2014
 * \since  Super Simple for Qt 5 1.1
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTERR_HPP_DEFINED__
#define __SSQTERR_HPP_DEFINED__

/**
 * \ingroup ssqt_consts
 * \defgroup ssqt_errors Error Codes
 * Standard error codes.
 * List of all error codes used in this library with its meaning. We
 * declare/use the type \c error_t to identify an error code. Errors in this
 * library are always negative values to differenciate them from OS error
 * values. When a function or method member will return an OS error value it
 * will be explicitly told so. Otherwise all returned error values are in this
 * list.
 *
 * If an application needs to define its own set of error values and want to
 * follow the sequence of this list it should declare all number below the
 * value of \c SSE_APP. \c %SSE_APP has the value of -1000 and it should be
 * used to declare error values of an application in the following way:
 * ~~~~~~~~~~~~~~{.cpp}
#define APP_FIRST_ERROR_CODE    (SSE_APP - 1)
#define APP_SECOND_ERROR_CODE   (SSE_APP - 2)
 * ~~~~~~~~~~~~~~
 * @{ *//* ---------------------------------------------------------------- */
#define SSNO_ERROR          0   /**< Used when no errors occurs. */
#define SSE_PERM           -1   /**< Not super-user */
#define SSE_NOENT          -2   /**< No such file or directory */
#define SSE_SRCH           -3   /**< No such process */
#define SSE_INTR           -4   /**< Interrupted system call */
#define SSE_IO             -5   /**< I/O error */
#define SSE_NXIO           -6   /**< No such device or address */
#define SSE_2BIG           -7   /**< Arg list too long */
#define SSE_NOEXEC         -8   /**< Exec format error */
#define SSE_BADF           -9   /**< Bad file number */
#define SSE_CHILD          -10  /**< No children */
#define SSE_AGAIN          -11  /**< No more processes */
#define SSE_NOMEM          -12  /**< Not enough memory. */
#define SSE_ACCES          -13  /**< Permission denied */
#define SSE_FAULT          -14  /**< Bad address */
#define SSE_NOTBLK         -15  /**< Block device required */
#define SSE_BUSY           -16  /**< Mount device busy */
#define SSE_EXIST          -17  /**< File exists */
#define SSE_XDEV           -18  /**< Cross-device link */
#define SSE_NODEV          -19  /**< No such device */
#define SSE_NOTDIR         -20  /**< Not a directory */
#define SSE_ISDIR          -21  /**< Is a directory */
#define SSE_INVAL          -22  /**< Invalid argument */
#define SSE_NFILE          -23  /**< Too many open files in system */
#define SSE_MFILE          -24  /**< Too many open files */
#define SSE_NOTTY          -25  /**< Not a typewriter */
#define SSE_TXTBSY         -26  /**< Text file busy */
#define SSE_FBIG           -27  /**< File too large */
#define SSE_NOSPC          -28  /**< No space left on device */
#define SSE_SPIPE          -29  /**< Illegal seek */
#define SSE_ROFS           -30  /**< Read only file system */
#define SSE_MLINK          -31  /**< Too many links */
#define SSE_PIPE           -32  /**< Broken pipe */
#define SSE_DOM            -33  /**< Math arg out of domain of func */
#define SSE_RANGE          -34  /**< Math result not representable */
#define SSE_NOMSG          -35  /**< No message of desired type */
#define SSE_IDRM           -36  /**< Identifier removed */
#define SSE_CHRNG          -37  /**< Channel number out of range */
#define SSE_L2NSYNC        -38  /**< Level 2 not synchronized */
#define SSE_L3HLT          -39  /**< Level 3 halted */
#define SSE_L3RST          -40  /**< Level 3 reset */
#define SSE_LNRNG          -41  /**< Link number out of range */

#define SSE_UNATCH         -42  /**< Protocol driver not attached */
#define SSE_NOCSI          -43  /**< No CSI structure available */
#define SSE_L2HLT          -44  /**< Level 2 halted */
#define SSE_DEADLK         -45  /**< Deadlock condition */
#define SSE_NOLCK          -46  /**< No record locks available */
#define SSE_BADE           -50  /**< Invalid exchange */
#define SSE_BADR           -51  /**< Invalid request descriptor */
#define SSE_XFULL          -52  /**< Exchange full */
#define SSE_NOANO          -53  /**< No anode */
#define SSE_BADRQC         -54  /**< Invalid request code */
#define SSE_BADSLT         -55  /**< Invalid slot */
#define SSE_DEADLOCK       -56  /**< File locking deadlock error */
#define SSE_BFONT          -57  /**< Bad font file fmt */
#define SSE_NOSTR          -60  /**< Device not a stream */
#define SSE_NODATA         -61  /**< No data (for no delay io) */
#define SSE_TIME           -62  /**< Timer expired */
#define SSE_NOSR           -63  /**< Out of streams resources */
#define SSE_NONET          -64  /**< Machine is not on the network */
#define SSE_NOPKG          -65  /**< Package not installed */
#define SSE_REMOTE         -66  /**< The object is remote */
#define SSE_NOLINK         -67  /**< The link has been severed */
#define SSE_ADV            -68  /**< Advertise error */
#define SSE_SRMNT          -69  /**< Srmount error */
#define SSE_COMM           -70  /**< Communication error on send */
#define SSE_PROTO          -71  /**< Protocol error */
#define SSE_MULTIHOP       -74  /**< Multihop attempted */
#define SSE_LBIN           -75  /**< Inode is remote (not really error) */
#define SSE_DOTDOT         -76  /**< Cross mount point (not really error) */
#define SSE_BADMSG         -77  /**< Trying to read unreadable message */
#define SSE_FTYPE          -79  /**< Inappropriate file type or format */
#define SSE_NOTUNIQ        -80  /**< Given log. name not unique */
#define SSE_BADFD          -81  /**< f.d. invalid for this operation */
#define SSE_REMCHG         -82  /**< Remote address changed */
#define SSE_LIBACC         -83  /**< Can't access a needed shared lib */
#define SSE_LIBBAD         -84  /**< Accessing a corrupted shared lib */
#define SSE_LIBSCN         -85  /**< .lib section in a.out corrupted */
#define SSE_LIBMAX         -86  /**< Attempting to link in too many libs */
#define SSE_LIBEXEC        -87  /**< Attempting to exec a shared library */
#define SSE_NOSYS          -88  /**< Function not implemented */
#define SSE_NMFILE         -89  /**< No more files */
#define SSE_NOTEMPTY       -90  /**< Directory not empty */
#define SSE_NAMETOOLONG    -91  /**< File or path name too long */
#define SSE_LOOP           -92  /**< Too many symbolic links */
#define SSE_OPNOTSUPP      -95  /**< Operation not supported on transport endpoint */
#define SSE_PFNOSUPPORT    -96  /**< Protocol family not supported */
#define SSE_CONNRESET      -104 /**< Connection reset by peer */
#define SSE_NOBUFS         -105 /**< No buffer space available */
#define SSE_AFNOSUPPORT    -106 /**< Address family not supported by protocol family */
#define SSE_PROTOTYPE      -107 /**< Protocol wrong type for socket */
#define SSE_NOTSOCK        -108 /**< Socket operation on non-socket */
#define SSE_NOPROTOOPT     -109 /**< Protocol not available */
#define SSE_SHUTDOWN       -110 /**< Can't send after socket shutdown */
#define SSE_CONNREFUSED    -111 /**< Connection refused */
#define SSE_ADDRINUSE      -112 /**< Address already in use */
#define SSE_CONNABORTED    -113 /**< Connection aborted */
#define SSE_NETUNREACH     -114 /**< Network is unreachable */
#define SSE_NETDOWN        -115 /**< Network interface is not configured */
#define SSE_TIMEDOUT       -116 /**< Connection timed out */
#define SSE_HOSTDOWN       -117 /**< Host is down */
#define SSE_HOSTUNREACH    -118 /**< Host is unreachable */
#define SSE_INPROGRESS     -119 /**< Connection already in progress */
#define SSE_ALREADY        -120 /**< Socket already connected */
#define SSE_DESTADDRREQ    -121 /**< Destination address required */
#define SSE_MSGSIZE        -122 /**< Message too long */
#define SSE_PROTONOSUPPORT -123 /**< Unknown protocol */
#define SSE_SOCKTNOSUPPORT -124 /**< Socket type not supported */
#define SSE_ADDRNOTAVAIL   -125 /**< Address not available */
#define SSE_NETRESET       -126 /**< Netword connection was reset. */
#define SSE_ISCONN         -127 /**< Socket is already connected */
#define SSE_NOTCONN        -128 /**< Socket is not connected */
// define SSE_TOOMANYREFS    -129
// define SSE_PROCLIM        -130
// define SSE_USERS          -131
// define SSE_DQUOT          -132
// define SSE_STALE          -133
#define SSE_NOTSUP         -134 /**< Not supported */
#define SSE_NOMEDIUM       -135 /**< No medium (in tape drive) */
#define SSE_NOSHARE        -136 /**< No such host or network path */
#define SSE_CASECLASH      -137 /**< Filename exists with different case */
// define SSE_ILSEQ           -138
#define SSE_OVERFLOW       -139 /**< Value too large for defined data type */

#define SSE_WOULDBLOCK     E_AGAIN  /**< Used only withing socket errors. */

#define SSE_APP             -1000   /**< Limit for application errors.  */
///@} ssqt_errors
#endif /* __SSQTERR_HPP_DEFINED__ */
