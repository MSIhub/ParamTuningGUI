#include "cueing_process_handler.h"


namespace cueing_handler
{

	void startCueingProcess()
	{
		ShellExecute(NULL, L"open", L"executables\\MotionCueing.exe", NULL, NULL, SW_SHOWDEFAULT);
	}

	void startCueingWithDataExtractionFromMFS()
	{

		ShellExecute(NULL, L"open", L"executables\\MotionCueing.exe", NULL, NULL, SW_SHOWDEFAULT);
		Sleep(2000); // Wait for 2 seconds before launching the data extraction
		ShellExecute(NULL, L"open", L"executables\\MFS22Plugin.exe", NULL, NULL, SW_SHOWDEFAULT);	
	}
}
