class CPUSnapshot;

class CPUStatsPrinter
{
public:
	CPUStatsPrinter(const CPUSnapshot& s1, const CPUSnapshot& s2);

	void PrintActivePercentageTotal();
	void PrintActivePercentageAll();

	void SetPrecision(unsigned int prec);

private:
	float GetPercActiveTotal();
	float GetPercActive(unsigned int cpu);

private:
	const CPUSnapshot & mS1;
	const CPUSnapshot & mS2;

	unsigned int mPrecision;
};

inline void CPUStatsPrinter::SetPrecision(unsigned int prec) { mPrecision = prec; }
