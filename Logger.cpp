#include "Logger.h"

void Logger::setPrefix(const char *_prefix)
{
#if LOG_LEVEL > 0
	strcpy(prefix,_prefix);
#endif
}

void Logger::print(const char *format, va_list args)
{
#if LOG_LEVEL > 0
    for (; *format != 0; ++format)
    {
        if(*format == '%')
        {
            ++format;
            printf(*format, &args);
        }
        else
        {
            _logOutput->print(*format);
        }
    }
#endif
}

void Logger::printf(const char format, va_list *args) {
#ifndef DISABLE_LOGGING
	if (format == '%')
	{
		_logOutput->print(format);
	}
	else if (format == 's')
	{
		register char *s = (char *)va_arg(*args, int);
		_logOutput->print(s);
	}
	else if (format == 'd')
	{
		_logOutput->print(va_arg(*args, int), DEC);
	}
	else if (format == 'f')
	{
		_logOutput->print(va_arg(*args, double));
	}
	else if (format == 'c')
	{
		_logOutput->print((char) va_arg(*args, int));
	}
	else if (format == 't')
	{
		if (va_arg(*args, int) == 1)
		{
			_logOutput->print(F("true"));
		}
		else
		{
			_logOutput->print(F("false"));
		}
	}
#endif
}