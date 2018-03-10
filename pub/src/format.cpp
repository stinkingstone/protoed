#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "format.h"



/*
无符号整型转字符串
buf:用来输出字符串的地址，长度要足够保存无符号整型
value:要转换的无符号整型数
*/
char *utoa(char *buf, unsigned value)
{
/*
    char *tmp = buf;
    while(1)
    {
        *tmp++ = ('0' + value % 10);
        value /= 10;
        if(0 == value)
            break;
    }

    *tmp-- = 0;
    for(char *start = buf; start < tmp; start++, tmp--)
    {
        char chr = *start;
        *start = *tmp;
        *tmp = chr;
    }*/
    sprintf(buf, "%u", value);
        
    return buf;
}

/*
格式函数
buf:用来输出格式化后的字符串的缓冲区
size:用来输出格式化后的字符串的缓冲区的长度
format:格式化字符串
*/
int sformat(char *buf, unsigned size, const char *format, ...)
{
    assert(buf && size);

    va_list args;
    va_start(args, format);

    int len = vsnprintf(buf, size, format, args);

    va_end(args);

    if (len > -1 && len < (int)size)
        return 0;

    buf[0] = 0;
    return -1;
}

/*
删除字符串末尾的空格字符
*/
char *rm_space_tail(char *p)
{
    if(p)
    {
        for(int i = (int)strlen(p) - 1; i >= 0; i--)
        {
            if(isspace(p[i]))
            {    
                p[i] = 0;
            }
            else
            {    
                break;
            }
        }

    }

    return p;
}

/*
跳过字符串头的空格字符
*/
char *skip_space_front(const char *p)
{
    if(p)
    {
        while(isspace(*p))
        {
            p++;
        }
    }

    return (char*)p;
}

/*
删除字符串头和末尾的空格字符
*/
int spacetrim(string &str)
{
    try 
    {
        int s = str.find_first_not_of(" \t\r\n");
        if(0 > s)
        {
            str = (char*)"";
        }
        else
        {
            int e = str.find_last_not_of(" \t\r\n");
            if(s <= e)
            {    
                str=str.substr(s, e-s+1);
            }
        }
    } 
    catch(...) 
    {
        return -4;
    }

    return 0;
}

/*
删除字符串末尾的空格字符,跳过字符串头的空格
*/
char* spacetrim(char *str)
{
    return rm_space_tail(skip_space_front(str));
        
}

/*
配置行的匹配，如port=21,就和port匹配
config:配置行
name:配置行的名称
*/
bool config_match(const char *config, const char *name)
{
    config = skip_space_front(config);
    unsigned len = strlen(name);
    if(config[len] && config[len] != '=' && !isspace(config[len]))
    {    
        return false;
    }
    
    return !memcmp(config, name, len);
}

/*
取配置行的值，如port=21,值就是"21"
config:配置行
*/
char *config_value(char *config)
{
    char *str = strchr(config, '=');
    if(!str)
    {    
        return NULL;
    }

    str = skip_space_front(str+1);
    rm_space_tail(str);
    return str;
}

/*
从配置中读取一行
config:配置数据
line:用来返回行数据
*/
const char *config_line(const char *config, char *line)
{
    if(!config || !*config)
    {    
        return NULL;
    }
    
    while(*config)
    {
        if(*config == '\n')
        {
            *line = 0;
            return ++config;
        }

        *line++ = *config++;
    }

    *line = 0;
    return config; 
}

/*
删除字符串中的指定字符
str:输入的字符串
c:要删除的字符
*/
char * rmchar(char *str, char c)
{
    char *tmp = str;
    unsigned index = 0;
    
    while(*tmp)
    {        
        if(*tmp != c)
        {
            str[index++] = *tmp;
        }

        tmp++;
    }

    str[index] = 0;
    return str;
}

/*
从从map中获取无符号int值
value:输入的map
kay:要取值的键值
ret:用来返回无符号int值
*/
int get_map_u(const map<string, string> &value, const char *key, unsigned &ret)
{
    map <string, string>::const_iterator iter = value.find(key);
    if(iter != value.end()) 
    {
        ret = atoi(iter->second.c_str());
        return 0;
    }

    return -1;
}

/*
从从map中获取int值
value:输入的map
kay:要取值的键值
ret:用来返回int值
*/
int get_map_i(const map<string, string> &value, const char *key, int &ret)
{
    map <string, string>::const_iterator iter = value.find(key);
    if(iter != value.end()) 
    {
        ret = atoi(iter->second.c_str());
        return 0;
    }

    return -1;
}

/*
从从map中获取int值
value:输入的map
kay:要取值的键值
ret:用来返回int值
*/
int get_map_l(const map<string, string> &value, const char *key, long long int &ret)
{
    map <string, string>::const_iterator iter = value.find(key);
    if(iter != value.end()) 
    {
        ret = atoi(iter->second.c_str());
        return 0;
    }

    return -1;
}

/*
从从map中获取字符串值
value:输入的map
kay:要取值的键值
ret:用来返回字符串值
*/
int get_map_string(const map<string, string> &value, const char *key, string &ret)
{
    map <string, string>::const_iterator iter = value.find(key);
    if(iter != value.end()) 
    {
        ret = iter->second;
        return 0;
    }

    return -1;
}


