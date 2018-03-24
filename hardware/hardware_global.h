#ifndef HARDWARE_GLOBAL_H
#define HARDWARE_GLOBAL_H

#include <QtCore/QtGlobal>

#ifndef BUILD_STATIC
# if defined(HARDWARE_LIB)
#  define HARDWARE_EXPORT Q_DECL_EXPORT
# else
#  define HARDWARE_EXPORT Q_DECL_IMPORT
# endif
#else
# define HARDWARE_EXPORT
#endif

#endif