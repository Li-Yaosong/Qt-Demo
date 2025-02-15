#ifndef OHREMOTE_GLOBAL_H
#define OHREMOTE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(OHREMOTE_LIBRARY)
#define OHREMOTE_EXPORT Q_DECL_EXPORT
#else
#define OHREMOTE_EXPORT Q_DECL_IMPORT
#endif

#endif // OHREMOTE_GLOBAL_H
