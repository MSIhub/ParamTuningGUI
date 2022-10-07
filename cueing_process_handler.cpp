#include "cueing_process_handler.h"


namespace cueing_handler
{

	void startCueingProcess()
	{
		ShellExecute(NULL, L"open", L"MotionCueing.exe", NULL, NULL, SW_SHOWDEFAULT);
	}
}
