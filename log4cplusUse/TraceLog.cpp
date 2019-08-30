#include "stdafx.h"
#include <iostream>

#include "TraceLog.h"

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

CTraceLog *CTraceLog::ms_pInstance = nullptr;

CTraceLog::CTraceLog()
{
    m_nLevel = TRACE_LOG_LEVEL_CALL;

	log4cplus::initialize();
	PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(".\\Config\\log4cplus.properties"));
	loggerRoot = Logger::getRoot();
	//loggerRoot = Logger::getInstance(LOG4CPLUS_TEXT("testlogger"));//��ͬ����־����
}

CTraceLog::~CTraceLog()
{
    delete ms_pInstance;
}

CTraceLog * CTraceLog::GetInstance()
{
    if (!ms_pInstance)
    {
        ms_pInstance = new CTraceLog;
    }
    return ms_pInstance;
}

std::string CTraceLog::GetTraveLogLevelName( eTraceLogLevel level ) const
{
    switch (level)
    {
    case TRACE_LOG_LEVEL_CALL:
        return "CALL";
        break;
    case TRACE_LOG_LEVEL_DEBUG:
        return "DEBUG";
        break;
    case TRACE_LOG_LEVEL_INFO:
        return "INFO";
        break;
    case TRACE_LOG_LEVEL_WARNING:
        return "WARNING";
        break;
    case TRACE_LOG_LEVEL_ERROR:
        return "ERROR";
        break;
    case TRACE_LOG_LEVEL_FATAL:
        return "FATAL";
        break;
    default:
        break;
    }

    return "NULL";
}


void CTraceLog::TraceL(eTraceLogLevel level, const char* pDesctription, ...) const
{
	if (level >= m_nLevel)
	{
		char cTmp[TRACE_LOG_MAX_DESCRIPTION_SIZE + 1] = { 0 };

		va_list ap;
		va_start(ap, pDesctription);
		_vsnprintf_s(cTmp, TRACE_LOG_MAX_DESCRIPTION_SIZE, pDesctription, ap);
		va_end(ap);

		std::string strLevelName = GetTraveLogLevelName(level);

		std::string strTmp = cTmp;
		_snprintf_s(cTmp, TRACE_LOG_MAX_DESCRIPTION_SIZE, "[%s] %s", strLevelName.c_str(), strTmp.c_str());

		//������־������ʾ����
		writeLog(level, cTmp);
	}
}

void CTraceLog::writeLog(eTraceLogLevel trace_log_level, char* message) const
{
	switch (trace_log_level)
	{
	case TRACE_LOG_LEVEL_CALL:
		LOG4CPLUS_TRACE(loggerRoot, message);
		break;
	case TRACE_LOG_LEVEL_DEBUG:
		LOG4CPLUS_DEBUG(loggerRoot, message);
		break;
	case TRACE_LOG_LEVEL_INFO:
		LOG4CPLUS_INFO(loggerRoot, message);
		break;
	case TRACE_LOG_LEVEL_WARNING:
		LOG4CPLUS_WARN(loggerRoot, message);
		break;
	case TRACE_LOG_LEVEL_ERROR:
		LOG4CPLUS_ERROR(loggerRoot, message);
		break;
	case TRACE_LOG_LEVEL_FATAL:
		LOG4CPLUS_FATAL(loggerRoot, message);
		break;
	default:
		break;
	}

//#ifdef DEBUG
	//��ӡ������̨
	std::string strMessage = message;
	//int size = MultiByteToWideChar(CP_ACP, 0, message, -1,NULL, 0);
	size_t size = strMessage.length();
	wchar_t* buffer = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, strMessage.c_str(), size, buffer, size * sizeof(wchar_t));
	buffer[size] = 0;  //ȷ���� '\0' ��β 
	OutputDebugString(buffer);
	OutputDebugString(_T("\n"));
	delete buffer;
	buffer = NULL;
//#endif

}