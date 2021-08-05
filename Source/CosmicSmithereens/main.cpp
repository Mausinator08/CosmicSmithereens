#include "stdafx.h"

#include "CApp.h"

#if defined(_UNICODE)

/*!
 *  The unicode main entry point for Windows GUI applications.
 *
 *      @param [in] hInstance     
 *      @param [in] hPrevInstance 
 *      @param [in] lpCmdLine     
 *      @param [in] nShowCmd      
 *
 *      @return Result of running the application
 */
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
	// Creates (instantiates) the game with the applicaiton
	// name of "CosmicSmithereens".
	if (!CApp::CreateApp(L"CosmicSmithereens"))
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

#endif
