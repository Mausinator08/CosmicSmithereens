#include "stdafx.h"

#include "CApp.h"

std::unique_ptr<CApp> CApp::m_pInstance = NULL;

/*!
 *  Constructor.
 *
 *      @param [in] lpcwstrApplicatonName 
 */
CApp::CApp(const wchar_t* applicationName) {
	// Initial values
	m_bTerminate = false;
    m_applicationName = applicationName;
}

/*!
 *  Destructor.
 */
CApp::~CApp()
{
}

/*!
 *  Returns the app's system.
 *
 *      @return The system.
 */
// CWindowsSystem* const CApp::GetSystem() const
// {
// 	// If the unique_ptr itself is nullptr, then return nullptr.
// 	if (!m_pSystem) 
// 	{
// 		return nullptr;
// 	}

// 	// If the system instance raw pointer is nullptr, then return nullptr.
// 	if (!m_pSystem.get()) 
// 	{
// 		return nullptr;
// 	}

// 	// If we get this far, we have a system object to return and view.
// 	return m_pSystem.get();
// }

/*!
 *  Returns true if the app is terminating.
 *
 *      @return True if terminating. False if not.
 */
bool CApp::IsTerminating()
{
	// Return whether the program is terminating or not.
	return m_bTerminate;
}

/*!
 *  Creates the app.
 *
 *      @param [in] lpcwstrApplicatonName 
 *
 *      @return True if successfull. False if not.
 */
bool CApp::CreateApp(const wchar_t* applicatonName)
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

/*!
 *  Returns the app's app.
 *
 *      @return The app.
 */
CApp* const CApp::GetApp()
{
	// If the instance pointer is nullptr, return nullptr.
	if (!m_pInstance) {
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

/*!
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

/*!
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

/*!
 *  Initializes the app.
 *
 *      @return True if successfull. False if not.
 */
bool CApp::Initialize()
{
	// Initialize the system component.

	// Return true here, for at this point we were successfull.
	return true;
}

/*!
 *  Updates the app.
 */
void CApp::Update()
{
	// If the instance pointer for system is valid...
	
}

/*!
 *  Shutdown the app.
 */
void CApp::Shutdown()
{
	// Everything in Shutdown() will only be called after the loop is terminated.

	// If system is valid and is still initialized, call its Shutdown() method.
	
}

/*!
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
