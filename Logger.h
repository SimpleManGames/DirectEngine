#ifndef _LOGGER_H
#define _LOGGER_H

//C Runtime Header Files
//----------------------
#ifndef _VECTOR_
#include <vector>
#endif

//Additional Include Files
//------------------------
#ifndef _STRING_H
#include "string.h"
#endif

//Enumaration
//-----------
enum LogType
{
	Info,
	Warning,
	Error,
	ToDo
};

//Structs
//--------------
struct LogData
{
	LogData(LogType t, const std::tstring& m)
		: Type(t)
		, Message(m)
	{}

	const std::tstring ToString();

	LogType Type;
	std::tstring Message;
};

//Defines
//--------------
#define LOGTYPE_INFO LogType::Info,__LINE__,__FILE__
#define LOGTYPE_WARNING LogType::Warning,__LINE__,__FILE__
#define LOGTYPE_ERROR LogType::Error,__LINE__,__FILE__
#define LOGTYPE_TODO LogType::ToDo,__LINE__,__FILE__

//Class Logger
//--------------
class Logger
{
public:
	//Methods
	static void Log(const std::tstring& Message, LogType type, int ln, const std::tstring& fn, bool logtofile = false);
	static void WriteLogFile();

private:
	//Methods
	//Constructor & Destructor
	Logger(void);
	~Logger(void);
	//Copy constructor & Assignment operator
	Logger(const Logger& tRef);
	Logger& operator=(const Logger& tRef);

	//Members
	static std::vector<LogData> m_LogMessages;
};
#endif