#include "stdafx.h"

#include "CWindowsSystem.h"

#include "CWindow.h"

/*!
 *  Constructor.
 */
CWindowsSystem::CWindowsSystem()
{
	// Set initial values.
	m_windows = WindowMap();
	m_applicationName = L"";
	m_bIsInitialized = false;
	m_bQuitting = false;
	m_appHandle = GetApplicationHandle();
}

/*!
 *  Destructor.
 */
CWindowsSystem::~CWindowsSystem()
{
}

/*!
 *  Returns true if the windows system is initialized.
 *
 *      @return True if initialized. False if not.
 */
bool CWindowsSystem::IsInitialized()
{
	return m_bIsInitialized;
}

/*!
 *  Quittings the windows system.
 *
 *      @return True if quitting. False if not.
 */
bool CWindowsSystem::Quitting()
{
	return m_bQuitting;
}

/*!
 *  Returns the windows system's application name.
 *
 *      @return The application name.
 */
LPCWSTR const CWindowsSystem::GetApplicationName() const
{
	return m_applicationName;
}

/*!
 *  Returns the windows system's application handle.
 *
 *      @return The application handle.
 */
HINSTANCE CWindowsSystem::GetApplicationHandle() const
{
	return m_appHandle;
}

/*!
 *  Quits the windows system.
 */
void CWindowsSystem::Quit()
{
	m_bQuitting = true;
}

/*!
 *  Creates a window.
 *
 *      @param [in]     name    
 *      @param [in,out] pWindow 
 *
 *      @return true if successfull, or false if not successfull.
 */
bool CWindowsSystem::Create(std::wstring name, WeakWindow pWindow)
{
	if (m_windows.find(name) != m_windows.end()) {
		return false;
	}

	Window window = MakeStrongPtr<CWindow>(pWindow);

	m_windows.insert(std::make_pair(name, window));
	return true;
}

/*!
 *  Initializes the windows system.
 *
 *      @param [in] lpcwstrApplicationName 
 *      @param [in] lpwstrCmdLine          
 *
 *      @return True if successfull. False if not.
 */
bool CWindowsSystem::Initialize(const LPCWSTR applicationName, const LPWSTR cmdLine)
{
	// Set the application name
	m_applicationName = applicationName;

	// We made it this far, initialization successfull.
	m_bIsInitialized = true;
	return true;
}

/*!
 *  Shutdown the windows system.
 */
void CWindowsSystem::Shutdown()
{
	m_bIsInitialized = false;
}
