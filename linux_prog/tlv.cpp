#include "tlv.h"
#include<arpa/inet.h>
#include <string.h>

void tlv::h2n()
{
    char ctype=(m_ntl&0xF0)>>4;
    char clen = m_ntl&0x0F;
    int nLengthBytes = 0;
    switch(ctype){
    case MT_SHORT:
        switch(clen){
        case 2:
            *((short*)m_szValue)=htons(*((short*)m_szValue));
            break;
        }
        break;
    case MT_INT:
        switch(clen){
        case 2:
            *((short*)m_szValue)=htons(*((short*)m_szValue));
            break;
        case 4:
            *((int*)m_szValue)=htonl(*((int*)m_szValue));
            break;
        }
        break;
    case MT_LONG:
        switch(clen){
        case 2:
            *((short*)m_szValue)=htons(*((short*)m_szValue));
            break;
        case 4:
            *((int*)m_szValue)=htonl(*((int*)m_szValue));
            break;
        case 8:
            if(sizeof(long)==8){
                *((long*)m_szValue)=htonl(*((long*)m_szValue));
            }else{
                      //*(int64_t*(m_szValue))=htonl(*(int64_t*(m_szValue)));
            }
            break;
        }
        break;
#if 0
        case MT_INT32:
              switch(clen){
              case 2:
                    *((short*)m_szValue)=htons(*((short*)m_szValue));
                    break;
              case 4:
                    *((int*)m_szValue)=htonl(*((int*)m_szValue));
                    //*(int32_t*(m_szValue))=htonl(*(int32_t*(m_szValue)));
                    break;
              }
              break;
        case MT_INT64:
              switch(clen){
              case 2:
                    *((short*)m_szValue)=htons(*((short*)m_szValue));
                    break;
              case 4:
                    *((int*)m_szValue)=htonl(*((int*)m_szValue));
                    break;
              case 8:
                    //*(int64_t*(m_szValue))=htonl(*(int64_t*(m_szValue)));
                    break;
              }
              break;
#endif              
    case MT_STRINGL:
    case MT_STRUCT:
    case MT_VECTOR:
    case MT_MAP:
        nLengthBytes = getLengthBytes();
        switch(nLengthBytes){
        case 2:
            *((short*)m_szValue)=htons(*((short*)m_szValue));
            break;
        case 4:
            *((int*)m_szValue)=htonl(*((int*)m_szValue));
            break;
        case 8:
            *((long*)m_szValue)=htonl(*((long*)m_szValue));
            break;
        }
    default:
         break;              
    }
}

void tlv::n2h()
{
    char ctype=(m_ntl&0xF0)>>4;
    char clen = m_ntl&0x0F;
    int nLengthBytes = 0;
    switch(ctype){
    case MT_SHORT:
        switch(clen){
        case 2:
            *((short*)m_szValue)=ntohs(*((short*)m_szValue));
            break;
        }
        break;
    case MT_INT:
        switch(clen){
        case 2:
            *((short*)m_szValue)=ntohs(*((short*)m_szValue));
            break;
        case 4:
            *((int*)m_szValue)=ntohl(*((int*)m_szValue));
            break;
        }
        break;
    case MT_LONG:
        switch(clen){
        case 2:
            *((short*)m_szValue)=ntohs(*((short*)m_szValue));
            break;
        case 4:
            *((int*)m_szValue)=ntohl(*((int*)m_szValue));
            break;
        case 8:
 //           if(sizeof(long)==8){
                *((long*)m_szValue)=ntohl(*((long*)m_szValue));
 //           }else{
 //               *(int64_t*(m_szValue))=ntohl(*(int64_t*(m_szValue)));
 //           }
            break;
        }
        break;
#if 0              
        case MT_INT32:
              switch(clen){
              case 2:
                    *((short*)m_szValue)=ntohs(*((short*)m_szValue));
                    break;
              case 4:
                    *(int32_t*(m_szValue))=ntohl(*(int32_t*(m_szValue)));
                    break;
              }
              break;
        case MT_INT64:
              switch(clen){
              case 2:
                    *((short*)m_szValue)=ntohs(*((short*)m_szValue));
                    break;
              case 4:
                    *((int*)m_szValue)=ntohl(*((int*)m_szValue));
                    break;
              case 8:
                    *(int64_t*(m_szValue))=ntohl(*(int64_t*(m_szValue)));
                    break;
              }
              break;
#endif              
    case MT_STRINGL:
    case MT_STRUCT:
    case MT_VECTOR:
    case MT_MAP:
        nLengthBytes = getLengthBytes();
        switch(nLengthBytes){
        case 2:
            *((short*)m_szValue)=ntohs(*((short*)m_szValue));
            break;
        case 4:
            *((int*)m_szValue)=ntohl(*((int*)m_szValue));
            break;
        case 8:
            *((long*)m_szValue)=ntohl(*((long*)m_szValue));
            break;
        }
        break;
    default:
        break;              
    }
}

