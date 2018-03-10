#include "para_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

bool para_item_parse(const string &line, char &shortopt, string &longopt)
{
    if(line.length() > 0) 
    {
        shortopt = line.c_str()[0];

        if(line.c_str()[1] == ':')
        {
            longopt = line.substr(2);
        }
        else
        {    
            longopt = line;
        }
        return true;
    }

    return false;
}


bool para_comp(const char *arg, char shortopt, const string &longopt)
{
    if(arg[0] == '-' && arg[1] == '-') 
    {
        return !strcmp(arg + 2, longopt.c_str());
    }
    else if(arg[0] == '-') 
    {
        return arg[1] == shortopt && arg[2] == '\0';
    }

    return false;
}


bool opt_find(const vector<COptarg> &optvec, int opt)
{
    for(unsigned i = 0; i < optvec.size(); i++) 
    {
        const COptarg &optarg = optvec[i];
        if(optarg.opt == opt)
        {
            return true;
        }
    }

    return false;
}


bool para_string(const COptarg &optarg, string &ret, int index)
{
    ret = "";
    if(index >= 0 && optarg.arg.size() > (unsigned)index) 
    {
        ret = optarg.arg[index];
        return true;
    }

    if(index >= 0)
    {
        return false;
    }
    
    for(unsigned i = 0; i < optarg.arg.size(); i++)
    {    
        ret += optarg.arg[i];
    }
    return true;
}


bool para_find(const vector<COptarg> &optvec, int opt, string &ret)
{
    for(unsigned i = 0; i < optvec.size(); i++) 
    {
        const COptarg &optarg = optvec[i];
        if(optarg.opt == opt) 
        {
            para_string(optarg, ret, -1);
            return true;
        }
    }

    return false;
}


bool para_check(vector<COptarg> &opt, char shortopt, string &longopt)
{
    for(unsigned i = 0; i < opt.size(); i++) 
    {
        COptarg &optarg = opt[i];
        if(optarg.opt == shortopt || optarg.logopt == longopt)
        {
            return true;
        }
    }

    return false;
}


int para_arg(int argc, char *argv[], char shortopt, string &longopt, vector<COptarg> &opt)
{
    if(para_check(opt, shortopt, longopt)) 
    {
        return -1;
    }

    COptarg optarg;
    optarg.opt = shortopt;
    optarg.logopt = longopt;
    optarg.arg.clear();

    bool opthas = false;
    for(int i = 0; i < argc; i++) 
    {
        if(!para_comp(argv[i], shortopt, longopt))
        {
            continue;
        }
        opthas = true;
        for(++i; i < argc; i++) 
        {
            if(*argv[i] != '-')
            {
                optarg.arg.push_back(argv[i]);
            }
            else 
            {
                i--;
                break;
            }
        }
    }

    if(opthas) 
    {
        opt.push_back(optarg);
        return 1;
    }

    return 0;
}


int para_parse(int argc, char *argv[], const char *optarg, vector<COptarg> &opt)
{
    vector<string> optvec;
    vector<string> arg;
    char shortopt;
    string longopt;
    key_split(optvec, optarg);

    opt.clear();
    for(unsigned i = 0; i < optvec.size(); i++) 
    {
        if(!para_item_parse(optvec[i], shortopt, longopt)) 
        {
            return -1;
        }

        if(0 > para_arg(argc, argv, shortopt, longopt, opt)) 
        {
            return -1;
        }
    }

    return 0;
}

void InitDaemon()
{
    pid_t pid;
    if ((pid = fork() ) != 0 ) {
        exit(0);
    }
    
    /* 屏蔽一些有关控制终端操作的信号 
     * 防止在守护进程没有正常运转起来时，因控制终端受到干扰退出或挂起 
     * */  
    signal(SIGINT,  SIG_IGN);// 终端中断  
    signal(SIGHUP,  SIG_IGN);// 连接挂断  
    signal(SIGQUIT, SIG_IGN);// 终端退出  
    signal(SIGPIPE, SIG_IGN);// 向无读进程的管道写数据  
    signal(SIGTTOU, SIG_IGN);// 后台程序尝试写操作  
    signal(SIGTTIN, SIG_IGN);// 后台程序尝试读操作  
    signal(SIGTERM, SIG_IGN);// 终止 
    signal( SIGCHLD, SIG_IGN);
    
    pid = fork();  
    if(pid < 0)  
    {  
        perror("fork error!");  
        exit(1);  
    }  
    else if(pid > 0)  
    {  
        exit(0);  
    } 
    
    setsid();                            // creates  a  new session if the calling process is not a process group leader

    struct sigaction sig;
    sig.sa_handler = SIG_IGN;
    sig.sa_flags = 0;
    sigemptyset( &sig.sa_mask);
    sigaction( SIGHUP,&sig,NULL);

    umask(0);                            // sets the umask to mask & 0777
    setpgrp();
}


void print_usage(int exit_code)
{
    //fprintf (stdout, "Usage: %s options [ inputfile ... ]\n", program_name);
    fprintf (stdout, 
             " -h --help                       display this message\n"
             " -d --daemon                  daemon model    \n"
             " -c config file\n"
             );

    exit(exit_code);
}


int opt_process(const vector<COptarg> &opt)
{
    string arg;

    for(unsigned i = 0; i < opt.size(); i++) 
    {
        const COptarg &optarg = opt[i];
        switch(optarg.opt) 
        {            
        case 'h':
            print_usage(0);
            break;
        case 'd':
            InitDaemon();
            break;
        default:      /* 未指定的参数出现，出错处理 */
            //print_usage (1);
            break;
        }
    }
    return 0;
}
