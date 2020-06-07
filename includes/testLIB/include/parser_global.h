#ifndef PARSER_GLOBAL_H
#define PARSER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PARSER_LIBRARY)
#  define PARSER_EXPORT Q_DECL_EXPORT
#else
#  define PARSER_EXPORT Q_DECL_IMPORT
#endif

#endif // PARSER_GLOBAL_H
