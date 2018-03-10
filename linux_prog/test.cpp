//#include "BinBuf.h"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include "test_proc.h"


int main()
{
     Test1 t1;
	 t1.set(-1295056,-38,-20,-58988,"hello world");
	 t1.m_cMyTest.set(-18,-833213,"Tom guy");
	 t1.m_cMyTest.m_csFd2="How do you do! where are you from";
	 t1.m_cMyTest.m_csFd3="Hello, this is tom";
	 t1.m_fFd = -2.801;
	 t1.m_dFd = -1983412913894.22;
	 t1.m_bFd = true;
	 printf(" t1 fd1:%d fd2:%d fd3:%d fd4:%d fd5:%s fd6:%f fd7:%f fd8:%d\n",t1.m_nFd,t1.m_nsFd,t1.m_cFd,t1.m_lFd,t1.m_csFd.c_str(),t1.m_dFd,t1.m_fFd,t1.m_bFd);
     printf(" t1.m_cMyTest fd1:%d fd2:%d fd3:%s fd4:%s fd5:%s\n",t1.m_cMyTest.m_nFd,t1.m_cMyTest.m_lFd,t1.m_cMyTest.m_csFd.c_str(),
	 	     t1.m_cMyTest.m_csFd2.c_str(),
	 	     t1.m_cMyTest.m_csFd3.c_str());
     Buf4ProtoEncode b1;
	 t1.encode(b1);
	 Buf4ProtoDecode b2;
	 b2.SetBuf(b1.getBuf(),b1.getLength());
	 Test1 t2;
	 t2.decode(b2);
     printf(" t2 fd1:%d fd2:%d fd3:%d fd4:%d fd5:%s fd6:%f fd7:%f fd8:%d\n",t2.m_nFd,t2.m_nsFd,t2.m_cFd,t2.m_lFd,t2.m_csFd.c_str(),t2.m_dFd,t2.m_fFd,t2.m_bFd);
     printf(" t2.m_cMyTest fd1:%d fd2:%d fd3:%s fd4:%s fd5:%s\n",t2.m_cMyTest.m_nFd,t2.m_cMyTest.m_lFd,t2.m_cMyTest.m_csFd.c_str(),
	 	           t2.m_cMyTest.m_csFd2.c_str(),
	 	           t2.m_cMyTest.m_csFd3.c_str());

	 Test2 tst2;
	 vector<int> vecVal;
	 vecVal.push_back(11);
	 vecVal.push_back(91321);
	 vecVal.push_back(-235);
	 tst2.set(25,vecVal);
	 map<int ,string> vmap;
	 string csV ="Hello";
	 vmap[0]=csV;
	 csV = "World";
	 vmap[1]=csV;
//	 tst2.set(vmap);
	 Buf4ProtoEncode tb1;
	 tst2.encode(tb1);
	 Buf4ProtoDecode tb2;
	 tb2.SetBuf(tb1.getBuf(),tb1.getLength());
	 Test2 tt2;
	 tt2.decode(tb2);
	 map<int, string> vmap2;
//	 tt2.get(vmap2);
	 vector<int> vecVal2;
	 int nFd;
	 tt2.get(nFd,vecVal2);
	 printf("tt2.m_nFd:%d\n",t2.m_nFd);
	 for(int i=0;i<vecVal2.size();i++){
	 	printf("i:%d value:%d\n",i,vecVal2[i]);
	 }
//	 printf("%s\n,%s\n",vmap[0].c_str(),vmap[1].c_str());
     return 0;
}

