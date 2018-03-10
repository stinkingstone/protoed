#ifndef _PARA_PARSE_H
#define _PARA_PARSE_H

#include <string>
#include <vector>

using namespace std;



class COptarg
{
public:
    int opt;        //��ѡ���ַ�
    string logopt;    //��ѡ����
    vector<string> arg;    //ѡ������б�
};

void InitDaemon();
void print_usage(int exit_code);
bool para_string(const COptarg &optarg, string &ret, int index = 0);
int  para_parse(int argc, char *argv[], const char *optarg, vector<COptarg> &opt);
bool para_find(const vector<COptarg> &optvec, int opt, string &ret);
int  para_process(const vector<COptarg> &opt,string& csFileConf);
int opt_process(const vector<COptarg> &opt);

#endif
