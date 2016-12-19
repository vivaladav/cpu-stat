/*
 *	cpu-stat - a simple program to get CPU stats on Linux
 *
 *	by Davide Coppola - http://www.davidecoppola.com
 *
 *	0.00.01		19-Dec-2016		First basic version.
 *
*/

#include "CPUSnapshot.h"

#include <chrono>
#include <iostream>
#include <thread>

void PrintActivePercentage(const CPUSnapshot & s1, const CPUSnapshot & s2);

int main(int argc, char * argv[])
{
	// snapshot 1
	CPUSnapshot s1;

	// 100ms pause
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	// snapshot 2
	CPUSnapshot s2;

	// print active percentage of tot
	PrintActivePercentage(s1, s2);

	return 0;
}

void PrintActivePercentage(const CPUSnapshot & s1, const CPUSnapshot & s2)
{
	const float ACTIVE_TIME		= s2.GetActiveTimeTotal() - s1.GetActiveTimeTotal();
	const float IDLE_TIME		= s2.GetIdleTimeTotal() - s1.GetIdleTimeTotal();
	const float TOTAL_TIME		= ACTIVE_TIME + IDLE_TIME;

	const float PERC_ACTIVE		= 100.f * ACTIVE_TIME / TOTAL_TIME;

	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout.precision(2);
	std::cout << PERC_ACTIVE << std::endl;
}
