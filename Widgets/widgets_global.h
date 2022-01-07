#ifndef WIDGETS_GLOBAL_H
#define WIDGETS_GLOBAL_H

#include <QtCore/qglobal.h>

// Makes the library available for other project inside the program
#if defined(WIDGETS_LIBRARY)
#  define WIDGETSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WIDGETSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WIDGETS_GLOBAL_H
