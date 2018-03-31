#ifndef MINERETHMINER_GLOBAL_H
#define MINERETHMINER_GLOBAL_H

#include <QtCore/QtGlobal>

#ifndef BUILD_STATIC
# if defined(MINERETHMINER_LIB)
#  define MINERETHMINER_EXPORT Q_DECL_EXPORT
# else
#  define MINERETHMINER_EXPORT Q_DECL_IMPORT
# endif
#else
# define MINERETHMINER_EXPORT
#endif

#endif