#include"CLEYERA/CLEYERA.h"

#define TriangleMax 2

struct Triangle
{
	Position position;
	ShapeResourcePeroperty Resources;
	unsigned int Color;
	Matrix4x4 matrix;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{


	Cleyera* Cleyera_ = new Cleyera;

	MatrixTransform* matrixTransform = new MatrixTransform();

	//Size
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	
	
	Cleyera_->Initialize(kClientWidth,kClientHeight);

	Triangle triangle[TriangleMax];
	triangle[0].position =
	{ {0.0f,0.5,0.0f},{-0.5f,0.0f,0.0f},{0.5f,0.0f,0.0f } };
	triangle[0].Resources = Cleyera_->CreateResource();
	triangle[0].Color = 0xff0000ff;
	triangle[0].matrix = matrixTransform->Identity();
	
	triangle[1].position =
	{ {-0.5f,0.5,0.0f},{-1.0f,0.0f,0.0f},{0.0f,0.0f,0.0f } };
	triangle[1].Resources = Cleyera_->CreateResource();
	triangle[1].Color = 0xff0000ff;
	triangle[1].matrix = matrixTransform->Identity();



	texResourceProperty tex;

	tex = Cleyera_->LoadTex("CLEYERA/DefaultResources/uvChecker.png");

	MSG msg{};

	

	while (msg.message!=WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			Cleyera_->WinMSG(msg);


		}

		Cleyera_->BeginFlame(kClientWidth, kClientHeight);
		
		for (int i = 0; i < TriangleMax; i++)
		{
		


			Cleyera_->TriangleDraw(triangle[i].position,
				triangle[i].Color, triangle[i].matrix,
				triangle[i].Resources);
		}

		Cleyera_->EndFlame();
	}

	///
	/// �}�`�̉������
	/// 
	
	for (int i = 0; i < TriangleMax; i++)
	{
		Cleyera_->TriangleResourceRelease(triangle[i].Resources);
	}
	///
	///
	/// 
	

	Cleyera_->Deleate();

	return 0;


}