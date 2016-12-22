
class CPUSnapshot;

class CPUStatsPrinter
{
public:
	CPUStatsPrinter(const CPUSnapshot& s1, const CPUSnapshot& s2);

	void PrintActivePercentageTotal();
	void PrintActivePercentageAll();

private:
	const CPUSnapshot & mS1;
	const CPUSnapshot & mS2;
};
