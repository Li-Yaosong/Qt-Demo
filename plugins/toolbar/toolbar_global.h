#ifndef TOOLBAR_GLOBAL_H
#define TOOLBAR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TOOLBAR_LIBRARY)
#define TOOLBAR_EXPORT Q_DECL_EXPORT
#else
#define TOOLBAR_EXPORT Q_DECL_IMPORT
#endif

#endif // TOOLBAR_GLOBAL_H
