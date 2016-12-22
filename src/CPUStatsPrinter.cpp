#include "CPUStatsPrinter.h"

#include "CPUSnapshot.h"

#include <iostream>

CPUStatsPrinter::CPUStatsPrinter(const CPUSnapshot& s1, const CPUSnapshot& s2)
	: mS1(s1)
	, mS2(s2)
{

}

void CPUStatsPrinter::PrintActivePercentageTotal()
{
	const float ACTIVE_TIME		= mS2.GetActiveTimeTotal() - mS1.GetActiveTimeTotal();
	const float IDLE_TIME		= mS2.GetIdleTimeTotal() - mS1.GetIdleTimeTotal();
	const float TOTAL_TIME		= ACTIVE_TIME + IDLE_TIME;

	const float PERC_ACTIVE		= 100.f * ACTIVE_TIME / TOTAL_TIME;

	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout.precision(2);
	std::cout << PERC_ACTIVE << std::endl;
}

void CPUStatsPrinter::PrintActivePercentageAll()
{
	// PRINT TOTAL
	PrintActivePercentageTotal();

	// PRINT ALL CPUS
	const unsigned int NUM_ENTRIES = mS1.GetNumEntries();

	for(unsigned int i = 0; i < NUM_ENTRIES; ++i)
	{
		const float ACTIVE_TIME		= mS2.GetActiveTime(i) - mS1.GetActiveTime(i);
		const float IDLE_TIME		= mS2.GetIdleTime(i) - mS1.GetIdleTime(i);
		const float TOTAL_TIME		= ACTIVE_TIME + IDLE_TIME;

		const float PERC_ACTIVE		= 100.f * ACTIVE_TIME / TOTAL_TIME;

		std::cout.setf(std::ios::fixed, std::ios::floatfield);
		std::cout.precision(2);
		std::cout << PERC_ACTIVE << std::endl;
	}
}
