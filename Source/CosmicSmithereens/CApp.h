#pragma once

/*!
 * @brief 
 * @author 
 * @since Wed Aug 18 2021
 */
class CApp
{
private:
#pragma region Constructors

	/*!
	 *  Constructor. (deleted)
	 */
	CApp() = delete;
	/*!
	 *  Constructor. (explicit)
	 *
	 *      @param [in] lpcwstrApplicatonName 
	 */
	explicit CApp(const wchar_t* applicatonName);
public:

	/*!
	 *  Copy Constructor. (deleted)
	 *
	 *      @param [in] rApp 
	 */
	CApp(const CApp& application) = delete;
	/*!
	 *  Destructor.
	 */
	~CApp();
#pragma endregion

#pragma region Operators
        /*!
         *  Operator=Copies and assigns the app. (deleted)
         *
         *      @param [in] rApp
         *
         *      @return
         */
        CApp& operator=(const CApp& application) = delete;

#pragma endregion

#pragma region CApp Member Accessors

	/*!
	 *  Returns the app's system.
	 *
	 *      @return The system.
	 */
	//CWindowsSystem* const GetSystem() const;
	/*!
	 *  Returns true if the app is terminating.
	 *
	 *      @return True if terminating. False if not.
	 */
	bool IsTerminating();
#pragma endregion

#pragma region CApp Instance Members

    /*!
     *  Creates the app.
     *
     *      @param [in] lpcwstrApplicatonName
     *
     *      @return True if successfull. False if not.
     */
	static bool CreateApp(const wchar_t* applicatonName);
	/*!
	 *  Returns the app's app.
	 *
	 *      @return The app.
	 */
	static CApp* const GetApp();
	/*!
	 *  Runs the app.
	 */
	static void RunApp();
	/*!
	 *  Destroys the app.
	 */
	static void DestroyApp();
#pragma endregion

#pragma region CApp Member Functions
protected:

	/*!
	 *  Initializes the app.
	 *
	 *      @return True if successfull. False if not.
	 */
	bool Initialize();
	/*!
	 *  Updates the app.
	 */
	void Update();
	/*!
	 *  Shutdown the app.
	 */
	void Shutdown();
public:

	/*!
	 *  Runs the app instance.
	 */
	void Run();
#pragma endregion

private:

#pragma region Control Members
	bool m_bTerminate;
	static std::unique_ptr<CApp> m_pInstance;
	const wchar_t* m_applicationName;
#pragma endregion
};
