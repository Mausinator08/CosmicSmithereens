#include "stdafx.h"

#include "CApp.h"
#include "UI/Dialog.h"

#include "memplumber.h"
#include "Debugging/Debug.h"
#include "FileSystem/FSPlatform.h"
#include "Functions/Strings.h"
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
		if (!MakeDirectory(L"Logs/"))
		{
			std::cout << "Could not create directory \"Logs/\"!" << std::endl;
		}

		MemPlumber::start(Debugging::IsDebugBuild(), ws2s(ConvertToPathStyle(L"Logs/memleaks-verbose.log")).c_str());

		// Creates (instantiates) the game with the applicaiton
		// name of "CosmicSmithereens".
		if (!CApp::CreateApp(L"CosmicSmithereens"))
		{
			ShowFatalDialog("Could not create application!");
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
		char *error_type = NULL;
		_itoa(e.type, error_type, 10);

		ShowFatalDialog(std::string().append("Error: ").append(e.name).append("\nError Type: ").append(error_type).append("\n").c_str());

		returnVal = e.retval;
	}

	size_t count = 0;
	uint64_t size = 0;
	MemPlumber::memLeakCheck(count, size, Debugging::IsDebugBuild(), ws2s(ConvertToPathStyle(L"Logs/memleaks-verbose.log")).c_str());

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
