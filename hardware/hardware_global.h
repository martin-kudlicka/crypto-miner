#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HARDWARE_LIB)
#  define HARDWARE_EXPORT Q_DECL_EXPORT
# else
#  define HARDWARE_EXPORT Q_DECL_IMPORT
# endif
#else
# define HARDWARE_EXPORT
#endif
