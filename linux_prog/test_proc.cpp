
#include "Test_proc.h"


int MyTest::set(int nFd,
		long lFd,
		string csFd)
{
    m_nFd = nFd;
	m_lFd = lFd;
	m_csFd = csFd;
}

int MyTest::get(int& nFd,
				long& lFd,
				string& csFd)
{
    nFd = m_nFd;
	lFd = m_lFd;
	csFd = m_csFd;
}

void MyTest::encode(Buf4ProtoEncode& cByteBuf)
{
    cByteBuf.PushBack(m_nFd);
	cByteBuf.PushBack(m_lFd);
	cByteBuf.PushBack(m_csFd);
	cByteBuf.PushBack(m_csFd2);
	cByteBuf.PushBack(m_csFd3);
}

void MyTest::decode(Buf4ProtoDecode& cByteBuf)
{
    cByteBuf.PopAhead(m_nFd);
	cByteBuf.PopAhead(m_lFd);
	cByteBuf.PopAhead(m_csFd);
	cByteBuf.PopAhead(m_csFd2);
	cByteBuf.PopAhead(m_csFd3);
}


int Test1::set(int nfd, short nsfd, char cfd, long lfd, string csfd)
{
    m_nFd = nfd;
	m_nsFd = nsfd;
	m_cFd = cfd;
	m_lFd = lfd;
	m_csFd = csfd;
}
int Test1::get(int &nfd, short& nsfd, char& cfd, long &lfd, string &csfd)
{
    nfd = m_nFd;
	nsfd = m_nsFd;
	cfd = m_cFd;
	lfd = m_lFd;
	csfd = m_csFd;
}

void Test1::encode(Buf4ProtoEncode& cByteBuf)
{
    cByteBuf.PushBack(m_nFd);
	cByteBuf.PushBack(m_nsFd);
	cByteBuf.PushBack(m_cFd);
	cByteBuf.PushBack(m_lFd);
	cByteBuf.PushBack(m_csFd);
	cByteBuf.PushBack(m_cMyTest);
	cByteBuf.PushBack(m_dFd);
	cByteBuf.PushBack(m_fFd);
	cByteBuf.PushBack(m_bFd);
}

void Test1::decode(Buf4ProtoDecode& cByteBuf)
{
    cByteBuf.PopAhead(m_nFd);
	cByteBuf.PopAhead(m_nsFd);
	cByteBuf.PopAhead(m_cFd);
	cByteBuf.PopAhead(m_lFd);
	cByteBuf.PopAhead(m_csFd);
	cByteBuf.PopAhead(m_cMyTest);
	cByteBuf.PopAhead(m_dFd);
	cByteBuf.PopAhead(m_fFd);
	cByteBuf.PopAhead(m_bFd);
}


int Test2::set(int nfd, vector<int> vecFd)
{
    m_nFd = nfd;
	m_vecFd = vecFd;
}

int Test2::get(int &nfd, vector<int> &vecFd)
{
     nfd = m_nFd;
	 vecFd= m_vecFd;
}
/*
int Test2::set(map<int,string> mapFd)
{
    m_mapFd = mapFd;
}

int Test2::get(map<int,string>& mapFd)
{
    mapFd = m_mapFd;
}
*/
void Test2::encode(Buf4ProtoEncode& cByteBuf)
{
     cByteBuf.PushBack(m_nFd);
	 cByteBuf.PushBack(m_vecFd);
//	 cByteBuf.PushBackMap(m_mapFd);
}

void Test2::decode(Buf4ProtoDecode& cByteBuf)
{
    cByteBuf.PopAhead(m_nFd);
	cByteBuf.PopAhead(m_vecFd);	
//	cByteBuf.PopAheadMap(m_mapFd);
}