/********************************************************
把字符串形式以strip分隔的字符串分割为字符串集合
这个调用不能保存顺序，但可以保证元素唯一性
************************************************************/
int key_split(set<string> &key, const char* keystr, const char *strip)
{
    char *p;
    char *str = strdup(keystr);
    char *outer_ptr = str;
    if(!str)
        return -1;

    key.clear();
    while((p = strtok_r(outer_ptr, strip, &outer_ptr))) 
    {
        key.insert(skip_space_front(p));
    }

    free(str);
    return 0;
}

/********************************************************
把字符串形式以strip分隔的字符串分割为字符串集合
这个调用不能保存顺序，但可以保证元素唯一性
************************************************************/
int key_split(set<string> &key, string keystr, const char *strip)
{
    return key_split(key, keystr.c_str(), strip);
}


/********************************************************
把字符串形式以strip分隔的字符串分割为字符串向量
这个调用可以保证元素顺序，但不能保证元素唯一性
key可能包含多个""空字符串
************************************************************/
/*
int key_split(vector<string> &key, string keystr, const char *strip)
{
    char *p;
    char *str = strdup(keystr.c_str());
    char *outer_ptr = str;
    if(!str)
        return -1;

    key.clear();
    while((p = strtok_r(outer_ptr, strip, &outer_ptr))) {
        key.push_back(skip_space(p));
    }

    free(str);
    return 0;
}
*/

/********************************************************
把字符串形式以strip分隔的字符串分割为字符串向量
这个调用可以保证元素顺序，但不能保证元素唯一性
key可能包含多个""空字符串
************************************************************/
int key_split(vector<string> &key, string keystr, const char *strip)
{
    const char *p = keystr.c_str();
    const char *tmp;

    try
    {
        key.clear();
        while(1) 
        {
            if((tmp = strstr(p, strip)))
            {
                char *str = skip_space_front(p);
                string keystr(str, 0, tmp > str ? (tmp - str) : 0);
                key.push_back(keystr);
                p = tmp + strlen(strip);
            }
            else
            {
                if(*p)
                {    
                    key.push_back(p);    
                }
                return 0;
            }
        }
    }
    catch(...)
    {
        return -1;
    }
    return 0;
}


/*
map加函数
dest:被添加元素的目标
source:要添加的map
*/
int mapset_add(map<unsigned, map<string, string> > &dest, map<unsigned, map<string, string> > &source)
{
    map<unsigned, map<string, string> > ::iterator it;
    map<unsigned, map<string, string> > ::iterator itdest;

    for(it = source.begin(); it != source.end(); it++)
    {
        itdest = dest.find(it->first);
        if(itdest == dest.end())
        {
            dest[it->first] = it->second;
        }
        else
        {
            return -1;
        }
    }

    return 0;
}

/*
如果dest在source的末尾，则删除source末尾的dest
*/
void string_remove(string &source, string &dest)
{
    while(1)
    {
        int pos = source.find(dest);
        if(0 == pos)
        {
            source.erase(pos, dest.length());
        }
        else if(0 < pos)
        {
            if(source[pos-1] == ',')
            {    
                source.erase(pos, dest.length());
            }
        }
        else
        {    
            break;
        }
    }
}


int key_map_insert(vector<string> &veckey, map<string,string> &value, map<string, vector<string>  >   &result, const char *nullstr)
{
    for(unsigned i = 0; i < veckey.size(); i++)
    {
        map<string,string>::iterator itvalue = value.find(veckey[i]);
        if(itvalue == value.end())
        {
            return -1;
        }
    }

    for(unsigned i = 0; i < veckey.size(); i++)
    {
        map<string,string>::iterator itvalue = value.find(veckey[i]);
        map<string, vector<string>  >::iterator itresult = result.find(veckey[i]);
        string strval = itvalue->second;
        if(0 == strval.length())
        {
            strval = nullstr;
        }
        if(itresult == result.end())
        {
            vector<string> vecstr;
            vecstr.clear();
            vecstr.push_back(strval);

            result[veckey[i]] = vecstr;
        }
        else
        {
            itresult->second.push_back(strval);
        }
    }

    return 0;
}

/*
字符串分割。把字符分割为无符号型集合
str:被分割的字符串
friendlist:无符号型集合
*/
void string_split_vector(string str, set<unsigned> &friendlist)
{
    char *p = (char*)str.c_str();
    friendlist.clear();
    if(isdigit(*p))
    {    
        friendlist.insert(atoi(p));
    }
    while((p = strchr(p, ',')))
    {
        unsigned mq = atoi(++p);
        if(mq)
        {    
            friendlist.insert(mq);
        }
    }
}

/*
如果dest在source的末尾，则删除source末尾的dest
*/
void string_tail_remove(string &souce, const string &dest)
{
    int index = souce.length() - dest.length();
    if(index >= 0)
    {
        if(!strcmp(souce.c_str() + index, dest.c_str()))
        {
            souce.erase(index, dest.length());
        }
    }    
}