int  tlv::getLengthBytes()
{
    int nBytes = 0;
    char ctype=(m_ntl&0xF0)>>4;
    switch(ctype){
    case MT_STRINGL:
    case MT_STRUCT:
        nBytes = m_ntl&0x0F;
        break;
    default:
        nBytes = 0;
        break;
    }
    return nBytes;
}

int  tlv::getLength()
{
    int nLen = 1;
    int nBytes = 0;
    char ctype=(m_ntl&0xF0)>>4;
    nBytes = m_ntl&0x0F; //数据所占字节数 
    switch(ctype){
    case MT_STRINGL:
    case MT_STRUCT:
        switch(nBytes){//对于MT_STRINGL类型，则nBytes此时表示字符串长度记数器所占字节数
        case 1:
            nLen += *((char*)m_szValue);//字符串所占字节数
            break;
        case 2:
            nLen += *((short*)m_szValue);//字符串所占字节数
            break;
        case 4:
            nLen += *((int*)m_szValue);//字符串所占字节数
            break;
        case 8:
            nLen += *((long*)m_szValue);//字符串所占字节数
            break;                                
        }
        break;
    default:
        nBytes = 0;
        break;
    } 
    return (nLen+nBytes);
}

int  tlv::getTL(char& cT, char &nL)
{
    cT=(m_ntl&0xF0)>>4;
    nL = m_ntl&0x0F;
    int nBytes = 0;
    switch(cT){
    case MT_STRINGL:
    case MT_STRUCT:
        nBytes = m_ntl&0x0F;
        switch(nBytes){
        case 1:
            nL = *((char*)m_szValue);
            break;
        case 2:
            nL = *((short*)m_szValue);
            break;
        case 4:
            nL = *((int*)m_szValue);
            break;
        case 8:
            nL = *((long*)m_szValue);
            break;                                
        }
        break;
    default:
        nBytes = 0;
        break;
    } 
    return 0;
}

//返回值:tlv所占字节数
int  tlv::setValue(char cValue)
{
    m_ntl = 0;
	m_ntl = MT_CHAR<<4;
	bool bNegative = false;
	char cValue2=cValue;
	if(cValue2<0){
		bNegative=true;
		cValue2 = -cValue2;
	}
    if(cValue2==0){
        m_ntl |= 0;
        return 1;
    }else{
        if(bNegative){
            *((char*)m_szValue) = cValue2|CHAR_SIGN_MASK_BIT;
		}else{
	        *((char*)m_szValue) = cValue2;
        }
		m_ntl |= 1;
		return 2;
    }        
}

//返回值:tlv所占字节数
int  tlv::setValue(bool bValue)
{
    m_ntl = 0;
	m_ntl = MT_BOOL<<4;
    if(bValue==0){
        m_ntl |= 0;
        return 1;
    }else{
        *((bool*)m_szValue) = bValue;
		m_ntl |= 1;
        return 2;
    } 
}

