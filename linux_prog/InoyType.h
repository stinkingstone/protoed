#ifndef __INOY_TYPE_H__
#define __INOY_TYPE_H__

#include <netinet/in.h>
#include <vector>
#include <map>
#include <string>

namespace inoy
{
/////////////////////////////////////////////////////////////////////////////////////
typedef bool    Bool;
typedef char    Char;
typedef short   Short;
typedef float   Float;
typedef double  Double;
typedef int     Int32;

typedef unsigned char   UInt8;
typedef unsigned short  UInt16;
typedef unsigned int    UInt32;

#if __WORDSIZE == 64
typedef long    Int64;
#else
typedef long long   Int64;
#endif


namespace inoy
{
        union bswap_helper
        {
                Int64   i64;
                Int32   i32[2];
        };
}
inline Int64 inoy_htonll(Int64 x)
{
        inoy::bswap_helper h;
        h.i64 = x;
        Int32 tmp = htonl(h.i32[1]);
        h.i32[1] = htonl(h.i32[0]);
        h.i32[0] = tmp;
        return h.i64;
}
inline Float inoy_ntohf(Float x)
{
    Int32 __t__ = htonl((*((Int32 *)&x)));
    return *((Float *) &__t__);
}

inline Double inoy_ntohd(Double x)
{
    Int64 __t__ = inoy_htonll((*((Int64 *)&x)));
    return *((Double *) &__t__);
}

#endif

//type2name
template<typename T> struct Class    { static std::string name() { return T::className(); } };
template<> struct Class<inoy::Bool>   { static std::string name() { return "bool"; } };
template<> struct Class<inoy::Char>   { static std::string name() { return "char"; } };
template<> struct Class<inoy::Short>  { static std::string name() { return "short"; } };
template<> struct Class<inoy::Float>  { static std::string name() { return "float"; } };
template<> struct Class<inoy::Double> { static std::string name() { return "double"; } };
template<> struct Class<inoy::Int32>  { static std::string name() { return "int32"; } };
template<> struct Class<inoy::Int64>  { static std::string name() { return "int64"; } };
template<> struct Class<inoy::UInt8>  { static std::string name() { return "short"; } };
template<> struct Class<inoy::UInt16> { static std::string name() { return "int32"; } };
template<> struct Class<inoy::UInt32> { static std::string name() { return "int64"; } };
template<> struct Class<std::string> { static std::string name() { return "string"; } };
template<typename T> struct Class<std::vector<T> > { static std::string name() { return std::string("list<") + Class<T>::name() + ">"; } };
template<typename T, typename U> struct Class<std::map<T, U> > { static std::string name() { return std::string("map<") + Class<T>::name() + "," + Class<U>::name() + ">"; } };

////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif

