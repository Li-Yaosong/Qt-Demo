#ifndef HDC_GLOBAL_H
#define HDC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HDC_LIBRARY)
#define HDC_EXPORT Q_DECL_EXPORT
#else
#define HDC_EXPORT Q_DECL_IMPORT
#endif

#endif // HDC_GLOBAL_H