//返回值:tlv所占字节数
int  tlv::setValue(short sValue)
{
    short sValue2=sValue;
    bool bNegative = false;
    m_ntl = MT_SHORT<<4;
    if(sValue2<0){
        bNegative = true;
        sValue2 = -sValue2;
    }
    if(sValue==0){
        return 1;
    }else{
        if(bNegative){
            if(sValue2<=CHAR_POSITIVE_MAX){
                *((char*)m_szValue) = sValue2|CHAR_SIGN_MASK_BIT;
                m_ntl |= 1; 
                return 2;
            }else{
                *((short*)m_szValue) = sValue2|SHORT_SIGN_MASK_BIT;
                m_ntl |= 2;
                return 3; 
            }
        }else{
            if(sValue2<=CHAR_POSITIVE_MAX){
                *((char*)m_szValue) = sValue2;
                m_ntl |= 1;
                return 2; 
            }else{
                *((short*)m_szValue) = sValue2;
                m_ntl |= 2;
                return 3; 
            }
        }
    } 
}

//返回值:tlv所占字节数
int  tlv::setValue(int nValue)
{
    int nValue2=nValue;
    bool bNegative = false;
    m_ntl = MT_INT<<4;
    if(nValue2<0){
        bNegative = true;
        nValue2 = -nValue2;
    }
    if(nValue2==0){
        return 1;
    }else{
        if(bNegative){
            if(nValue2<=CHAR_POSITIVE_MAX){
                *((char*)m_szValue) = nValue2;
				*((char*)m_szValue) |= CHAR_SIGN_MASK_BIT;
                m_ntl |= 1; 
                return 2;
            }else if(nValue2<=SHORT_POSITIVE_MAX){
                *((short*)m_szValue) = nValue2;
				*((short*)m_szValue) |= SHORT_SIGN_MASK_BIT;
                m_ntl |= 2;
                return 3; 
            }else {
                *((int*)m_szValue) = nValue2;
				*((int*)m_szValue) |= INT_SIGN_MASK_BIT;
                m_ntl |= 4;
                return 5; 
            }
        }else{
            if(nValue2<=CHAR_POSITIVE_MAX){
                m_ntl |= 1; 
                *((char*)m_szValue) = nValue2;
                return 2;
            }else if(nValue2<=SHORT_POSITIVE_MAX){
                m_ntl |= 2;
                *((short*)m_szValue) = nValue2;
                return 3; 
            }else {
                m_ntl |= 4;
                *((int*)m_szValue) = nValue2;
                return 5; 
            }
        }
    }    
}

//返回值:tlv所占字节数
int  tlv::setValue(long lValue)
{
    long lValue2=lValue;
    bool bNegative = false;
        m_ntl = MT_LONG<<4;
    if(lValue2<0){
        bNegative = true;
        lValue2 = -lValue2;
    }
    if(lValue==0){
        return 1;
    }else{
        if(bNegative){
            if(lValue2<=CHAR_POSITIVE_MAX){
                *((char*)m_szValue) = lValue2;
				*((char*)m_szValue) |= CHAR_SIGN_MASK_BIT;
                m_ntl |= 1;
                return 2; 
            }else if(lValue2<=SHORT_POSITIVE_MAX){
                *((short*)m_szValue) = lValue2;
				*((short*)m_szValue) |= SHORT_SIGN_MASK_BIT;
                m_ntl |= 2;
                return 3; 
            }else if(lValue2<=INT_POSITIVE_MAX){
                *((int*)m_szValue) = lValue2;
				*((int*)m_szValue) |= INT_SIGN_MASK_BIT;
                m_ntl |= 4;
                return 5; 
            }else {
                *((long*)m_szValue) = lValue2;
				*((long*)m_szValue) |= LONG_SIGN_MASK_BIT;
                m_ntl |= 8;
                return 9; 
            }
        }else{
            if(lValue2<=CHAR_POSITIVE_MAX){
                m_ntl |= 1;
                *((char*)m_szValue) = lValue2;
                return 2; 
            }else if(lValue2<=SHORT_POSITIVE_MAX){
                m_ntl |= 2;
                *((short*)m_szValue) = lValue2;
                return 3; 
            }else if(lValue2<=INT_POSITIVE_MAX){
                m_ntl |= 4;
                *((int*)m_szValue) = lValue2;
                return 5; 
            }else {
                m_ntl |= 8; 
                *((long*)m_szValue) = lValue2;
                return 9;
            }
        }
    }    
}

