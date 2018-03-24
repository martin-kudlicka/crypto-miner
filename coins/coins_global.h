#ifndef COINS_GLOBAL_H
#define COINS_GLOBAL_H

#include <QtCore/QtGlobal>

#ifndef BUILD_STATIC
# if defined(COINS_LIB)
#  define COINS_EXPORT Q_DECL_EXPORT
# else
#  define COINS_EXPORT Q_DECL_IMPORT
# endif
#else
# define COINS_EXPORT
#endif

#endif