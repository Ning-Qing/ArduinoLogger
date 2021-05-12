#ifndef LOGGER_H
#define LOGGER_H
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

typedef void (*printfunc)(Print*);

 /*
 * %s	string (char*)
 * %c	char
 * %d	int
 * %f   double
 * %t	boole
 */

// LOG_LEVEL
// 0 disable 
// 1 output error info debug
// 2 output error info
// 3 output error

#define LOG_OFF 0
#define LOG_DEBUG 1
#define LOG_TEST 2
#define LOG_RUN 3

// #define LOG_LEVEL LOG_OFF
#define LOG_LEVEL LOG_DEBUG
// #define LOG_LEVEL LOG_TEST
// #define LOG_LEVEL LOG_RUN

#define debug(msg, args...) _debug(__FILE__,__LINE__,msg, args)
#define error(msg, args...) _error(__FILE__,__LINE__,msg, args)


class Logger
{
	public:
	Logger()
	#if LOG_LEVEL > 0
	:_logOutput(NULL)
	#endif
	{

	}

	Logger(Print *logOutput){
	#if LOG_LEVEL > 0
	_logOutput = logOutput;
	#endif
	}

	template <class T,typename... Args> void _debug(const char *_file,int line,T msg, Args... args)
	{
		#if LOG_LEVEL > 0 && LOG_LEVEL < 2
		char file[20];
		strcpy(file,_file);
		printLog(file,line,LOG_DEBUG,msg, args...);
		#endif
	}

	template <class T,typename... Args> void _error(const char *_file,int line,T msg,Args... args)
	{
		#if LOG_LEVEL > 0
		char file[20];
		strcpy(file,_file);
		printLog(file,line,LOG_RUN,msg, args...);
		#endif
	}

	template <class T,typename... Args> void info(T msg, ...)
	{
		#if LOG_LEVEL > 0 && LOG_LEVEL < 3
		va_list args;
		va_start(args,msg);
		print(msg, args);
		#endif
	}

	void setPrefix(const char *_prefix);

	private:
	#if LOG_LEVEL > 0
	Print* _logOutput;
	char prefix[20];
	#endif

	

	void print(const __FlashStringHelper *format, va_list args);
	void print(const char *format,va_list args);
	void printf(const char format,va_list *args);

	template <class T> void printLog(const char *file,int line,int level,T msg, ...){
		#if LOG_LEVEL > 0
		if(prefix != NULL) _logOutput->print(prefix);
		_logOutput->print(" ");

		va_list args;
		va_start(args,msg);
		print(msg, args);

		_logOutput->print(" file: ");
		_logOutput->print(file);
		_logOutput->print(" line: ");
		_logOutput->print(line);
		
		if (level) {
			static const char levels[] = "D E";
			_logOutput->print(" level: ");
			_logOutput->print(levels[level - 1]);
		}

		_logOutput->println();
		#endif
	}
};
#endif