//返回值:tlv所占字节数
int  tlv::setValue(float fValue)
{
    m_ntl = MT_FLOAT<<4;
    *((float*)m_szValue) = fValue;
    m_ntl |= sizeof(float);
    return 1+sizeof(float);
}

//返回值:tlv所占字节数
int  tlv::setValue(double dValue)
{
    m_ntl = MT_DOUBLE<<4;
    *((double*)m_szValue) = dValue;
    m_ntl |= sizeof(double);
    return 1+sizeof(double);
}

//返回值:tlv所占字节数
int  tlv::setValue(string csValue)
{
    if(csValue.length()<=15){
        m_ntl = MT_STRINGS<<4;
        m_ntl |= csValue.length();
        memcpy(m_szValue,csValue.c_str(),csValue.length());
        return 1+csValue.length();
    }else{
        m_ntl = MT_STRINGL<<4;
        if(csValue.length()<=0xff){
            m_ntl |= 1;
            *((char*)m_szValue) = csValue.length();
            memcpy(&m_szValue[1],csValue.c_str(),csValue.length());
            return 2+csValue.length();
        }else if(csValue.length()<=0xffff){
            m_ntl |= 2;                    
            *((short*)m_szValue) = csValue.length();
            memcpy(&m_szValue[2],csValue.c_str(),csValue.length());
            return 3+csValue.length();
        }else if(csValue.length()<=0xffffffff){
            m_ntl |= 4;
            *((int*)m_szValue) = csValue.length();
            memcpy(&m_szValue[4],csValue.c_str(),csValue.length());
            return 5+csValue.length();
        }else if(csValue.length()<=0xffffffffffffffff){
            m_ntl |= 8;
            *((long*)m_szValue) = csValue.length();
            memcpy(&m_szValue[8],csValue.c_str(),csValue.length());
            return 9+csValue.length();
        }
    }
}


int  tlv::setValue(char* pszValue, int nLen)
{
    if(nLen<=15){
        m_ntl = MT_STRINGS<<4;
        m_ntl |= nLen;
        memcpy(m_szValue,pszValue,nLen);
        return 1+nLen;
    }else{
        m_ntl = MT_STRINGL<<4;
        if(nLen<=0xff){
            m_ntl |= 1;
            *((char*)m_szValue) = nLen;
            memcpy(&m_szValue[1],pszValue,nLen);
            return 2+nLen;
        }else if(nLen<=0xffff){
            m_ntl |= 2;                  
            *((short*)m_szValue) = nLen;
            memcpy(&m_szValue[2],pszValue,nLen);
            return 3+nLen;
        }else if(nLen<=0xffffffff){
            m_ntl |= 4;
            *((int*)m_szValue) = nLen;
            memcpy(&m_szValue[4],pszValue,nLen);
            return 5+nLen;
        }else if(nLen<=0xffffffffffffffff){
            m_ntl |= 8;
            *((long*)m_szValue) = nLen;
            memcpy(&m_szValue[8],pszValue,nLen);
            return 9+nLen;
        }
    }

}

