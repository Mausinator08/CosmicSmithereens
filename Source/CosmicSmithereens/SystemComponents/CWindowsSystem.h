#pragma once

#pragma region Forward Declarations

class CWindow;

#pragma endregion

#pragma region Typedefs

typedef std::shared_ptr<CWindow> Window;
typedef std::weak_ptr<CWindow> WeakWindow;
typedef std::map<std::wstring, Window> WindowMap;

#pragma endregion

class CWindowsSystem 
{
public:
#pragma region Constructors
 /*!
  *  Constructor.
  */
 CWindowsSystem();
 /*!
  *  Copy Constructor (deleted).
  *
  *      @param [in] rWinSys 
  */
 CWindowsSystem(const CWindowsSystem& windowsSystem) = delete;
 /*!
  *  Destructor.
  */
 ~CWindowsSystem();
#pragma endregion

#pragma region Operators

 /*!
  *  Operator=Copies and assigns the windows system. (deleted)
  *
  *      @param [in] rWinSys
  *
  *      @return
  */
 CWindowsSystem& operator=(const CWindowsSystem& windowsSystem) = delete;

#pragma endregion

#pragma region Member Accessors
	// Getters
	// Class Specific
 /*!
  *  Returns true if the windows system is initialized.
  *
  *      @return True if initialized. False if not.
  */
 bool IsInitialized();
 /*!
  *  Quitting the windows system.
  *
  *      @return True if quitting. False if not.
  */
 bool Quitting();

	// Windows Specific
 /*!
  *  Returns the windows system's application name.
  *
  *      @return The application name.
  */
 LPCWSTR const GetApplicationName() const;
 /*!
  *  Returns the windows system's application handle.
  *
  *      @return The application handle.
  */
 HINSTANCE GetApplicationHandle() const;

	//Setters
	// Class Specific
 /*!
  *  Quits the windows system.
  */
 void Quit();
#pragma endregion

/*!
 *  Initializes the windows system.
 *
 *      @param [in] lpcwstrApplicationName 
 *      @param [in] lpwstrCmdLine          
 *
 *      @return True if successfull. False if not successfull.
 */
#pragma region CWindowsSystem Member Functions

 /*!
  *  Creates a window.
  *
  *      @param [in]     name    
  *      @param [in,out] pWindow 
  *
  *      @return true if successfull, or false if not successfull.
  */
 bool Create(std::wstring name, WeakWindow pWindow);
 /*!
  *  Initializes the windows system.
  *
  *      @param [in] applicationName 
  *      @param [in] cmdLine         
  *
  *      @return true if successfull, or false if not successfull
  */
 bool Initialize(const LPCWSTR applicationName,
                 const LPWSTR cmdLine = NULL);
 /*!
  *  Shutdown the windows system.
  */
 void Shutdown();
#pragma endregion

private:
#pragma region Windows System Member Variables
	
	// Window List
	WindowMap m_windows;

	LPCWSTR m_applicationName;
	HINSTANCE m_appHandle;
	 
	// Class Specific
	bool m_bIsInitialized;
	bool m_bQuitting;
#pragma endregion
};
