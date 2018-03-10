#include <string>


using namespace std;
#define RT_OK   0
#define RT_ERR  1

//namespace inoy
//{

class BufWt{//
	public:
	    char*           m_pszBuf;  //缓冲区指针
	    unsigned int    m_unLength; //缓冲区当前有效数据长长
	    unsigned int    m_unSize;   //缓冲区总空间
	public:    
		BufWt();
		~BufWt();
	    BufWt(const BufWt& bw);
		BufWt& operator=(const BufWt& buf);

		void Reset();

		int WriteBuf(const char* pszBuf, unsigned int len);
		const char * getBuf();
		unsigned int getLength();
		
		bool Expand(unsigned int  unLen);
		char* GetPos4Wt();
		unsigned int  WtOffShift(unsigned int nOffset);//写指针偏移
};


class BufRd{//
	public:
	    const char*     m_pszBuf;   //缓冲区指针
	    unsigned int    m_unLength; //缓冲区当前有效数据长长
	    unsigned int    m_unCur;    //缓冲区读取游标
	public:    
	     
		BufRd();
		~BufRd();
        void SetBuf(const char* pszBuf, unsigned int unLen);
		int ReadBuf(char* pszBuf, unsigned int unLen, unsigned int unOffset); 
		
		const char* GetPos4Rd();
		unsigned int  RdOffShift(unsigned int nOffset);//读指针偏移
};


//}

