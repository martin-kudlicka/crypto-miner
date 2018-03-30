#ifndef MINERXMRIGWIN32_GLOBAL_H
#define MINERXMRIGWIN32_GLOBAL_H

#include <QtCore/QtGlobal>

#ifndef BUILD_STATIC
# if defined(MINERXMRIGWIN32_LIB)
#  define MINERXMRIGWIN32_EXPORT Q_DECL_EXPORT
# else
#  define MINERXMRIGWIN32_EXPORT Q_DECL_IMPORT
# endif
#else
# define MINERXMRIGWIN32_EXPORT
#endif

#endif