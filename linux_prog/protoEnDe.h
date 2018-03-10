#include <string>
#include <vector>
#include <map>
#include "tlv.h"
#include "BinBuf.h"
//#include "ProtocolBase.h"
using namespace  std;

class Buf4ProtoEncode: public BufWt
{
public:
	Buf4ProtoEncode(){
	};
	int PushBack(bool bData)
	{
		int nMaxSize = 1+sizeof(bool);
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(bData);
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    }
	    return 0;
	}

	int PushBack(char cData)
	{
		int nMaxSize = 1+sizeof(char);
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(cData);
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    }
	    return 0; 
	}

	int  PushBack(short nsData)
     {
	    int nMaxSize = 1+sizeof(short);
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(nsData);
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    }
	    return 0; 
	}


	int  PushBack(int   nData)    
	{
	    int nMaxSize = 1+sizeof(int);
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(nData);
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    }
	    return 0; 
	}


	int  PushBack(long  lData)    
	{
	    int nMaxSize = 1+sizeof(long);
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(lData);
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    }
	    return 0;  
	}

	int  PushBack(float  fData)    
	{
	    int nMaxSize = 1+sizeof(float);
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(fData);
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    }
	    return 0;  
	}

	int  PushBack(double  dData)    
	{
	    int nMaxSize = 1+sizeof(double);
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(dData);
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    }
	    return 0;  
	}


	    
	int  PushBack(char*  pszcData, long lNum)    
	{
	    int nMaxSize = 1+sizeof(long)+lNum;
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(pszcData,lNum);
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    }
	    return 0;
	}

	int  PushBack(string  &csData)    
	{
	    int nMaxSize = 1+sizeof(long)+csData.length();
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(csData);
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    }
	    return 0;
	}

	template<typename K, typename V, typename Cmp, typename Alloc>
	int PushBackMap( const std::map<K, V, Cmp, Alloc>& m )
	{
		Buf4ProtoEncode cElemSet;
		typedef typename std::map<K, V, Cmp, Alloc>::const_iterator IT;
		for (IT i = m.begin(); i != m.end(); ++i)
		{
		    Buf4ProtoEncode cElemSet1;
			cElemSet1.PushBack(i->first);
			//write(i->first, 0);
			Buf4ProtoEncode cElemSet2;
			cElemSet2.PushBack(i->second);
			cElemSet.PushBack((char*)cElemSet1.getBuf(),cElemSet1.getLength());
			cElemSet.PushBack((char*)cElemSet2.getBuf(),cElemSet2.getLength());
			//write(i->second, 1);
		}
		int nMaxSize = 1+sizeof(long) + cElemSet.getLength();
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(MT_MAP,(char*)cElemSet.getBuf(),cElemSet.getLength());
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    } 
	}

    template<typename Alloc>
	int PushBack(const std::vector<char, Alloc>& v)
	{
		PushBack(&v[0], v.size());
	}

    template<class T>
	int PushBack(const std::vector<T>& v)
	{
		Buf4ProtoEncode cElemSet;
		typedef typename std::vector<T>::iterator IT;
		//typedef typename std::vector<T, Alloc>::const_iterator IT;
		for (IT i = v.begin(); i != v.end(); ++i){
			cElemSet.PushBack(*i);
    	}
	    int nMaxSize = 1+sizeof(long) + cElemSet.getLength();
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(MT_VECTOR,(char*)cElemSet.getBuf(),cElemSet.getLength());
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    } 
		return 0;
	}

	template<typename T>
	int  PushBack( T& cPBData)    
	{
	    Buf4ProtoEncode cPE;
//		ProtocolBase* pcPB = (ProtocolBase*)&cPBData;
//	    pcPB->encode(cPE);
        cPBData.encode(cPE);
	    int nMaxSize = 1+sizeof(long)+cPE.getLength();
	    int nret = this->Expand(nMaxSize);
	    if(!nret){
	        return -1;
	    }
	    tlv *pcTlv = (tlv*)this->GetPos4Wt();
	    nret = pcTlv->setValue(MT_STRUCT,(char*)cPE.getBuf(),cPE.getLength());
	    pcTlv->h2n();
	    if(nret>0){
	        this->WtOffShift(nret);
	    }     
	     return 0; 
	}



};

class Buf4ProtoDecode: public BufRd
{
public:
	int  PopAhead(char &cData)    
	{
	    tlv *pcTlv = (tlv*)this->GetPos4Rd();
	    pcTlv->n2h();
	    int nret = pcTlv->getValue(cData);
	    if(nret>0){        
	        this->RdOffShift(nret);
	    }
	    return 0;
	}

	int  PopAhead(bool &bData)    
	{
	    tlv *pcTlv = (tlv*)this->GetPos4Rd();
	    pcTlv->n2h();
	    int nret = pcTlv->getValue(bData);
	    if(nret>0){        
	        this->RdOffShift(nret);
	    }
	    return 0;
	}

