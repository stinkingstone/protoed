
#include <string.h>
#include "BinBuf.h"


//namespace inoy
//{
    
BufWt::BufWt(const BufWt& bw)
{
    m_pszBuf = NULL;
	m_unLength = 0;
	m_unSize = 0;
	WriteBuf(bw.m_pszBuf, bw.m_unLength);
}

BufWt& BufWt::operator=(const BufWt& buf)
{
    Reset();
	WriteBuf(buf.m_pszBuf, buf.m_unLength);	
	return *this;
}

BufWt::BufWt()
{
    m_pszBuf = NULL;
	m_unLength = 0;
	m_unSize = 0;
}

BufWt::~BufWt()
{
    Reset();
}
bool BufWt::Expand(unsigned int  unLen)
{
	if (m_unSize-m_unLength<= unLen)
	{
	    unsigned int nTmpVal = unLen;
		nTmpVal += m_unSize;
		nTmpVal *=2;
		char * pszTmp = new char[nTmpVal];
		if(pszTmp){
			memset(pszTmp,0,nTmpVal);
			memcpy(pszTmp, m_pszBuf, m_unLength);
			delete[] m_pszBuf;
			m_pszBuf = pszTmp;
			m_unSize = nTmpVal;
			return true;
		}else{
		    return false;
		}
	}else{
	    return true;
	}
}

char*  BufWt::GetPos4Wt()
{
    if(m_pszBuf){
        return m_pszBuf+m_unLength;
    }else{
        return NULL;
    }
}

//Ð´Ö¸ÕëÆ«ÒÆ
unsigned int  BufWt::WtOffShift(unsigned int nOffset)
{
    m_unLength+=nOffset;
	return m_unLength;
}

void BufWt::Reset(){
	if(m_pszBuf){
		delete[] m_pszBuf;
		m_pszBuf = NULL;
		m_unLength = 0;
		m_unSize = 0;
	}
}

int BufWt::WriteBuf(const char* pszBuf, unsigned int unLen)
{
    if(Expand(unLen)){
		memcpy(m_pszBuf+m_unLength,pszBuf,unLen);
		m_unLength += unLen;
		return RT_OK;
    }else{
        //Ð´Êý¾ÝÊ§°Ü
        return RT_ERR;
    }
}

const char * BufWt::getBuf()
{
    return m_pszBuf;
}

unsigned int BufWt::getLength()
{
    return m_unLength;
}


BufRd::BufRd()
{
    m_pszBuf = NULL;
	m_unLength = 0;
	m_unCur = 0;
}

BufRd::~BufRd()
{

}

void BufRd::SetBuf(const char* pszBuf, unsigned int unLen)
{
    m_pszBuf = pszBuf;
	m_unLength = unLen;
}

int BufRd::ReadBuf(char* pszBuf, unsigned int unLen, unsigned int unOffset)
{
    if(m_unCur+unOffset+unLen>m_unLength){
		return RT_ERR;
    }else{
        memcpy(pszBuf,m_pszBuf+m_unCur+unOffset,unLen);
		m_unCur += unOffset;
		m_unCur += unLen;
		return RT_OK;
    }
}

const char* BufRd::GetPos4Rd()
{
    if(m_pszBuf){
        return m_pszBuf+m_unCur;
    }else{
        return NULL;
    }
}

//Ð´Ö¸ÕëÆ«ÒÆ
unsigned int  BufRd::RdOffShift(unsigned int nOffset)
{
    m_unCur += nOffset;
	return m_unCur;
}
		
//}
