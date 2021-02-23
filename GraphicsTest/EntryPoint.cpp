#include "ProgramManager.h"

int main()
{
	ProgramManager program;

	if (!program.Initialise())
	{
		return -1;
	}

	program.Run();

	program.ShutDown();

	return 0;
}