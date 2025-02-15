#ifndef WELCOME_GLOBAL_H
#define WELCOME_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WELCOME_LIBRARY)
#define WELCOME_EXPORT Q_DECL_EXPORT
#else
#define WELCOME_EXPORT Q_DECL_IMPORT
#endif

#endif // WELCOME_GLOBAL_H
