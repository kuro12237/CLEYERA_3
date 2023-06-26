#pragma once
#include<format>
#include"Setup/Win/WinSetup.h"


class Cleyera
{
public:
	Cleyera();
	~Cleyera();


	void Initialize(const int32_t  kClientWidth, const int32_t  kClientHeight);



#pragma region ループする必要がある処理


	/// <summary>
	/// メッセージをWinSetupに転送
	/// </summary>
	/// <param name="msg"></param>
	void WinMSG(MSG msg);



#pragma endregion


private:


	WindowsSetup* WinSetup = nullptr;


};

