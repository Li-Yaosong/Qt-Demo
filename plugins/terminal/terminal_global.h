#ifndef TERMINAL_GLOBAL_H
#define TERMINAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TERMINAL_LIBRARY)
#define TERMINAL_EXPORT Q_DECL_EXPORT
#else
#define TERMINAL_EXPORT Q_DECL_IMPORT
#endif

#endif // TERMINAL_GLOBAL_H
