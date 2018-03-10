#ifndef __LHS_H_LOG_H__
#define __LHS_H_LOG_H__

#pragma once
#include <iostream>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

using namespace log4cplus ;
using namespace log4cplus::helpers;
extern Logger logger;


#define LOG_LOG(logEvent)     LOG4CPLUS_TRACE(logger,logEvent)
#define LOG_WARN(logEvent)    LOG4CPLUS_WARN(logger,logEvent)
#define LOG_FATAL(logEvent)   LOG4CPLUS_FATAL(logger,logEvent)
#define LOG_DB(logEvent)      LOG4CPLUS_DEBUG(logger,logEvent)

extern void InitLogger (bool daemonized);
extern void lmsg(int color,const char * msg);
extern void InitLogger(bool daemonized,const char* pszLogCfg);

#endif  //__LHS_H_LOG_H__ 

