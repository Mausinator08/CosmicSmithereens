#include "stdafx.h"

#include "CApp.h"

#include <SDL.h>

/**
 * @brief 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char *argv[])
{
	// Creates (instantiates) the game with the applicaiton
	// name of "CosmicSmithereens".
	if (!CApp::CreateApp("CosmicSmithereens"))
	{
		// If unsuccessfull then return 0.
		return 0;
	}

	// Runs the created instance of the application statically held in CApp class.
	CApp::RunApp();

	// Destroys the application instance after the running loop is broken and all systems are shutdown.
	CApp::DestroyApp();

	return 0;
}
