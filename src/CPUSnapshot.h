#pragma once

// CPUSnapshot - a snapshot of all the CPU data from /proc/stat at a given time

#include "CPUData.h"

#include <vector>

class CPUSnapshot
{
public:
	CPUSnapshot();

	std::size_t GetNumEntries() const;

	const char * GetLabelTotal() const;
	const char * GetLabel(unsigned int cpu) const;

	std::size_t GetActiveTimeTotal() const;
	std::size_t GetActiveTime(unsigned int cpu) const;

	std::size_t GetIdleTimeTotal() const;
	std::size_t GetIdleTime(unsigned int cpu) const;

	std::size_t GetStateTimeTotal(unsigned int state) const;
	std::size_t GetStateTime(unsigned int state, unsigned int cpu) const;

	std::size_t GetTotalTimeTotal() const;
	std::size_t GetTotalTime(unsigned int cpu) const;

private:
	static const int INDEX_TOT;

private:
	std::vector<CPUData> mEntries;
};

// == INLINE FUNCTIONS ==

inline std::size_t CPUSnapshot::GetNumEntries() const { return mEntries.size() - 1; }

inline const char * CPUSnapshot::GetLabelTotal() const { return mEntries[INDEX_TOT].GetLabel().c_str(); }

inline const char * CPUSnapshot::GetLabel(unsigned int cpu) const
{
	// skip total
	++cpu;

	if(cpu < mEntries.size())
		return mEntries[cpu].GetLabel().c_str();
	else
		return nullptr;
}

inline std::size_t CPUSnapshot::GetActiveTimeTotal() const { return mEntries[INDEX_TOT].GetActiveTime(); }

inline std::size_t CPUSnapshot::GetActiveTime(unsigned int cpu) const
{
	// skip total
	++cpu;

	if(cpu < mEntries.size())
		return mEntries[cpu].GetActiveTime();
	else
		return 0;
}

inline std::size_t CPUSnapshot::GetIdleTimeTotal() const { return mEntries[INDEX_TOT].GetIdleTime(); }

inline std::size_t CPUSnapshot::GetIdleTime(unsigned int cpu) const
{
	// skip total
	++cpu;

	if(cpu < mEntries.size())
		return mEntries[cpu].GetIdleTime();
	else
		return 0;
}

inline std::size_t CPUSnapshot::GetStateTimeTotal(unsigned int state) const { return mEntries[INDEX_TOT].GetStateTime(state); }

inline std::size_t CPUSnapshot::GetStateTime(unsigned int state, unsigned int cpu) const
{
	// skip total
	++cpu;

	if(cpu < mEntries.size())
		return mEntries[cpu].GetStateTime(state);
	else
		return 0;
}

inline std::size_t CPUSnapshot::GetTotalTimeTotal() const { return mEntries[INDEX_TOT].GetTotalTime(); }

inline std::size_t CPUSnapshot::GetTotalTime(unsigned int cpu) const
{
	// skip total
	++cpu;

	if(cpu < mEntries.size())
		return mEntries[cpu].GetTotalTime();
	else
		return 0;
}
