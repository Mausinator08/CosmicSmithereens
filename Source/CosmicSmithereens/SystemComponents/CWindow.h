#pragma once

#include "Types/CRect.h"
#include "Geometry/CColor.h"

#pragma region Forward Declarations

class CWindowsSystem;
class CRect;
class CColor;

#pragma endregion

#pragma region Enumerations

// Fullscreen, Borderless Fullscreen, Borderless Windowed, Windowed
enum class WindowState
{
	Fullscreen, Borderless_Fullscreen, Borderless_Windowed, Windowed
};

// Normal, Max, Min
enum class WindowStateEx
{
	Normal, Maximized, Minimized
};

#pragma endregion

class CWindow 
{ 
#pragma region Constructors

public:
	 /*!
	  *  Default Constructor. (deleted)
	  */
	 CWindow() = delete;

	 /*!
	  *  Explicit Constructor.
	  *
	  *      @param [in] windowName 
	  */	 
	 CWindow(std::wstring windowName, bool bCreatedOutsideProgram, HWND windowHandle, std::wstring windowTitle);

#pragma endregion

#pragma region CWindow Control Methods

	 /*!
	  *  Initializes the window.
	  *
	  *      @return true if successfull, false if not successfull
	  */
	 bool Initialize();
	 /*!
	  *  Updates the window.
	  */
	 void Update();
	 /*!
	  *  Shutdown the window.
	  */
	 void Shutdown();

	 /*!
	  *  Message handler. (WndProc)
	  *
	  *      @param [in] hwnd     
	  *      @param [in] umessage 
	  *      @param [in] wparam   
	  *      @param [in] lparam   
	  *
	  *      @return Result of the processed message.
	  */
	 LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

#pragma endregion

#pragma region Accessors

	 bool IsInitialized();
	 void Quit();
	 bool IsQuitting();
	 void Show();
	 void Hide();
	 bool IsVisible();
	 void Enable();
	 void Disable();
	 bool IsEnabled();
	 void Focus();
	 void Unfocus();
	 bool HasFocus();
	 void FocusKeyboard();
	 void FocusMouse();
	 bool HasKeyboardFocus();
	 bool HasMouseFocus();
	 void SendToForeground();
	 bool IsForeground();
	 void SetFullscreen();
	 void SetBorderlessFullscreen();
	 void SetBorderlessWindowed();
	 void SetWindowed();
	 void SetWindowState(WindowState state);
	 WindowState GetWindowState();
	 void SetNormal();
	 void SetMaximized();
	 void SetMinimized();
	 void SetWindowStateEx(WindowStateEx stateEx);
	 WindowStateEx GetWindowStateEx();
	 void SetPosition(long x, long y);
	 void GetPosition(long& x, long& y);
	 void SetWidth(long width);
	 void SetHeight(long height);
	 long GetWidth();
	 long GetHeight();
	 void SetBackColor(unsigned long color);
	 unsigned long GetBackColor();
	 void SetWindowClassName(const std::wstring& name);
	 std::wstring GetWindowClassName();
	 void SetTitle(const std::wstring& title);
	 std::wstring GetTitle();
	 void SetIcon(const void* icon);
	 void* GetIcon();
	 void SetSmIcon(const void* smIcon);
	 void* GetSmIcon();
	 CRect const * const GetNormRect() const;
	 void SetNormRect(const CRect* rect);
	 void* GetHandle();
	 void SetHandle(void* handle);
	 std::wstring GetName();

#pragma endregion

#pragma region Windows System

private:

	 // Windows Specific
	 HWND m_windowHandle;
	 WNDCLASSEXW m_windowClass;
	 DEVMODEW m_screenSettings;
	 LONG m_dwStyle;
	 LONG m_dwExStyle;
	 LONG_PTR m_oldWndProc;
	 HICON m_icon;
	 HICON m_iconSmall;

	 // CWindow fields
	 std::wstring m_name;

	 bool m_bClassRegistered;
	 bool m_bCreatedOutsideProgram;

	 // Status
	 bool m_bIsInitialized;
	 bool m_bRequestShutdown;
	 
	 // Display Panel states...
	 bool m_bIsVisible;
	 bool m_bIsEnabled;
	 bool m_bHasFocus;
	 bool m_bKeyFocus;
	 bool m_bMouseFocus;
	 bool m_bForeground;
	 WindowState m_screenState;
	 WindowState m_lastScreenState;
	 WindowStateEx m_windowState;
	 
	 // Display Panel data...
	 std::unique_ptr<CRect> m_pWindowRect;
	 std::unique_ptr<CRect> m_pNormalWindowRect;
	 std::unique_ptr<CColor> m_pBackColor;

	 std::wstring m_className;
	 std::wstring m_title;

#pragma endregion
};
