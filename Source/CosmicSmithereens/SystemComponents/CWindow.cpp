#include "stdafx.h"

#include "CWindow.h"

#include "CApp.h"
#include "CWindowsSystem.h"

#include <DbgHelp.h>
#include <vld.h>

#include "Utilities\StringHelpers.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

CWindow::CWindow(std::wstring windowName, bool bCreatedOutsideProgram = false, HWND windowHandle = nullptr, std::wstring windowTitle = L"")
{
	m_bClassRegistered = false;
	m_bCreatedOutsideProgram = bCreatedOutsideProgram;
	m_windowHandle = windowHandle;
	m_bForeground = true;
	m_bHasFocus = true;
	m_bIsEnabled = true;
	m_bIsInitialized = false;
	m_bIsVisible = true;
	m_bKeyFocus = true;
	m_bMouseFocus = true;
	m_bRequestShutdown = false;
	m_dwExStyle = 0;
	m_dwStyle = 0;
	m_icon = NULL;
	m_iconSmall = NULL;
	m_lastScreenState = WindowState::Windowed;
	m_screenState = WindowState::Windowed;
	m_windowState = WindowStateEx::Normal;
	m_oldWndProc = NULL;
	m_pBackColor = std::unique_ptr<CColor>(new CColor(0.f, 0.f, 0.f, 1.f));
	m_className = windowName;
	if (windowTitle != L"")
	{
		m_title = windowTitle;
	}
	else
	{
		m_title = windowName;
	}
	m_name = windowName;

	m_pNormalWindowRect = std::unique_ptr<CRect>(new CRect(0, 0, 1280, 720));
	m_pWindowRect = std::unique_ptr<CRect>(new CRect(0, 0, 1280, 720));

	CApp::GetApp()->GetSystem()->Create(m_name, Window(this));
}

bool CWindow::Initialize()
{
	Enable();
	Show();

	SetBackColor(RGB(0, 0, 0));

	HICON ico = static_cast<HICON>(::LoadImageW(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0, 0,
		LR_DEFAULTCOLOR | LR_SHARED | LR_DEFAULTSIZE));

	SetIcon(ico);
	SetSmIcon(ico);

	ZeroMemory(&m_windowClass, sizeof(WNDCLASSEXW));
	m_windowClass.cbSize = sizeof(m_windowClass);
	m_windowClass.cbClsExtra = 0;
	m_windowClass.cbWndExtra = 0;
	CColor backColor = GetBackColor();
	m_windowClass.hbrBackground = CreateSolidBrush(RGB(backColor.r * 255, backColor.g * 255, backColor.b * 255));

	m_windowClass.hCursor = static_cast<HCURSOR>(::LoadImageW(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0, 0,
		LR_DEFAULTCOLOR | LR_SHARED | LR_DEFAULTSIZE));

	m_windowClass.hIcon = static_cast<HICON>(::LoadImageW(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0, 0,
		LR_DEFAULTCOLOR | LR_SHARED | LR_DEFAULTSIZE));

	m_windowClass.hIconSm = static_cast<HICON>(::LoadImageW(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0, 0,
		LR_DEFAULTCOLOR | LR_SHARED | LR_DEFAULTSIZE));

	m_windowClass.hInstance = GetModuleHandleW(NULL);

	m_windowClass.lpfnWndProc = WndProc;
	m_windowClass.lpszMenuName = 0;
	m_windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	SetPosition(0, 0);
	SetWidth(GetSystemMetrics(SM_CXSCREEN));
	SetHeight(GetSystemMetrics(SM_CYSCREEN));
	SetNormRect(&CRect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
	SetWindowed();
	Focus();
	SendToForeground();
	m_dwStyle = WS_OVERLAPPEDWINDOW;
	m_dwExStyle = WS_EX_OVERLAPPEDWINDOW;

	if (m_windowHandle && m_bCreatedOutsideProgram)
	{
		if (m_bIsInitialized)
			return true;

		m_oldWndProc = GetWindowLongPtrW(m_windowHandle, GWLP_WNDPROC);

		LONG_PTR nResult = SetWindowLongPtrW(m_windowHandle, GWLP_WNDPROC, (LONG_PTR)WndProc);

		DWORD dwError = GetLastError();

		wchar_t buf[256];
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			buf, (sizeof(buf) / sizeof(wchar_t)), NULL);

		if (nResult == 0)
		{
			MGK_FATAL("System.Window, SetWindowLongPtr, " + WideStrToStr(buf));

			nResult = SetWindowLongPtrW(m_windowHandle, GWLP_WNDPROC, (LONG_PTR)m_oldWndProc);

			if (nResult == 0)
			{
				dwError = GetLastError();

				FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					buf, (sizeof(buf) / sizeof(wchar_t)), NULL);

				MGK_FATAL("System.Window, SetWindowLongPtr (Restore Original WndProc()), " + WideStrToStr(buf));
			}

			return false;
		}

		m_bIsInitialized = true;
		m_bClassRegistered = true;
		return true;
	}

	if (!m_windowClass.hInstance)
	{
		m_windowClass.hInstance = GetModuleHandleW(NULL);
	}

	if (!m_windowClass.lpszClassName || !StrCmp(m_windowClass.lpszClassName, m_className))
	{
		m_windowClass.lpszClassName = m_className.c_str();
	}

	if (!m_bClassRegistered)
	{
		if (!RegisterClassExW(&m_windowClass))
		{
			MGK_ERROR("Could not register the window class for [" + WideStrToStr(m_className) + "]!");
			return false;
		}
		m_bClassRegistered = true;
	}

	LPCWSTR title = m_title.c_str();
	m_windowHandle = CreateWindowExW(m_dwExStyle, m_windowClass.lpszClassName, title, m_dwStyle,
		m_pWindowRect->left, m_pWindowRect->top, (m_pWindowRect->right - m_pWindowRect->left), (m_pWindowRect->bottom - m_pWindowRect->top),
		NULL, NULL, m_windowClass.hInstance, this);

	if (!m_windowHandle)
	{
		m_bIsInitialized = false;

		return false;
	}

	m_bIsInitialized = true;
	return true;
}

