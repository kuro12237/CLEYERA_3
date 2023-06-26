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

	

	//WinSetup‚Ì‰Šú‰»
	

	WinSetup->Initialize(kClientWidth, kClientHeight);

	//DirectX‚Ì‰Šú‰»
	



}

void Cleyera::WinMSG(MSG msg)
{
	WinSetup->WinMSG(msg);

}



