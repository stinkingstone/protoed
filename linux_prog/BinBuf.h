#include <string>


using namespace std;
#define RT_OK   0
#define RT_ERR  1

//namespace inoy
//{

class BufWt{//
	public:
	    char*           m_pszBuf;  //������ָ��
	    unsigned int    m_unLength; //��������ǰ��Ч���ݳ���
	    unsigned int    m_unSize;   //�������ܿռ�
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
		unsigned int  WtOffShift(unsigned int nOffset);//дָ��ƫ��
};


class BufRd{//
	public:
	    const char*     m_pszBuf;   //������ָ��
	    unsigned int    m_unLength; //��������ǰ��Ч���ݳ���
	    unsigned int    m_unCur;    //��������ȡ�α�
	public:    
	     
		BufRd();
		~BufRd();
        void SetBuf(const char* pszBuf, unsigned int unLen);
		int ReadBuf(char* pszBuf, unsigned int unLen, unsigned int unOffset); 
		
		const char* GetPos4Rd();
		unsigned int  RdOffShift(unsigned int nOffset);//��ָ��ƫ��
};


//}

