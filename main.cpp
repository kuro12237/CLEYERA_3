#include"CLEYERA/CLEYERA.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{


	Cleyera* Cleyera_ = new Cleyera;

	//Size
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	
	
	Cleyera_->Initialize(kClientWidth,kClientHeight);


	MSG msg{};



	while (msg.message!=WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			Cleyera_->WinMSG(msg);


		}


	}

	
	return 0;


}