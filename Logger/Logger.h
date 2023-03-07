/*
 * Logger.h
 *
 *  Created on: Mar 4, 2023
 *      Author: alaa
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#include <stdio.h>
#include <mutex>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>



#define StartIndex   10
#define EndIndex    20

typedef enum {
	lOff, lError, lWarn, lInfo, lDebug,
} LogLevel;

typedef enum {
	mFile, mConsole, mRemote,
} LogMode;

class Logger {
private:
	std::string AppId;
	LogLevel logLevel;
	LogMode logMode;

	std::string getTimestamp();
	int logNum;
	std::string fileName;
	std::ofstream fileStream;

public:
	Logger(std::string appId, LogLevel logLevel, LogMode logMode,
			std::string fileName);
	void setLogLevel(std::string appId, LogLevel logLevel);
	void setLogMode(std::string appId, LogMode logMode);
	friend std::ostream& operator <<(Logger &logger, const char *logMsg);
	~Logger();
};

#endif /* LOGGER_H_ */
