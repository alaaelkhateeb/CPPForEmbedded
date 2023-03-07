/*
 * main.cpp
 *
 *  Created on: Feb 26, 2023
 *      Author: alaa
 */

#include "Logger.h"
#include <thread>
#include <stdio.h>
#include <mutex>
#include <ctime>
void log_test(int n) {
	Logger t("APP", lDebug, mFile, "log.txt");
	t.setLogMode("APP", mFile);
	t << "HIIIIIIII";
	t.setLogMode("APP", mConsole);
	t.setLogLevel("APP", lInfo);
	t << " console";
	t.setLogLevel("APP", lOff);
	t << "level is off";
}

int main() {
	std::thread threads[10];

	for (int i = 0; i < 10; i++)
		threads[i] = std::thread(log_test, i);

	for (int i = 0; i < 10; i++)
		threads[i].join();
	return 0;
}
