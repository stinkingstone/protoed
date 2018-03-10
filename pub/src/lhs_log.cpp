#include"lhs_h_log.h"
#include <log4cplus/logger.h> 
#include <log4cplus/consoleappender.h> 
#include <log4cplus/fileappender.h> 
#include <log4cplus/layout.h>  
#include <log4cplus/configurator.h> 
 
Logger logger = log4cplus::Logger::getInstance("log");

void InitLogger(bool daemonized)
{     
    if(daemonized)
        PropertyConfigurator::doConfigure("logger.properties");
    else
        return;
    //PropertyConfigurator::doConfigure("logger.properties");
}

void InitLogger(bool daemonized,const char* pszLogCfg)
{     
    if(daemonized)
        PropertyConfigurator::doConfigure(pszLogCfg);
    else
        return;
    //PropertyConfigurator::doConfigure("logger.properties");
}


