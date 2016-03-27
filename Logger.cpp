//C Run Time Header Files
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#include <intrin.h>

//Additional Header Files
#ifndef _STRINGSTREAM_H
#include "stringstream.h"
#endif
#ifndef _IOSTREAM_H
#include "iostream.h"
#endif
#ifndef _FSTREAM_H
#include "fstream.h"
#endif
#ifndef _ASSERT_
#include "assert.h"
#endif

#include "Logger.h"

//Defines
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

//Declarations
std::vector<LogData> Logger::m_LogMessages;

//Class Logger
Logger::Logger(void)
{
}
Logger::~Logger(void)
{
}

void Logger::Log(const std::tstring& Message, LogType type, int ln, const std::tstring& fn, bool logtofile)
{
#if defined(DEBUG) | defined(_DEBUG)
	std::tstringstream buffer;

	switch (type)
	{
	case LogType::Info:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		buffer << _T("Info Message") << _T(" INFO: ") << Message.c_str();
		buffer << _T("\nFound in file: ") << fn;
		buffer << _T("\nAt linenumber: ") << ln;
		buffer << _T("\n");

		if (logtofile)
			m_LogMessages.push_back(LogData(LogType::Info, buffer.str()));

		std::tcout << _T("INFO: ") << Message.c_str() << std::endl;
		OutputDebugString(buffer.str().c_str());

		break;
	case LogType::Warning:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		buffer << _T("Warning Message") << _T(" WARNING: ") << Message.c_str();
		buffer << _T("\nFound in file: ") << fn;
		buffer << _T("\nAt linenumber: ") << ln;
		buffer << _T("\n");

		if (logtofile)
			m_LogMessages.push_back(LogData(LogType::Info, buffer.str()));

		std::tcout << _T("WARNING: ") << Message.c_str() << std::endl;
		OutputDebugString(buffer.str().c_str());

		break;
	case LogType::Error:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		buffer << _T("Error Message") << _T(" ERROR: ") << Message.c_str();
		buffer << _T("\nFound in file: ") << fn;
		buffer << _T("\nAt linenumber: ") << ln;
		buffer << _T("\n");

		if (logtofile)
			m_LogMessages.push_back(LogData(LogType::Info, buffer.str()));

		std::tcout << _T("ERROR: ") << Message.c_str() << std::endl;
		OutputDebugString(buffer.str().c_str());

		//Break when errors occur
		__nop();

		break;
	case LogType::ToDo:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTCYAN);
		buffer << _T("Todo Message") << _T(" TODO: ") << Message.c_str();
		buffer << _T("\nFound in file: ") << fn;
		buffer << _T("\nAt linenumber: ") << ln;
		buffer << _T("\n");

		if (logtofile)
			m_LogMessages.push_back(LogData(LogType::Info, buffer.str()));

		std::tcout << _T("TODO: ") << Message.c_str() << std::endl;
		OutputDebugString(buffer.str().c_str());

		break;
	}

	//clearing stringstream buffer
	buffer.clear();
	buffer.str(_T(""));
#endif
}

void Logger::WriteLogFile()
{
#if defined(DEBUG) | defined(_DEBUG)
	int currentlog = 0;
	for (LogData& logdata : m_LogMessages)
	{
		//Set the path
		std::tstringstream buffer;
		buffer << ".\\Logs\\" << _T("LogFile") << currentlog << _T(".txt") << _T("\0");

		//Create the log file
		//Open the log file
		//Open it for input design if file already exists whipe all content
		std::tofstream logfile(buffer.str().c_str(), std::ios::in | std::ios::out | std::ios::trunc);

		if (!logfile)
		{
			OutputDebugString(_T("Cannot create log file \n"));
			return;
		}

		//Fill up data 
		logfile << _T("Logfile ") << currentlog << std::endl;
		logfile << __DATE__ << _T(" ") << __TIME__ << std::endl;
		logfile << logdata.ToString() << std::endl;
		logfile << _T("End of log");

		//Close log file
		logfile.close();

		//Set value for the next logfile
		++currentlog;
	}
#endif
}

//LogData
const std::tstring LogData::ToString()
{
	std::tstringstream buffer;

	switch (Type)
	{
	case Info:
		buffer << _T("LogMessage Type: Info") << std::endl;
		buffer << Message << std::endl;
		return buffer.str();
		break;
	case Warning:
		buffer << _T("LogMessage Type: Warning") << std::endl;
		buffer << Message << std::endl;
		return buffer.str();
		break;
	case Error:
		buffer << _T("LogMessage Type: Error") << std::endl;
		buffer << Message << std::endl;
		return buffer.str();
		break;
	default:
		buffer << _T("LogMessage Type: Not supported") << std::endl;
		buffer << Message << std::endl;
		return buffer.str();
		break;
	}
}