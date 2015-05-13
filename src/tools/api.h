#ifndef _GST_API_H
#define _GST_API_H

#ifdef _MSC_VER
#ifdef _GSTAPI
#define GSTAPI __declspec(dllexport)
#else
#define GSTAPI __declspec(dllimport)
#endif
#else
#define GSTAPI
#endif

#endif /* _GST_API_H */
