#include "CPUSnapshot.h"

#include <fstream>

CPUSnapshot::CPUSnapshot()
{
	std::ifstream fileStat("/proc/stat");

	std::string line;

	while(std::getline(fileStat, line))
	{
		// cpu stats line found
		if(CPUData::IsDataCPUStats(line))
		{
			// store entry
			mEntries.emplace_back(CPUData());
			CPUData & entry = mEntries.back();

			entry.ReadData(line);
		}
	}
}
