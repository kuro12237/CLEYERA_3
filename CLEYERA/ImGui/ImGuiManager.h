#pragma once

#include"../Setup/DX/DirectXSetup.h"
#include"../Setup/Win/WinSetup.h"
#include "/CLEYERA_3/CLEYERA/externals/imgui/imgui.h"

#include "/CLEYERA_3/CLEYERA/externals/imgui/imgui_impl_dx12.h"

#include "/CLEYERA_3/CLEYERA/externals/imgui/imgui_impl_win32.h"



class ImGuiManager
{
public:
	ImGuiManager();
	~ImGuiManager();

	static void Initialize(WindowsSetup* WinSetup_, DirectXSetup* DXSetup_);


	static void BeginFlame(DirectXSetup* DXSetup_);


	static void EndFlame(DirectXSetup* DXSetup_);

	static void Release();
private:

};
