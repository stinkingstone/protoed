//#include "BinBuf.h"
#include <string>
#include "ProtocolBase.h"
#include <map>
#include <vector>
//#include "protoEnDe.h"
using namespace std;

class MyTest:public ProtocolBase{
public:
	int m_nFd;
	long m_lFd;
	string m_csFd;
	string m_csFd2;
	string m_csFd3;

public:
	int set(int nFd,
		long lFd,
		string csFd);
	int get(int& nFd,
			long& lFd,
			string& csFd);
	void encode(Buf4ProtoEncode& cByteBuf);
	void decode(Buf4ProtoDecode& cByteBuf);
};

class Test1:public ProtocolBase{
public:
	  int m_nFd;
	  short m_nsFd;
	  char m_cFd;
	  long m_lFd;
	  string m_csFd;
	  MyTest m_cMyTest;
	  double  m_dFd;
	  float m_fFd;
	  bool  m_bFd;
public:
	  int set(int nfd, short nsfd, char cfd, long lfd, string csfd);
	  int get(int &nfd, short& nsfd, char& cfd, long &lfd, string &csfd);
	  void encode(Buf4ProtoEncode& cByteBuf);
	  void decode(Buf4ProtoDecode& cByteBuf); 	
};

class Test2:public ProtocolBase{
public:
	  int m_nFd;
	  vector<int> m_vecFd;
//	  map<int,string> m_mapFd;
public:
	  int set(int nfd, vector<int> m_vecFd);
	  int get(int &nfd, vector<int> &m_vecFd);
//	  int set(map<int,string> mapFd);
//	  int get(map<int,string>& mapFd);
	  void encode(Buf4ProtoEncode& cByteBuf);
	  void decode(Buf4ProtoDecode& cByteBuf); 	
};



