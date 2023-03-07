/*
 * Logger.cpp
 *
 *  Created on: Mar 4, 2023
 *      Author: alaa
 */
#include "Logger.h"
#include <stdio.h>
#include <mutex>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>


Logger::Logger(std::string appId, LogLevel logLevel, LogMode logMode,
		std::string fileName = "") {
	this->AppId = appId;
	this->logLevel = logLevel;
	this->logMode = logMode;
	this->fileName = fileName;
	if (this->fileName != "") {
		fileStream = std::ofstream(fileName);
	}
	this->logNum = 0;
}

std::string Logger::getTimestamp() {
	std::time_t localDateTime = std::time(nullptr);
	std::string dateAndTime = std::asctime(std::localtime(&localDateTime));
	std::string timestamp;
	for (uint8_t i = StartIndex;
			i <= EndIndex; i++) {
		timestamp += dateAndTime[i];
	}
	return timestamp;
}

std:: ostream& operator <<(Logger &logger, const char *logMsg) {
	std::mutex log_mutex;

	//Logger::log_mutex.lock();
	if (logger.logLevel == lOff) {

		if (logger.logMode == mFile) {
			std::scoped_lock lock(log_mutex);
			logger.fileStream << "|" << logger.getTimestamp() << "|"
					<< logger.AppId << "|" << logger.logNum << "|" << "lOff"
					<< "|" << std::endl;
			return logger.fileStream;
		}
		if (logger.logMode == mConsole) {
			std::scoped_lock lock(log_mutex);
			std::cout << "|" << logger.getTimestamp() << "|" << logger.AppId
					<< "|" << logger.logNum << "|" << "lOff" << "|"
					<< std::endl;
			return std::cout;
		}
	} else {
		std::string lLevel;
		switch (logger.logLevel) {
		case lError:
			lLevel = "lError";
			break;
		case lWarn:
			lLevel = "lWarn";
			break;
		case lInfo:
			lLevel = "lInfo";
			break;
		case lDebug:
			lLevel = "lDebug";
			break;
		}
		if (logger.logMode == mFile) {
			std::scoped_lock lock(log_mutex);
			logger.fileStream << "|" << logger.getTimestamp() << "|"
					<< logger.AppId << "|" << logger.logNum << "|" << lLevel
					<< "|" << logMsg << std::endl;
			logger.logNum++;
			return logger.fileStream;
		}
		if (logger.logMode == mConsole) {
			std::scoped_lock lock(log_mutex);
			std::cout << "|" << logger.getTimestamp() << "|" << logger.AppId
					<< "|" << logger.logNum << "|" << lLevel << "|"
					<< logMsg << std::endl;
			logger.logNum++;
			return std::cout;
		}
	}
}

void Logger::setLogLevel(std::string appId, LogLevel logLevel)
{
    if (appId != "")
    {
        this->AppId = appId;
    }
    this->logLevel = logLevel;
}

void Logger::setLogMode(std::string appId, LogMode logMode)
{
    if (appId != "")
    {
        this->AppId = appId;
    }
    this->logMode = logMode;
}

Logger::~Logger()
{
    if(fileStream)
    {
        fileStream.close();
    }
}
