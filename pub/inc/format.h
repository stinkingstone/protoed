#ifndef FORMAT_H
#define FORMAT_H

#include <stdarg.h>
#include <string>
#include <map>
#include <set>
#include <vector>

#define EMPTY_STRING        "<{^}>"
using namespace std;


char *utoa(char *buf, unsigned value);
int sformat(char *buf, unsigned size, const char *format, ...) __attribute__((format(printf,3,4)));
int spacetrim(string &str);
char* spacetrim(char *str);
bool config_match(const char *config, const char *name);
char *config_value(char *config);
const char *config_line(const char *config, char *line);
char * rmchar(char *str, char c);
int get_map_u(const map<string, string> &value, const char *key, unsigned &ret);
int get_map_i(const map<string, string> &value, const char *key, int &ret);
int get_map_l(const map<string, string> &value, const char *key, long long int &ret);
int get_map_string(const map<string, string> &value, const char *key, string &ret);
int key_split(set<string> &key, const char* keystr, const char *strip = "," );
int key_split(set<string> &key, string keystr, const char *strip = "," );
int key_split(vector<string> &key, string keystr, const char *strip = "," );
void string_split_vector(string str, set<unsigned> &friendlist);
void split_set(const char* p, set<unsigned> &friendlist);

void string_remove(string &source, string &dest);

int mapset_add(map<unsigned, map<string, string> > &dest, map<unsigned, map<string, string> > &source);

int key_map_insert(vector<string> &veckey, map<string,string> &value, map<string, vector<string>  >   &result, const char *nullstr = EMPTY_STRING);

int map_to_string(const map<string, string> &value, vector<string> keyvec, string &ret, const string &deli);

void string_tail_remove(string &souce, const string &dest);


 inline string trim_left(const string &s,const string& filt=" ")
{
    char *head=const_cast<char *>(s.c_str());
    char *p=head;
    while(*p) 
    {
        bool b = false;
        for(size_t i=0;i<filt.length();i++) 
        {
            if((unsigned char)*p == (unsigned char)filt.c_str()[i]) 
            {
                b=true;
                break;
            }
        }
        if(!b) 
        {
            break;
        }
        p++;
    }
    return string(p,0,s.length()-(p-head));
}

 inline string trim_right(const string &s,const string& filt=" ")
{
    if(s.length() == 0) return string();
    char *head=const_cast<char *>(s.c_str());
    char *p=head+s.length()-1;
    while(p>=head) 
    {
        bool b = false;
        for(size_t i=0;i<filt.length();i++) 
        {
            if((unsigned char)*p == (unsigned char)filt.c_str()[i]) 
            {
                b=true;
                break;
            }
        }
        if(!b) 
        {
            break;
        }
        p--;
    }
    return string(head,0,p+1-head);
}

 int set_to_string(const set<unsigned> &friendlist, string &ret);

 int now_date_format(char *str, unsigned size);

 int setadd(set<unsigned> &source, const set<unsigned> &dest);

int get_cpuid(string &ret);

bool xstr_decode(const char *in, unsigned len, char *out);
void xstr_encode(const char *in, unsigned len, char *out);

#endif

