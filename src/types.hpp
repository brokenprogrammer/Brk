#ifndef BRK_TYPES_HPP
#define BRK_TYPES_HPP

typedef unsigned long long integer_t;
typedef long double real_t;

typedef unsigned char       brk_uint8;
typedef signed char         brk_int8;
typedef unsigned short      brk_uint16;
typedef short               brk_int16;
typedef unsigned int        brk_uint32;
typedef int                 brk_int32;
typedef unsigned long long  brk_uint64;
typedef long long           brk_int64;

typedef float               brk_float32;
typedef double              brk_float64;
typedef long double         brk_float80;

enum BasicTypes {
    //TODO: Class, struct, enum, pointer, reference, function.. Oskar Mendel 2018-03-30

    BASIC_NONE,
    BASIC_VOID,

    BASIC_INT8,
    BASIC_UINT8,
    BASIC_INT16,
    BASIC_UINT16,
    BASIC_INT32,
    BASIC_UINT32,
    BASIC_INT64,
    BASIC_UINT64,

    BASIC_FLOAT32,
    BASIC_FLOAT64,

    BASIC_BYTE,
    BASIC_CHAR,
    BASIC_STRING,

    BASIC_MAX
};

#endif //BRK_TYPES_HPP