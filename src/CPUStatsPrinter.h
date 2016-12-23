class CPUSnapshot;

class CPUStatsPrinter
{
public:
	CPUStatsPrinter(const CPUSnapshot& s1, const CPUSnapshot& s2);

	void PrintActivePercentageTotal();
	void PrintActivePercentageAll();
	void PrintActivePercentageCPU(unsigned int cpu);

	void SetPrecision(unsigned int prec);

	void SetVerbose(bool val);

private:
	float GetPercActiveTotal();
	float GetPercActive(unsigned int cpu);

private:
	static const int CPU_LABEL_W = 3;

private:
	const CPUSnapshot & mS1;
	const CPUSnapshot & mS2;

	unsigned int mPrecision;

	bool mVerbose;
};

inline void CPUStatsPrinter::SetPrecision(unsigned int prec) { mPrecision = prec; }

inline void CPUStatsPrinter::SetVerbose(bool val) { mVerbose = val; }
