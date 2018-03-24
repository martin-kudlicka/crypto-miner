#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MINERETHMINER_LIB)
#  define MINERETHMINER_EXPORT Q_DECL_EXPORT
# else
#  define MINERETHMINER_EXPORT Q_DECL_IMPORT
# endif
#else
# define MINERETHMINER_EXPORT
#endif