int  tlv::setValue(int nType, char* pszValue, int nLen)
{
    switch(nType){
    case MT_STRUCT:
	case MT_VECTOR:
	case MT_MAP:
        m_ntl = nType<<4;
        if(nLen<=0xff){
            m_ntl |= 1;
            *((char*)m_szValue) = nLen;
            memcpy(&m_szValue[1],pszValue,nLen);
            return 2+nLen;
        }else if(nLen<=0xffff){
            m_ntl |= 2;                  
            *((short*)m_szValue) = nLen;
            memcpy(&m_szValue[2],pszValue,nLen);
            return 3+nLen;
        }else if(nLen<=0xffffffff){
            m_ntl |= 4;
            *((int*)m_szValue) = nLen;
            memcpy(&m_szValue[4],pszValue,nLen);
            return 5+nLen;
        }else if(nLen<=0xffffffffffffffff){
            m_ntl |= 8;
            *((long*)m_szValue) = nLen;
            memcpy(&m_szValue[8],pszValue,nLen);
            return 9+nLen;
        }
		break;
    }
}
#if 0
int  tlv::setValue(int nType, int nElemNum, char* pszValue, int nLen)
{
    switch(nType){
    case MT_VECTOR:
        m_ntl = MT_VECTOR<<4;
        if(nLen<=0xff){
            m_ntl |= 1;
            *((char*)m_szValue) = nLen;
            memcpy(&m_szValue[1],pszValue,nLen);
            return 2+nLen;
        }else if(nLen<=0xffff){
            m_ntl |= 2;                  
            *((short*)m_szValue) = nLen;
            memcpy(&m_szValue[2],pszValue,nLen);
            return 3+nLen;
        }else if(nLen<=0xffffffff){
            m_ntl |= 4;
            *((int*)m_szValue) = nLen;
            memcpy(&m_szValue[4],pszValue,nLen);
            return 5+nLen;
        }else if(nLen<=0xffffffffffffffff){
            m_ntl |= 8;
            *((long*)m_szValue) = nLen;
            memcpy(&m_szValue[8],pszValue,nLen);
            return 9+nLen;
        }
    }
}
#endif

