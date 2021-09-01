#pragma once

#pragma region Forward Declarations
class SDL_Window;
#pragma endregion

/**
 * @brief 
 * @author 
 * @since Wed Aug 18 2021
 */
class CApp
{
private:
#pragma region Constructors

	/**
	 *  Constructor. (deleted)
	 */
	CApp() = delete;
	/**
	 *  Constructor. (explicit)
	 *
	 *      @param [in] lpcwstrApplicatonName 
	 */
	explicit CApp(std::string applicatonName);

public:
	/**
	 *  Copy Constructor. (deleted)
	 *
	 *      @param [in] rApp 
	 */
	CApp(const CApp &application) = delete;
	/**
	 *  Destructor.
	 */
	~CApp();
#pragma endregion

#pragma region Operators
	/**
         *  Operator=Copies and assigns the app. (deleted)
         *
         *      @param [in] rApp
         *
         *      @return
         */
	CApp &operator=(const CApp &application) = delete;

#pragma endregion

#pragma region CApp Member Accessors

	/**
	 *  Returns the app's system.
	 *
	 *      @return The system.
	 */
	SDL_Window *const GetWindow() const;
	/**
	 *  Returns true if the app is terminating.
	 *
	 *      @return True if terminating. False if not.
	 */
	bool IsTerminating();

	/**
  	* @brief Gets the application's name
  	* @return Returns the application's name
  	*/
	std::string GetApplicatoinName();
#pragma endregion

#pragma region CApp Instance Members

	/**
     *  Creates the app.
     *
     *      @param [in] lpcwstrApplicatonName
     *
     *      @return True if successfull. False if not.
     */
	static bool CreateApp(std::string applicatonName);
	/**
	 *  Returns the app's app.
	 *
	 *      @return The app.
	 */
	static CApp *const GetApp();
	/**
	 *  Runs the app.
	 */
	static void RunApp();
	/**
	 *  Destroys the app.
	 */
	static void DestroyApp();
#pragma endregion

#pragma region CApp Member Functions
protected:
	/**
	 *  Initializes the app.
	 *
	 *      @return True if successfull. False if not.
	 */
	bool Initialize();
	/**
	 *  Updates the app.
	 */
	void Update();
	/**
	 *  Shutdown the app.
	 */
	void Shutdown();

public:
	/**
	 *  Runs the app instance.
	 */
	void Run();
#pragma endregion

private:
#pragma region Control Members
	bool m_bTerminate;
#pragma endregion

#pragma region Instance Members
	static std::unique_ptr<CApp> m_pInstance;
	std::string m_applicationName;
#pragma endregion

#pragma region System Members
	SDL_Window *m_pWindow;
#pragma endregion
};
