#include"CLEYERA/CLEYERA.h"

#define TriangleMax 3

struct Triangle
{
	Position position;
	ResourcePeroperty Resources;
	unsigned int Color;
	Matrix4x4 matrix;
}; 

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{


	//Cleyera* Cleyera_ = new Cleyera;

	MatrixTransform* matrixTransform = new MatrixTransform();

	//Size
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	Cleyera::Initialize(kClientWidth, kClientHeight);
	//Cleyera_->Initialize(kClientWidth, kClientHeight);


	Triangle triangle[TriangleMax];
	//t,l,r
	triangle[0].position =
	{ {0.0f,0.0,0.0f},{-0.5f,-1.0f,0.0f},{0.5f,-1.0f,0.0f } };
	//triangle[0].Resources = Cleyera_->CreateShapeResource();
	triangle[0].Color = 0xff0000ff;
	triangle[0].matrix = matrixTransform->Identity();

	triangle[1].position =
	{ 
	{ 0.0f, 1.0f, 0.0f},
	{ -0.5f,0.0f,0.0f },
	{ 0.5f,-0.0f,0.0f} };
	//triangle[1].Resources = Cleyera_->CreateSpriteResource();
	triangle[1].Color = 0xffffffff;
	triangle[1].matrix = matrixTransform->Identity();



	//texResourceProperty tex;

	//tex = Cleyera_->LoadTex("CLEYERA/DefaultResources/uvChecker.png");
	
	//texResourceProperty Enemytex;
	//Enemytex = Cleyera_->LoadTex("CLEYERA/DefaultResources/Enemy.png");

	triangle[2].position =
	{
	{ -0.5f, 1.0f, 0.0f},
	{ -1.0f,0.0f,0.0f },
	{ 0.0f,0.0f,0.0f} };
	//triangle[2].Resources = Cleyera_->CreateSpriteResource();
	triangle[2].Color = 0xffffffff;
	triangle[2].matrix = matrixTransform->Identity();


	MSG msg{};

	

	while (msg.message!=WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			Cleyera::WinMSG(msg);


		}
		Cleyera::BeginFlame(kClientWidth, kClientHeight);
		//Cleyera_->BeginFlame(kClientWidth, kClientHeight);
		
		for (int i = 0; i < TriangleMax; i++)
		{
		

/*
			Cleyera_->TriangleDraw(triangle[0].position,
				triangle[0].Color, triangle[0].matrix,
				triangle[0].Resources);
	*/
	     }

		/*
		Cleyera_->SpriteTriangleDraw(
			triangle[1].position,
			triangle[1].Color,
			triangle[1].matrix,
			triangle[1].Resources,
			tex

		);

		Cleyera_->SpriteTriangleDraw(
			triangle[2].position,
			triangle[2].Color,
			triangle[2].matrix,
			triangle[2].Resources,
			Enemytex

		);
		*/
		Cleyera::EndFlame();
	}

	///
	/// }Œ`‚Ì‰ð•úˆ—
	/// 
	/*
	Cleyera_->TriangleResourceRelease(triangle[0].Resources);


		Cleyera_->SpriteTriangleResourceRelease(triangle[1].Resources, tex);
		Cleyera_->SpriteTriangleResourceRelease(triangle[2].Resources, Enemytex);
	*/
	///
	///
	/// 
	

	//Cleyera_->Finalize();
	Cleyera::Finalize();
	return 0;


}
