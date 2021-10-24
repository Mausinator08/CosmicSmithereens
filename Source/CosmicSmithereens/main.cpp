#include "stdafx.h"

#include "CApp.h"

#include "memplumber.h"
#include "Debugging/Debug.h"
#include "FileSystem/FSPlatform.h"
#include <SDL.h>

/**
 * @brief 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char *argv[])
{
	int returnVal = 0;

	try
	{
		if (!FSPlatform::MakeDirectory(FSPlatform::ConvertToPathStyle("Logs/")))
		{
			std::cout << "Could not create directory \"Logs/\"!" << std::endl;
		}

		MemPlumber::start(Debugging::IsDebugBuild(), FSPlatform::ConvertToPathStyle("Logs/memleaks-verbose.log").c_str());

		// Creates (instantiates) the game with the applicaiton
		// name of "CosmicSmithereens".
		if (!CApp::CreateApp("CosmicSmithereens"))
		{
			std::cout << "Could not create application!" << std::endl;
			// If unsuccessfull then return 0.
			return 0;
		}

		// Runs the created instance of the application statically held in CApp class.
		CApp::RunApp();

		// Destroys the application instance after the running loop is broken and all systems are shutdown.
		CApp::DestroyApp();
	}
	catch (_exception e)
	{
		std::cout << printf_s("Error: %s\nError Type: %s", e.name, e.type) << std::endl;

		returnVal = e.retval;
	}

	size_t count = 0;
	uint64_t size = 0;
	MemPlumber::memLeakCheck(count, size, Debugging::IsDebugBuild(), FSPlatform::ConvertToPathStyle("Logs/memleaks-verbose.log").c_str());

	if (Debugging::IsDebugBuild() == true)
	{
		if (count > 0)
		{
			std::cout << printf_s("Memory has been leaked!\nLeak Count: %ull\nTotal Leaked Size: %ui64", count, size) << std::endl;
		}
		else
		{
			std::cout << "No detected memory leaks." << std::endl;
		}
	}

	return returnVal;
}
