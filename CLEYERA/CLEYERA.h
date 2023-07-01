#pragma once
#include<format>
#include"Setup/Win/WinSetup.h"
#include"Setup/DX/DirectXSetup.h"

#include"Models/Model.h"
#include"TexManager/TexManager.h"

#include"ImGui/ImGuiManager.h"
class Cleyera
{
public:
	Cleyera();
	~Cleyera();


	 static void Initialize(const int32_t  kClientWidth, const int32_t  kClientHeight);

	static void Finalize();
#pragma region ループする必要がある処理


	/// <summary>
	/// メッセージをWinSetupに転送
	/// </summary>
	/// <param name="msg"></param>
	static void WinMSG(MSG msg);


	static void BeginFlame(const int32_t  kClientWidth, const int32_t  kClientHeight);

	static void EndFlame();
		  
	
#pragma region テクスチャー

	/// <summary>
	/// テクスチャの読み込み
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	texResourceProperty LoadTex(const std::string& filePath);




#pragma endregion


#pragma region 三角形

	/// <summary>
	/// 頂点を作る
	/// </summary>
	/// <param name="Resource"></param>
	ResourcePeroperty CreateShapeResource();

	/// <summary>
	/// 三角形のResourceの解放
	/// </summary>
	void TriangleResourceRelease(
		ResourcePeroperty Resource);

	/// <summary>
	/// 三角形の表示
	/// </summary>
	/// <param name="position"></param>
	/// <param name="Color"></param>
	/// <param name="worldTransform"></param>
	/// <param name="Resource"></param>
	void TriangleDraw(
		Position position,unsigned int Color,
		Matrix4x4 worldTransform,
		ResourcePeroperty Resource);


	/// <summary>
	/// テクスチャ描画のResourceの作成
	/// </summary>
	/// <returns></returns>
	ResourcePeroperty CreateSpriteResource();

	/// <summary>
	/// 三角形の表示(テクスチャ)
	/// </summary>
	/// <param name=""></param>
	/// <param name="color"></param>
	/// <param name="worldTransform"></param>
	/// <param name="Resource"></param>
	/// <param name="tex"></param>
	void SpriteTriangleDraw(
		Position position, unsigned int color,
		Matrix4x4 worldTransform,
		ResourcePeroperty Resource,
		texResourceProperty tex
	);
	/// <summary>
    /// リソースの解放
    /// </summary>
    /// <param name="Resource"></param>
    /// <param name="tex"></param>
	void SpriteTriangleResourceRelease(
		ResourcePeroperty& Resource,
		texResourceProperty& tex
	);

#pragma endregion

#pragma region 四角形




#pragma endregion


#pragma endregion


private:


	WindowsSetup* WinSetup = nullptr;
	DirectXSetup* DXSetup = nullptr;
	Model* model = nullptr;
	ImGuiManager* imGuimanager = nullptr;
	TexManager* texManager = nullptr;


};

