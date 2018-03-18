#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(COINS_LIB)
#  define COINS_EXPORT Q_DECL_EXPORT
# else
#  define COINS_EXPORT Q_DECL_IMPORT
# endif
#else
# define COINS_EXPORT
#endif
