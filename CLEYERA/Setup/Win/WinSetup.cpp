#include"WinSetup.h"



WindowsSetup::WindowsSetup()
{
}

WindowsSetup::~WindowsSetup()
{
}

WindowsSetup* WindowsSetup::GetInstance()
{
	static WindowsSetup instance;
	return &instance;

}

LRESULT CALLBACK WindowsSetup::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
	{
		return true;
	}
	//メッセージにおいて固有の動作を行う
	switch (msg)
	{
		//ウインドウが破棄
	case WM_DESTROY:
		//OSに対しアプリ終了を伝える
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


void WindowsSetup::Initialize(const int32_t  kClientWidth, const int32_t  kClientHeight)
{

	//ウインドウプロージャー
	//wc_.lpfnWndProc = WindowProc;
	WindowsSetup::GetInstance()->wc_.lpfnWndProc = WindowsSetup::WindowProc;

	//ウインドウクラス名
	//wc_.lpszClassName = L"CLEYERA";
	WindowsSetup::GetInstance()->wc_.lpszClassName = L"CLEYERA";

	//インスタンス
	WindowsSetup::GetInstance()->wc_.hInstance = GetModuleHandle(nullptr);
	//wc_.hInstance = GetModuleHandle(nullptr);
	//カーソル
	WindowsSetup::GetInstance()->wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);


	RegisterClass(&WindowsSetup::GetInstance()->wc_);


	//クライアントの領域設定
	RECT wrc = { 0,0,kClientWidth,kClientHeight };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);



	//ウインドウの生成
	WindowsSetup::GetInstance()->hwnd = CreateWindow(
		WindowsSetup::GetInstance()->wc_.lpszClassName,
		L"CLEYERA",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		WindowsSetup::GetInstance()->wc_.hInstance,
		nullptr
	);
	ShowWindow(WindowsSetup::GetInstance()->hwnd, SW_SHOW);



}

void WindowsSetup::WinMSG(MSG& msg)
{
	TranslateMessage(&msg);
	DispatchMessage(&msg);

}


void WindowsSetup::Deleate()
{
	CloseWindow(hwnd);


}