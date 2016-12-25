#pragma once

// CPUData - container of stats for a CPU

#include <string>

class CPUData
{
public:
	void ReadData(const std::string & line);

	std::size_t GetActiveTime() const;
	std::size_t GetIdleTime() const;
	std::size_t GetStateTime(unsigned int state) const;
	std::size_t GetTotalTime() const;

	const std::string & GetLabel() const;

public:
	static bool IsDataCPUStats(const std::string & line);

public:
	enum CPUStates
	{
		S_USER = 0,
	    S_NICE,
	    S_SYSTEM,
	    S_IDLE,
	    S_IOWAIT,
	    S_IRQ,
	    S_SOFTIRQ,
	    S_STEAL,
	    S_GUEST,
	    S_GUEST_NICE,

		NUM_CPU_STATES
	};

private:
	static const std::string STR_CPU;
	static const std::string STR_TOT;

	static const std::size_t LEN_STR_CPU;

private:
	std::string mLabel;

	std::size_t mTimes[NUM_CPU_STATES];
};

// == INLINE FUNCTIONS ==

inline 	std::size_t CPUData::GetActiveTime() const
{
	return	mTimes[S_USER] +
			mTimes[S_NICE] +
			mTimes[S_SYSTEM] +
			mTimes[S_IRQ] +
			mTimes[S_SOFTIRQ] +
			mTimes[S_STEAL] +
			mTimes[S_GUEST] +
			mTimes[S_GUEST_NICE];
}

inline std::size_t CPUData::GetIdleTime() const
{
	return mTimes[S_IDLE] + mTimes[S_IOWAIT];
}

inline std::size_t CPUData::GetStateTime(unsigned int state) const
{
	if(state < NUM_CPU_STATES)
		return mTimes[state];
	else
		return 0;
}

inline std::size_t CPUData::GetTotalTime() const
{
	return	mTimes[S_USER] +
			mTimes[S_NICE] +
			mTimes[S_SYSTEM] +
			mTimes[S_IDLE] +
			mTimes[S_IOWAIT] +
			mTimes[S_IRQ] +
			mTimes[S_SOFTIRQ] +
			mTimes[S_STEAL] +
			mTimes[S_GUEST] +
			mTimes[S_GUEST_NICE];
}

inline const std::string & CPUData::GetLabel() const { return mLabel; }

inline bool CPUData::IsDataCPUStats(const std::string & line)
{
	return (!line.compare(0, LEN_STR_CPU, STR_CPU));
}