void CWindow::Update()
{
}

void CWindow::Shutdown()
{
}

LRESULT CALLBACK CWindow::MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		case WM_DESTROY:
		{
			return 0;
		}
		break;

		case WM_CLOSE:
		{
			return SendMessageW(hwnd, WM_QUIT, NULL, NULL);
		}
		break;

		// All other messages pass to the message handler in the system class.
		default:
		{
			// Access the Windows System class from CApp to pass the remaining values to its message handler for processing.
			return DefWindowProcW(hwnd, umessage, wparam, lparam);
		}
	}
}

bool CWindow::IsInitialized()
{
	return false;
}

void CWindow::Quit()
{
}

bool CWindow::IsQuitting()
{
	return false;
}

void CWindow::Show()
{
}

void CWindow::Hide()
{
}

bool CWindow::IsVisible()
{
	return false;
}

void CWindow::Enable()
{
}

void CWindow::Disable()
{
}

bool CWindow::IsEnabled()
{
	return false;
}

void CWindow::Focus()
{
}

void CWindow::Unfocus()
{
}

bool CWindow::HasFocus()
{
	return false;
}

void CWindow::FocusKeyboard()
{
}

void CWindow::FocusMouse()
{
}

bool CWindow::HasKeyboardFocus()
{
	return false;
}

bool CWindow::HasMouseFocus()
{
	return false;
}

void CWindow::SendToForeground()
{
}

bool CWindow::IsForeground()
{
	return false;
}

void CWindow::SetFullscreen()
{
}

void CWindow::SetBorderlessFullscreen()
{
}

void CWindow::SetBorderlessWindowed()
{
}

void CWindow::SetWindowed()
{
}

void CWindow::SetWindowState(WindowState state)
{
}

WindowState CWindow::GetWindowState()
{
	return WindowState();
}

void CWindow::SetNormal()
{
}

void CWindow::SetMaximized()
{
}

void CWindow::SetMinimized()
{
}

void CWindow::SetWindowStateEx(WindowStateEx stateEx)
{
}

WindowStateEx CWindow::GetWindowStateEx()
{
	return WindowStateEx();
}

void CWindow::SetPosition(long x, long y)
{
}

void CWindow::GetPosition(long& x, long& y)
{
}

void CWindow::SetWidth(long width)
{
}

void CWindow::SetHeight(long height)
{
}

long CWindow::GetWidth()
{
	return 0;
}

long CWindow::GetHeight()
{
	return 0;
}

void CWindow::SetBackColor(unsigned long color)
{
}

unsigned long CWindow::GetBackColor()
{
	return 0;
}

void CWindow::SetWindowClassName(const std::wstring& name)
{
}

std::wstring CWindow::GetWindowClassName()
{
	return std::wstring();
}

void CWindow::SetTitle(const std::wstring& title)
{
}

std::wstring CWindow::GetTitle()
{
	return std::wstring();
}

void CWindow::SetIcon(const void* icon)
{
}

void* CWindow::GetIcon()
{
	return nullptr;
}

void CWindow::SetSmIcon(const void* smIcon)
{
}

void* CWindow::GetSmIcon()
{
	return nullptr;
}

CRect const* const CWindow::GetNormRect() const
{
	return nullptr;
}

void CWindow::SetNormRect(const CRect* rect)
{
}

void* CWindow::GetHandle()
{
	return nullptr;
}

void CWindow::SetHandle(void* handle)
{
}

std::wstring CWindow::GetName()
{
	return std::wstring();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	return 
}
