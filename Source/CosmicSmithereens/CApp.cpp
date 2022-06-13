#include "stdafx.h"

#include "CApp.h"
#include "UI/Dialog.h"
#include "Functions/Strings.h"

#include <SDL.h>

std::unique_ptr<CApp> CApp::m_pInstance = NULL;

/**
 *  Constructor.
 *
 *      @param [in] lpcwstrApplicatonName 
 */
CApp::CApp(std::wstring applicationName)
{
	// Initial values
	m_bTerminate = false;
	m_applicationName = applicationName;
}

/**
 *  Destructor.
 */
CApp::~CApp()
{
}

/**
 *  Returns the app's window.
 *
 *      @return The system.
 */
SDL_Window *const CApp::GetWindow() const
{
	// If the unique_ptr itself is nullptr, then return nullptr.
	if (!m_pWindow)
	{
		return nullptr;
	}

	// If we get this far, we have a system object to return and view.
	return m_pWindow;
}

/**
 *  Returns true if the app is terminating.
 *
 *      @return True if terminating. False if not.
 */
bool CApp::IsTerminating()
{
	// Return whether the program is terminating or not.
	return m_bTerminate;
}

/**
 *  Creates the app.
 *
 *      @param [in] lpcwstrApplicatonName 
 *
 *      @return True if successfull. False if not.
 */
bool CApp::CreateApp(std::wstring applicatonName)
{
	// If an instance already exists, then do not create another application instance.
	if (m_pInstance)
	{
		if (m_pInstance.get())
		{
			return false;
		}
	}

	// Construct a new application instance.
	m_pInstance = std::unique_ptr<CApp>(new CApp(applicatonName));

	// If the instance pointer is nullptr then the above failed.
	if (!m_pInstance)
	{
		return false;
	}

	// If the application instance is nullptr then the above failed.
	if (!m_pInstance.get())
	{
		return false;
	}

	// If we get this far, then return true, for we are successfull.
	return true;
}

/**
 *  Returns the app's app.
 *
 *      @return The app.
 */
CApp *const CApp::GetApp()
{
	// If the instance pointer is nullptr, return nullptr.
	if (!m_pInstance)
	{
		return nullptr;
	}

	// If the application instance is nullptr, return nullptr.
	if (!m_pInstance.get())
	{
		return nullptr;
	}

	// If we get this far, we have an application instance, so return it for viewing.
	return m_pInstance.get();
}

/**
 *  Runs the app.
 */
void CApp::RunApp()
{
	// If the instance pointer is nullptr, return.
	if (!m_pInstance)
	{
		return;
	}

	// If the application instance is nullptr, return.
	if (!m_pInstance.get())
	{
		return;
	}

	// Otherwise, run the instance.
	m_pInstance->Run();
}

/**
 *  Destroys the app.
 */
void CApp::DestroyApp()
{
	// If the instance pointer is nullptr, return.
	if (!m_pInstance)
	{
		return;
	}

	// If the application instance is nullptr, return.
	if (!m_pInstance.get())
	{
		return;
	}

	// Otherwise, reset the application instance to destroy it.
	m_pInstance.reset();
}

bool CApp::IsAppTerminating()
{
	return m_pInstance->IsTerminating();
}

void CApp::QuitApp()
{
	m_pInstance->Quit();
}

void CApp::PromptQuitApp()
{
	m_pInstance->PromptQuit();
}

/**
 *  Initializes the app.
 *
 *      @return True if successfull. False if not.
 */
bool CApp::Initialize()
{
	// Initialize the SDL2 system.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Could not initialize SDL2 with SDL_INIT_VIDEO!" << SDL_GetError() << std::endl;

		return false;
	}

	m_pWindow = SDL_CreateWindow(
		ws2s(m_applicationName).c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280,
		720,
		SDL_WINDOW_SHOWN |
			SDL_WINDOW_ALLOW_HIGHDPI);

	if (!m_pWindow)
	{
		std::cout << "Could not create SDL2 window!" << SDL_GetError() << std::endl;

		return false;
	}

	SDL_UpdateWindowSurface(m_pWindow);

	// Return true here, for at this point we were successfull.
	return true;
}

/**
 *  Updates the app.
 */
void CApp::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			PromptQuit();
		}
	}

	// If the instance pointer for window is valid...
	SDL_UpdateWindowSurface(m_pWindow);
}

/**
 *  Shutdown the app.
 */
void CApp::Shutdown()
{
	// Everything in Shutdown() will only be called after the loop is terminated.

	// If window is valid and is still initialized, call its Shutdown() method.
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

/**
 *  Runs the app instance.
 */
void CApp::Run()
{
	// If Initialize() fails then Shutdown() and exit.
	if (!Initialize())
	{
		Shutdown();
		return;
	}

	// Loop until it's time to terminate the program.
	while (m_bTerminate == false)
	{
		// Run one frame update iteration. (This can include game updates and rendering.)
		Update();
	}

	// Release all resources.
	Shutdown();
}

void CApp::Quit()
{
	m_bTerminate = true;
}

void CApp::PromptQuit()
{
	int iQuitting = ShowPrompt("QUIT?", "Are you sure you want to quit?");

	if (iQuitting == PROMPT_USER_RESONSE::YES)
	{
		m_bTerminate = true;
		return;
	}
}