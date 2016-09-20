#ifndef _XYAH_COMPARABLE_H_
#define _XYAH_COMPARABLE_H_

#define BIGGER 1
#define LOWER -1
#define EQUALS 0

typedef short (*FGenericCompare)(void *, void *);

typedef struct comparable {
  void *data;
  FGenericCompare compare;
} IComparable;

short compare(IComparable *, IComparable *);

#endif ///_XYAH_COMPARABLE_H_
