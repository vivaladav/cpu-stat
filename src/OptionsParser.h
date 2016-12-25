#pragma once

// OptionsParser - objects that parses command line options.

class OptionsParser
{
public:
	OptionsParser(int argc, char * argv[], const char * appName, const char * version);

	bool HasError() const;
	int GetErrorCode() const;

	bool ExitRequested() const;

	// -- OPTIONS --
	int GetOptionCPU() const;
	int GetOptionDelay() const;
	int GetOptionState() const;
	unsigned int GetOptionPrecision() const;
	bool GetOptionFull() const;
	bool GetOptionPrintAll() const;
	bool GetOptionVerbose() const;

public:
	// -- SHORT OPTIONS --
	static const char * STR_OPT_ALL;
	static const char * STR_OPT_CPU;
	static const char * STR_OPT_DELAY;
	static const char * STR_OPT_FULL;
	static const char * STR_OPT_HELP;
	static const char * STR_OPT_PRECISION;
	static const char * STR_OPT_STATE;
	static const char * STR_OPT_VERBOSE;

	// -- LONG OPTIONS --
	static const char * STR_LONGOPT_ALL;
	static const char * STR_LONGOPT_FULL;
	static const char * STR_LONGOPT_HELP;
	static const char * STR_LONGOPT_VERBOSE;
	static const char * STR_LONGOPT_VERSION;

	// -- ERRORS --
	static const int NO_ERROR;
	static const int ERR_PARAM;
	static const int ERR_UNKNOWN_OPT;

	static const char * STR_ERR;
	static const char * STR_ERR_PARAM;
	static const char * STR_ERR_UNKNOWN_OPT;

private:
	void PrintHelp();
	void PrintUsage();
	void PrintVersion();

private:
	static const int MIN_DELAY;

private:
	const char * mAppName;
	const char * mVersion;

	int mError;

	int optCPU;
	int optDelay;
	int optState;

	unsigned int optPrecision;

	bool optFull;
	bool optPrintAll;
	bool optVerbose;

	bool mExit;
};

// == INLINE FUNCTIONS ==

inline bool OptionsParser::HasError() const { return mError != OptionsParser::NO_ERROR; }

inline int OptionsParser::GetErrorCode() const { return mError; }

inline bool OptionsParser::ExitRequested() const { return mExit; }

// -- OPTIONS --
inline int OptionsParser::GetOptionCPU() const { return optCPU; }
inline int OptionsParser::GetOptionDelay() const { return optDelay; }
inline int OptionsParser::GetOptionState() const { return optState; }
inline unsigned int OptionsParser::GetOptionPrecision() const { return optPrecision; }
inline bool OptionsParser::GetOptionFull() const { return optFull; }
inline bool OptionsParser::GetOptionPrintAll() const { return optPrintAll; }
inline bool OptionsParser::GetOptionVerbose() const { return optVerbose; }
