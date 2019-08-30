#ifndef _TRACE_LOG_H
#define _TRACE_LOG_H

#include <windows.h>

//#include <loglog.h>
#include <log4cplus/logger.h>

//������־�����ַ���
#define TRACE_LOG_MAX_DESCRIPTION_SIZE   1024

using namespace log4cplus;

//��־�ȼ�
enum eTraceLogLevel
{
    TRACE_LOG_LEVEL_CALL = 100, //����
    TRACE_LOG_LEVEL_DEBUG = 200, //����
    TRACE_LOG_LEVEL_INFO = 300, //��Ϣ
    TRACE_LOG_LEVEL_WARNING = 400, //����
    TRACE_LOG_LEVEL_ERROR = 500, //����
    TRACE_LOG_LEVEL_FATAL = 800, //����
};

class CTraceLog
{
private:
    CTraceLog();
    std::string GetTraveLogLevelName(eTraceLogLevel level) const;
	//�������Ϊ��������Ȼ����� ���ܽ���this��ָ��ӡ�const CTraceLog��ת��Ϊ��CTraceLog...�Ĵ���
	void writeLog(eTraceLogLevel trace_log_level, char* message) const;

    int m_nLevel;
    static CTraceLog *ms_pInstance;

public:
    ~CTraceLog();
    static CTraceLog *GetInstance();
	void TraceL(eTraceLogLevel level, const char* fmt, ...) const;

	Logger loggerRoot;
};

//����������printf()����ʽ�������־����һ������Ϊ��־�ȼ�
#define TRACE_A(LEVEL,F,...) CTraceLog::GetInstance()->TraceL(LEVEL, F, __VA_ARGS__)

#endif