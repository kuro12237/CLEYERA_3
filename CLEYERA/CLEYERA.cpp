#include"CLEYERA.h"

Cleyera::Cleyera()
{
}

Cleyera::~Cleyera()
{
}

void Cleyera::Initialize(const int32_t  kClientWidth, const int32_t  kClientHeight)
{

	WinSetup = new WindowsSetup();

	

	//WinSetupの初期化
	

	WinSetup->Initialize(kClientWidth, kClientHeight);

	//DirectXの初期化
	



}

void Cleyera::WinMSG(MSG msg)
{
	WinSetup->WinMSG(msg);

}



