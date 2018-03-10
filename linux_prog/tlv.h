#include <stdio.h>

#include <string>
using namespace std;

#define CHAR_POSITIVE_MAX    0x7f
#define SHORT_POSITIVE_MAX   0x7fff
#define INT_POSITIVE_MAX     0x7fffffff
#define LONG_POSITIVE_MAX     0x7fffffffffffffff

#define CHAR_SIGN_MASK_BIT   0x80
#define SHORT_SIGN_MASK_BIT  0x8000
#define INT_SIGN_MASK_BIT    0x80000000
#define LONG_SIGN_MASK_BIT   0x8000000000000000

#define TLV_TYPE_MASK        0xF0
#define TLV_LENGTH_MASK      0x0F

enum __METATYPE{
    MT_CHAR,    // 0  char                  1 byte data
    MT_SHORT,   // 1  short integer      2 bytes data
    MT_INT,     // 2  integer              4 bytes data
    MT_LONG,    // 3  long integer       8 bytes data
    MT_FLOAT,   // 4  float                 
    MT_DOUBLE,  // 5  double
    MT_STRINGS, // 6  string short 
    MT_STRINGL, // 7  string long 
    MT_STRUCT,  // 8  struct type
    MT_VECTOR,  // 9 vector type
    MT_MAP,     //  10map typ     
//    MT_BOOL,    // 1  bool                  1 byte data 
//    MT_ARR,     // 10  array typee
//	MT_INT32,	// 5  32 bit integer	 4 bytes data
//	MT_INT64,	// 6  64 bit integer	 8 bytes data
//	MT_INT128,	// 7  128 bit integer	16 bytes data
};

#define MT_BOOL   MT_CHAR

class tlv{
public:
    char m_ntl;
    char m_szValue[1];
public:
    void h2n();
    void n2h();
    int  getLength();//获取整个TLV的长度
    int  getTL(char& cT, char& cL);//获取T和V的值
    int  setValue(char cValue);
    int  setValue(bool bValue);
    int  setValue(short sValue);
    int  setValue(int nValue);
    int  setValue(long lValue);
    int  setValue(float fValue);
    int  setValue(double dValue);
    int  setValue(string csValue);
	int  setValue(char* pszValue, int nLen);
	int  setValue(int nType, char* pszValue, int nLen);
    int  getValue(char& cValue);
    int  getValue(bool& bValue);
    int  getValue(short& sValue);
    int  getValue(int& nValue);
    int  getValue(long& lValue);
    int  getValue(float& fValue);
    int  getValue(double& dValue);
    int  getValue(string& csValue);
	int  getValue(int nType, string& csValue);
private:
	int getLengthBytes();//获取长度字节数                   
};



