#ifndef IWIDGET_GLOBAL_H
#define IWIDGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IWIDGET_LIBRARY)
#define IWIDGET_EXPORT Q_DECL_EXPORT
#else
#define IWIDGET_EXPORT Q_DECL_IMPORT
#endif

#endif // IWIDGET_GLOBAL_H
