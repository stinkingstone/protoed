#ifndef __CFG_PARSE_H__
#define __CFG_PARSE_H__


#include <deque>
#include <map>
#include <vector>
#include <string>


using namespace std;

 
class CfgParse
{
public:
    CfgParse();
    /**
     * no implementation
     */
    CfgParse(const CfgParse&);
    ~CfgParse();

public:
 
    void Init(const string& filename);

 
    virtual void Load();

 
    virtual const string& operator [](const string& name);
 
    virtual const map<string,string>& GetPairs(const string& path) const;
 
    virtual const vector<string>& GetDomains(const string& path) const;
 
    virtual const vector<string>& GetSubPath(const string& path) const;

protected:
    enum EntryType 
    {
        T_STARTPATH = 0,
        T_STOPPATH = 1,
        T_NULL = 2,
        T_PAIR = 3,
        T_DOMAIN =4,
        T_ERROR = 5
    };

    string start_path(const string& s);
    string stop_path(const string& s);
    void decode_pair(const string& s,string& name,string& value);
    string trim_comment(const string& s); //trim×¢ÊÍºÍ\n·ûºÅ
    string path(const deque<string>& path);
    string parent_path(const deque<string>& path);
    string sub_path(const deque<string>& path);

    EntryType entry_type(const string& s);
protected:
    string _filename;

    map<string,map<string,string> > _pairs;
    map<string,vector<string> > _paths;
    map<string,vector<string> > _domains;

    map<string,string> _null_map;
    vector<string> _null_vector;
};

#endif //


