// log4cplusDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TraceLog.h"
#include <direct.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//������־�洢Ŀ¼
	_mkdir("log");
	TRACE_A(TRACE_LOG_LEVEL_WARNING,"�����־");
	getchar();
	return 0;
}

