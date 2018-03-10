#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[])
{
    vector<string> vecTest1;
    vector<string> vecTest2;
    vecTest1.push_back("T1");
    vecTest1.push_back("T2");
    vecTest1.push_back("T3");
    vecTest2 = vecTest1;

    printf(" vectest2 size:%d\n",vecTest2.size());

    for(unsigned ulop=0;ulop<vecTest2.size();ulop++)
    {
        printf(" vectest2[%d]=%s\n",ulop,vecTest2[ulop].c_str());
    }
    return 0;

}

