#include"CLEYERA/CLEYERA.h"

#define TriangleMax 3


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{


	MatrixTransform* matrixTransform = new MatrixTransform();

	//Size
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	Cleyera::Initialize(kClientWidth, kClientHeight);

#pragma region 初期化

		Triangle triangle[TriangleMax];
		//t,l,r
		triangle[0].position =
		{ {0.0f,0.0,0.0f},{-0.5f,-1.0f,0.0f},{0.5f,-1.0f,0.0f } };
		triangle[0].Resources = Cleyera::CreateShapeResource();
		triangle[0].Color = BLACK;
		triangle[0].matrix = matrixTransform->Identity();

		triangle[1].position =
		{
		{ 0.0f, 1.0f, 0.0f},
		{ -0.5f,0.0f,0.0f },
		{ 0.5f,-0.0f,0.0f} };
		triangle[1].Resources = Cleyera::CreateSpriteResource();
		triangle[1].Color = WHITE;
		triangle[1].matrix = matrixTransform->Identity();



		texResourceProperty tex;

		tex = Cleyera::LoadTex("CLEYERA/DefaultResources/uvChecker.png");

		texResourceProperty Enemytex;
		Enemytex = Cleyera::LoadTex("CLEYERA/DefaultResources/Enemy.png");

		triangle[2].position =
		{
		{ -0.5f, 1.0f, 0.0f},
		{ -1.0f,0.0f,0.0f },
		{ 0.0f,0.0f,0.0f} };
		triangle[2].Resources = Cleyera::CreateSpriteResource();
		triangle[2].Color = WHITE;
		triangle[2].matrix = matrixTransform->Identity();
#pragma endregion 

	MSG msg{};

	

	while (msg.message!=WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			Cleyera::WinMSG(msg);
		}

		Cleyera::BeginFlame(kClientWidth, kClientHeight);
#pragma region 更新処理

#pragma endregion
		
#pragma region 描画処理
		for (int i = 0; i < TriangleMax; i++)
		{
		


			Cleyera::TriangleDraw(triangle[0].position,
				triangle[0].Color, triangle[0].matrix,
				triangle[0].Resources);
	
	     }

		
		Cleyera::SpriteTriangleDraw(
			triangle[1].position,
			triangle[1].Color,
			triangle[1].matrix,
			triangle[1].Resources,
			tex

		);
		
		Cleyera::SpriteTriangleDraw(
			triangle[2].position,
			triangle[2].Color,
			triangle[2].matrix,
			triangle[2].Resources,
			Enemytex

		);
#pragma endregion
		Cleyera::EndFlame();
	}


#pragma region 頂点などの解放

	Cleyera::TriangleResourceRelease(triangle[0].Resources);
	
	Cleyera::SpriteTriangleResourceRelease(triangle[1].Resources, tex);
	Cleyera::SpriteTriangleResourceRelease(triangle[2].Resources, Enemytex);

#pragma endregion

	
	Cleyera::Finalize();
	return 0;


}