	int  PopAhead(short& nsData)    
	{
	    tlv *pcTlv = (tlv*)this->GetPos4Rd();
	    pcTlv->n2h();
	    int nret = pcTlv->getValue(nsData);
	    if(nret>0){        
	        this->RdOffShift(nret);
	    }
	    return 0;

	}
	    

	int  PopAhead(int& nData)    
	{
	    tlv *pcTlv = (tlv*)this->GetPos4Rd();
	    pcTlv->n2h();
	    int nret = pcTlv->getValue(nData);
	    if(nret>0){        
	        this->RdOffShift(nret);
	    }
	    return 0;

	}
	    

	int  PopAhead(long& lData)    
	{
	    tlv *pcTlv = (tlv*)this->GetPos4Rd();
	    pcTlv->n2h();
	    int nret = pcTlv->getValue(lData);
	    if(nret>0){        
	        this->RdOffShift(nret);
	    }
	    return 0;

	}

	int  PopAhead(float& fData)    
	{
	    tlv *pcTlv = (tlv*)this->GetPos4Rd();
	    pcTlv->n2h();
	    int nret = pcTlv->getValue(fData);
	    if(nret>0){        
	        this->RdOffShift(nret);
	    }
	    return 0;

	}

    int  PopAhead(double& dData)    
	{
	    tlv *pcTlv = (tlv*)this->GetPos4Rd();
	    pcTlv->n2h();
	    int nret = pcTlv->getValue(dData);
	    if(nret>0){        
	        this->RdOffShift(nret);
	    }
	    return 0;

	}		

	int  PopAhead(string& csData)    
	{
	    tlv *pcTlv = (tlv*)this->GetPos4Rd();
	    pcTlv->n2h();
	    int nret = pcTlv->getValue(csData);
	    if(nret>0){        
	        this->RdOffShift(nret);
	    }
	    return 0;

	}

    template<typename K, typename V, typename Cmp, typename Alloc>
	int PopAheadMap( std::map<K, V, Cmp, Alloc>& m )
	{
        tlv *pcTlv = (tlv*)this->GetPos4Rd();
	    pcTlv->n2h();
	    string csData;
	    int nret = pcTlv->getValue(MT_MAP,csData);
	    Buf4ProtoDecode cIBB;
		cIBB.SetBuf(csData.c_str(), csData.length());
	    //cPBData.decode(cIBB);
	    if(nret>0){        
	        this->RdOffShift(nret);
	    }else{
	        return -1;//说明当前不是vector数据，退出
	    }
		tlv *pcTlv2 = NULL;
		while(1){
			std::pair<K, V> pr;
		    pcTlv2 = (tlv*)cIBB.GetPos4Rd();
	        pcTlv2->n2h();
			int nret = pcTlv2->getValue(pr.first);
			if(nret>0){
				;
			}else{
			    break;
			}
			cIBB.RdOffShift(nret);
			pcTlv2 = (tlv*)cIBB.GetPos4Rd();
	        pcTlv2->n2h();
			nret = pcTlv2->getValue(pr.second);
			if(nret>0){
				;
			}else{
			    break;
			}
			cIBB.RdOffShift(nret);
			m.insert(pr);
		}

	}


	//template<typename T, typename Alloc>
	//typename vector<T>::iterator IT;
	template<class T>
	int PopAhead(vector<T> &v)//std::vector<T, Alloc>& v,int nsize)
	{
	    tlv *pcTlv = (tlv*)this->GetPos4Rd();
	    pcTlv->n2h();
	    string csData;
	    int nret = pcTlv->getValue(MT_VECTOR,csData);
	    Buf4ProtoDecode cIBB;
		cIBB.SetBuf(csData.c_str(), csData.length());
	    //cPBData.decode(cIBB);
	    if(nret>0){        
	        this->RdOffShift(nret);
	    }else{
	        return -1;//说明当前不是vector数据，退出
	    }
		tlv *pcTlv2 = NULL;
		while(1){
		    pcTlv2 = (tlv*)cIBB.GetPos4Rd();
	        pcTlv2->n2h();
		    T valT;
			int nret = pcTlv2->getValue(valT);
			if(nret>0){
				v.push_back(valT);
			}else{
			    break;
			}
			cIBB.RdOffShift(nret);
		}
		return 0;
	}


    template<typename T>
	int  PopAhead(T& cPBData)
	{
	    tlv *pcTlv = (tlv*)this->GetPos4Rd();
	    pcTlv->n2h();
	    string csData;
	    int nret = pcTlv->getValue(MT_STRUCT,csData);
	    Buf4ProtoDecode cIBB;
		cIBB.SetBuf(csData.c_str(), csData.length());
	    cPBData.decode(cIBB);
	    if(nret>0){        
	        this->RdOffShift(nret);
	    }
	    return 0;

	}



};

