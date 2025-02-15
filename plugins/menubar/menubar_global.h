#ifndef MENUBAR_GLOBAL_H
#define MENUBAR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MENUBAR_LIBRARY)
#define MENUBAR_EXPORT Q_DECL_EXPORT
#else
#define MENUBAR_EXPORT Q_DECL_IMPORT
#endif

#endif // MENUBAR_GLOBAL_H
