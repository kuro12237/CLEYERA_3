#include"CLEYERA.h"

Cleyera::Cleyera()
{
}

Cleyera::~Cleyera()
{
}

void Cleyera::Initialize(const int32_t  kClientWidth, const int32_t  kClientHeight)
{

	
	//WinSetupの初期化
	
	WindowsSetup::Initialize(kClientWidth, kClientHeight);


	//
	////DirectXの初期化
	//
	
	///ファクトリー作成
	
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

	TexManager::Initialize();

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

	
}


void Cleyera::WinMSG(MSG msg)
{
	
	WindowsSetup::WinMSG(msg);
}

void Cleyera::BeginFlame(const int32_t kClientWidth, const int32_t kClientHeight)
{
	ImGuiManager::BeginFlame(DirectXSetup::GetInstance());
	DirectXSetup::BeginFlame();
	DirectXSetup::ScissorViewCommand(kClientWidth, kClientHeight);

}

void Cleyera::EndFlame()
{
	ImGuiManager::EndFlame(DirectXSetup::GetInstance());
	DirectXSetup::EndFlame();
}


void Cleyera::Finalize()
{
	ImGuiManager::Release();
	TexManager::Finalize();
	DirectXSetup::Release();
	//model->Release();
	WindowsSetup::Deleate();
	DirectXSetup::ReleaseChack();


}

texResourceProperty Cleyera::LoadTex(const std::string& filePath)
{
	texResourceProperty tex;

	tex = TexManager::LoadTexture(filePath, DirectXSetup::GetInstance());

	return tex;
}
/*
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