int map_to_string(const map<string, string> &value, vector<string> keyvec, string &ret, const string &deli)
{
    ret = "";
    for (vector<string>::iterator iter = keyvec.begin(); iter != keyvec.end(); iter++) 
    {
        map<string, string>::const_iterator it = value.find(*iter);
        if(it == value.end())
        {    
            return -1;
        }
        if(it->second.length())
        {
            const string &value = it->second;
            if(value.find(deli) != string::npos)
            {
                ;
            }
            ret += it->second;            
        }
        else
        {    
            ret += (char*)EMPTY_STRING;
        }
        ret += deli;
    }

    string_tail_remove(ret, deli);
    return 0;
}


/*
字符串分割。把字符分割为无符号型集合
str:被分割的字符串
friendlist:无符号型集合
*/
void split_set(const char* p, set<unsigned> &friendlist)
{
    friendlist.clear();
    if(isdigit(*p))
    {
        friendlist.insert(atoi(p));
    }
    while((p = strchr(p, ',')))
    {
        unsigned mq = atoi(++p);
        if(mq)
        {
            friendlist.insert(mq);
        }
    }
}

/*
把无符号整型的集合转换为字符串
friendlist:无符号整型的集合
ret:用来返回结果的字符串
*/
int set_to_string(const set<unsigned> &friendlist, string &ret)
{
    char str[64];

    ret = (char*)"";
    for (set<unsigned>::const_iterator it = friendlist.begin(); it != friendlist.end(); it++) 
    {
        ret += utoa(str, *it);
        ret += ",";
    }

    return 0;
}

/*
输出当前时间的给时候字符串
*/
int now_date_format(char *str, unsigned size)
{
    struct tm now;
    time_t t = time(NULL);
    
    localtime_r(&t, &now);
    return sformat(str, size, "%d-%d-%d %d:%d:%d", now.tm_year+1900, now.tm_mon+1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
}

/*
集合加函数
source:被添加元素的目标
dest:要添加的集合
*/
int setadd(set<unsigned> &source, const set<unsigned> &dest)
{
    try
    {
        for(set<unsigned>::const_iterator it = dest.begin(); it != dest.end(); ++it)
        {
            source.insert(*it);
        }
    }
    catch(...)
    {
        return -1;
    }

    return 0;
}

/*
获取cpuid
*/
int get_cpuid(string &ret)
{
    unsigned int eax, ebx, ecx, edx;

    asm volatile( "movl $0x01 , %%eax ; \n\t"
          "xorl %%edx , %%edx ;\n\t"
          "cpuid ;\n\t"
          "movl %%edx ,%0 ;\n\t"
          "movl %%eax ,%1 ; \n\t"
          :"=m"(eax),"=m"(ebx)
    );

    asm volatile("movl $0x03,%%eax ;\n\t"
         "xorl %%ecx,%%ecx ;\n\t"
         "xorl %%edx,%%edx ;\n\t"
         "cpuid ;\n\t"
         "movl %%edx,%0 ;\n\t"
         "movl %%ecx,%1 ;\n\t"
         :"=m"(ecx),"=m"(edx)
    );

    char buffer[64];
    if(sformat(buffer, sizeof(buffer), "%8.8x%8.8x%8.8x%8.8x", eax, ebx, ecx, edx))
    {
        return -1;
    }

    ret = buffer;
    return 0;
}

/*
二进制值转换为16进制字符
*/
int xchr_decode(char c)
{
    if(isdigit(c))
    {
        return c - '0';
    }

    if('a' <= c && c <= 'f')
    {    
        return c - 'a' + 10;
    }

    if('A' <= c && c <= 'F')
    {    
        return c - 'A' + 10;
    }

    return 0;
}

/*
字符转换为16进制值
*/
int xchr_encode(int c, char *xstr)
{
    xstr[0] = ((c & 0xf) > 9) ? ((0xf & c) + 'A' - 10)  : ((0xf & c) + '0');
    xstr[1] = ((c>>4 & 0xf) > 9) ? ((c>>4 & 0xf) + 'A' - 10)  : ((c>>4 & 0xf) + '0');

    return 0;
}

/*
十六进制字符串解码为二进制进制数据
in:输入十六进制字符串
len:输入十六进制字符串长度
out:用来输出解码后的进制数据
*/
bool xstr_decode(const char *in, unsigned len, char *out)
{
    for(unsigned i = 0; i + 1 < len; i+=2)
    {
        int value = xchr_decode(in[i]) | xchr_decode(in[i+1]) << 4;
        if(value & ~0xff)
        {    
            return false;
        }
        out[i>>1] = value;
    }

    out[len>>1] = 0;
    return true;
}

/*
二进制数据编码为十六进制字符串
in:输入的二进制数据
len:输入的二进制数据长度
out:用来输出编码后的十六进制字符串，长度最少为len*2+1
*/
void xstr_encode(const char *in, unsigned len, char *out)
{
    for(unsigned i = 0; i < len; i++)
    {
        xchr_encode(in[i] & 0xff, out + 2*i);
    }    

    out[len*2] = 0;
}

