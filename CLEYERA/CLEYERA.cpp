#include"CLEYERA.h"

Cleyera::Cleyera()
{
}

Cleyera::~Cleyera()
{
}

void Cleyera::Initialize(const int32_t  kClientWidth, const int32_t  kClientHeight)
{

	//WinSetup = new WindowsSetup();
	//DXSetup = new DirectXSetup();
	//model = new Model();
	//texManager = new TexManager();
	//imGuimanager = new ImGuiManager();
	//WinSetupの初期化
	
	WindowsSetup::Initialize(kClientWidth, kClientHeight);
	//WinSetup->Initialize(kClientWidth, kClientHeight);

	//
	////DirectXの初期化
	//
	/*
	///ファクトリー作成
	//DXSetup->CreateDXGIFactorye();
	DirectXSetup::CreateDXGIFactorye();

	///デバイス作成
	DirectXSetup::CreateDevice();
#ifdef _DEBUG

	DirectXSetup::debugErrorInfoQueue();

#endif // _DEBUG

	///コマンドリストの生成
	DirectXSetup::CreateCommands();

	//swapChain
	DirectXSetup::CreateSwapChain(kClientWidth, kClientHeight, WindowsSetup::GetInstance()->GetHwnd());
	//rtvDescritor
	DirectXSetup::CreatertvDescritorHeap();
	//swapChainを引っ張る
	DirectXSetup::CreateSwapChainResorce();
	//RTVの設定と作成
	DirectXSetup::SettingandCreateRTV();
	//フェンスの生成
	DirectXSetup::CreateFence();

	ImGuiManager::Initialize(WindowsSetup::GetInstance(), DirectXSetup::GetInstance());

	//texManager->Initialize();

	///モデルの初期化

	//DXでつくったものを転送
	//model->SetDevice(DXSetup->GetDevice());
	//model->SetCommands(DXSetup->GetCommands());

	//DXCの初期化
	//model->dxcInitialize();
	//Compileするための対応処理
	//model->InitializeDfIncludeHandler();
	


	///シェーダーコンパイル処理
	//model->CompileShaders();

	//図形描画のパイプライン
	//model->ShapeCreatePSO();

	//描画のパイプライン
	//model->SpriteCreatePSO();

	//model->ShaderRelease();

	*/
}

/*
void Cleyera::WinMSG(MSG msg)
{
	//WinSetup->WinMSG(msg);
	WindowsSetup::WinMSG(msg);
}

void Cleyera::BeginFlame(const int32_t kClientWidth, const int32_t kClientHeight)
{
	imGuimanager->BeginFlame(DXSetup);
	DXSetup->BeginFlame();
	DXSetup->ScissorViewCommand(kClientWidth, kClientHeight);

}

void Cleyera::EndFlame()
{
	imGuimanager->EndFlame(DXSetup);
	DXSetup->EndFlame();
}

void Cleyera::Finalize()
{
	imGuimanager->Release();
	texManager->Finalize();
	DXSetup->Release();
	model->Release();
	WinSetup->Deleate();
	DXSetup->ReleaseChack();


}

texResourceProperty Cleyera::LoadTex(const std::string& filePath)
{
	texResourceProperty tex;

	tex=texManager->LoadTexture(filePath, DXSetup);
	
	return tex;
}

ResourcePeroperty Cleyera::CreateSpriteResource()
{
	ResourcePeroperty ResultResource;

	ResultResource = model->CreateSpriteResource();
	return ResultResource;
}

void Cleyera::SpriteTriangleResourceRelease(ResourcePeroperty &Resource, texResourceProperty &tex)
{

	Resource.Vertex->Release();
    Resource.Material->Release(); 
    Resource.wvpResource->Release();

    tex.Resource->Release();
	//model->SpriteResourceRelease(Resource, tex);
	//Resource;
	//tex;
}



ResourcePeroperty  Cleyera::CreateShapeResource()
{
	ResourcePeroperty resultResource;
	resultResource=model->CreateShapeResource();
	return resultResource;
}

void Cleyera::TriangleResourceRelease(ResourcePeroperty Resource)
{
	model->ShapeResourceRelease(Resource);


}

void Cleyera::TriangleDraw(Position position, unsigned int ColorCode, Matrix4x4 worldTransform, ResourcePeroperty Resource)
{
	model->ShapeDraw(position, ColorCode,worldTransform, Resource);

}

void Cleyera::SpriteTriangleDraw(Position position, unsigned int color, Matrix4x4 worldTransform, ResourcePeroperty Resource, texResourceProperty tex)
{

	model->SpriteDraw(position, color, worldTransform, Resource, tex);

}



*/