//返回值:tlv所占字节数
int  tlv::getValue(char& cValue)
{
    char cType = (m_ntl&TLV_TYPE_MASK)>>4; 
    char cLength = m_ntl&TLV_LENGTH_MASK;
    if(cType==MT_CHAR){
        if(cLength ==0){
            cValue = 0;
            return 1;
        }else if(cLength==1){
            cValue = *((char*)m_szValue);
			if(cValue&CHAR_SIGN_MASK_BIT){
				cValue &= CHAR_POSITIVE_MAX;
				cValue = -cValue;
			}
            return 2;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

//返回值:tlv所占字节数
int  tlv::getValue(bool& bValue)
{
    char cType = (m_ntl&TLV_TYPE_MASK)>>4; 
    char cLength = m_ntl&TLV_LENGTH_MASK;
    if(cType==MT_BOOL){
        if(cLength ==0){
            bValue = 0;
            return 1;
        }else if(cLength==1){
            bValue = *((bool*)m_szValue);
            return 2;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

//返回值:tlv所占字节数
int  tlv::getValue(short& sValue)
{
    char cType = (m_ntl&TLV_TYPE_MASK)>>4; 
    char cLength = m_ntl&TLV_LENGTH_MASK;
    if(cType==MT_SHORT){
        if(cLength == 0){
            sValue = 0;
            return 1;
        }else if(cLength==1){
            sValue = *((char*)m_szValue);
			if(sValue&CHAR_SIGN_MASK_BIT){
				sValue &= CHAR_POSITIVE_MAX;
				sValue = -sValue;
			}
            return 2;
        }else if(cLength==2){
            sValue = *((short*)m_szValue);
			if(sValue&SHORT_SIGN_MASK_BIT){
				sValue &= SHORT_POSITIVE_MAX;
				sValue = -sValue;
			}
            return 3;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

//返回值:tlv所占字节数
int  tlv::getValue(int& nValue)
{
    char cType = (m_ntl&TLV_TYPE_MASK)>>4; 
    char cLength = m_ntl&TLV_LENGTH_MASK;
    if(cType==MT_INT){
        if(cLength == 0){
            nValue = 0;
            return 1;
        }else if(cLength==1){
            nValue = *((char*)m_szValue);
			if(nValue&CHAR_SIGN_MASK_BIT){
				nValue &= CHAR_POSITIVE_MAX;
				nValue = -nValue;
			}
            return 2;
        }else if(cLength==2){
            nValue = *((short*)m_szValue);
			if(nValue&SHORT_SIGN_MASK_BIT){
				nValue &= SHORT_POSITIVE_MAX;
				nValue = -nValue;
			}
            return 3;
        }else if(cLength==4){
            nValue = *((int*)m_szValue);
			if(nValue&INT_SIGN_MASK_BIT){
				nValue &= INT_POSITIVE_MAX;
				nValue = -nValue;
			}
            return 5;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

//返回值:tlv所占字节数
int  tlv::getValue(long& lValue)
{
    char cType = (m_ntl&TLV_TYPE_MASK)>>4; 
    char cLength = m_ntl&TLV_LENGTH_MASK;
    if(cType==MT_LONG){
        if(cLength == 0){
            lValue = 0;
            return 1;
        }else if(cLength==1){
            lValue = *((char*)m_szValue);
			if(lValue&CHAR_SIGN_MASK_BIT){
				lValue &= CHAR_POSITIVE_MAX;
				lValue = -lValue;
			}
            return 2;
        }else if(cLength==2){
            lValue = *((short*)m_szValue);
			if(lValue&SHORT_SIGN_MASK_BIT){
				lValue &= SHORT_POSITIVE_MAX;
				lValue = -lValue;
			}
            return 3;
        }else if(cLength==4){
            lValue = *((int*)m_szValue);
			if(lValue&INT_SIGN_MASK_BIT){
				lValue &= INT_POSITIVE_MAX;
				lValue = -lValue;
			}
            return 5;
        }else if(cLength==8){
            lValue = *((long*)m_szValue);
			if(lValue&LONG_SIGN_MASK_BIT){
				lValue &= INT_POSITIVE_MAX;
				lValue = -lValue;
			}
            return 9;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

//返回值:tlv所占字节数
int  tlv::getValue(float& fValue)
{
    char cType = (m_ntl&TLV_TYPE_MASK)>>4; 
    char cLength = m_ntl&TLV_LENGTH_MASK;
    if(cType==MT_FLOAT){
        if(cLength == 0){
            fValue = 0;
            return 0;
        }else {
            fValue = *((float*)m_szValue);
            return (1+sizeof(float));
        }
    }else{
        return 0;
    }
}

//返回值:tlv所占字节数
int  tlv::getValue(double& dValue)
{
    char cType = (m_ntl&TLV_TYPE_MASK)>>4; 
    char cLength = m_ntl&TLV_LENGTH_MASK;
    if(cType==MT_DOUBLE){
        if(cLength == 0){
            dValue = 0;
            return 1;
        }else {
            dValue = *((double*)m_szValue);
            return 1+sizeof(double);
        }
    }else{
        return 0;
    }
}

//返回值:tlv所占字节数
int  tlv::getValue(string& csValue)
{
    char cType = (m_ntl&TLV_TYPE_MASK)>>4; 
    char cLength = m_ntl&TLV_LENGTH_MASK;
    long lLen = 0;
    if(cType==MT_STRINGS){
        if(cLength==0){
            csValue.clear();
            return 1;
        }else{
            csValue.append(m_szValue,cLength);
            return 1+cLength;
        }
    }else if(cType==MT_STRINGL){
        if(cLength==0){
            return 0;
        }else{
            if(cLength==1){
                lLen = *((char*)m_szValue);                        
            }else if(cLength==2){
                lLen = *((short*)m_szValue);
            }else if(cLength==4){
                lLen = *((int*)m_szValue);
            }else if(cLength==8){
                lLen = *((long*)m_szValue);
            }else{
                return 0;//现在不支持的数据类型
            }
            csValue.append(&m_szValue[cLength],lLen);
            return 1+lLen+cLength;
        }
    }
}


int  tlv::getValue(int nType, string& csValue)
{
    char cType = (m_ntl&TLV_TYPE_MASK)>>4; 
    char cLength = m_ntl&TLV_LENGTH_MASK;
    long lLen = 0;
	if(cType != nType){
		return 0;
	}
	switch(nType){
	case MT_STRUCT:
	case MT_VECTOR:
	case MT_MAP:
		if(cLength==0){
            return 0;
        }else{
            if(cLength==1){
                lLen = *((char*)m_szValue);                        
            }else if(cLength==2){
                lLen = *((short*)m_szValue);
            }else if(cLength==4){
                lLen = *((int*)m_szValue);
            }else if(cLength==8){
                lLen = *((long*)m_szValue);
            }else{
                return 0;//现在不支持的数据类型
            }
            csValue.append(&m_szValue[cLength],lLen);
            return 1+lLen+cLength;
        }
		break;
    }

}





