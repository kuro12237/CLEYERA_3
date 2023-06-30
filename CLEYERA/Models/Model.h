#pragma once

#include<windows.h>
#include<format>
#include<string>
#include <dxgidebug.h>
#include <dxcapi.h>
#include <d3d12.h>
#include <dxgi1_6.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")

#include<cassert>

#include"../Log/Log.h"
#include"../Setup/DX/DirectXSetup.h"

#include"../Vector/Vector4.h"
#include"../Vector/Vector3.h"

#include"../Matrix/Matrix4x4.h"
#include"../Matrix/MatrixTransform.h"

#include"../TexManager/TexManager.h"
#include"../Vector/Vector2.h"
struct PSOProperty
{
	ID3D12PipelineState* GraphicsPipelineState = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

};
struct  VertexData
{
	Vector4 position;
	Vector2 texcoord;

};


struct DXCProperty
{
	IDxcUtils* Utils;
	IDxcCompiler3* Compiler;

};

struct  Mode
{
	IDxcBlob* vertexBlob;
	IDxcBlob* pixelBlob;
};

struct Shaders
{
	Mode shape;
	Mode sprite;

};


struct  Position
{
	Vector3 top;
	Vector3 left;
	Vector3 right;

};

struct ShapeResourcePeroperty
{
	
   D3D12_VERTEX_BUFFER_VIEW BufferView;
   ID3D12Resource* Vertex;
   ID3D12Resource* Material;
   ID3D12Resource* wvpResource;
	

};

class Model : public TexManager
{
public:
	Model();
	~Model();

#pragma region 初期化
	void Initialize();

	void SetDevice(ID3D12Device* device_);
	void SetCommands(Commands command);

	void dxcInitialize();

	void InitializeDfIncludeHandler();


	/// <summary>
    /// シェーダーコンパイル関数
    /// </summary>
    /// <param name="filePath"></param>
    /// <param name="profile"></param>
    /// <param name="dxcUtils"></param>
    /// <param name="dxcCompiler"></param>
    /// <param name="includeHandler"></param>
    /// <returns></returns>
	static IDxcBlob* CompilerShader(
		const std::wstring& filePath,
		const wchar_t* profile,
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler);

	/// <summary>
	/// 実際にコンパイルする
	/// </summary>
	void CompileShaders();

	/// <summary>
	/// 色の図形のPSO生成
	/// </summary>
	void ShapeCreatePSO();

	/// <summary>
	/// 画像用のPSO
	/// </summary>
	void SpriteCreatePSO();



	/// <summary>
	/// コンパイルしたシェーダーのリリース
	/// </summary>
	void ShaderRelease();



	/// <summary>
	/// PSOなどのリリース
	/// </summary>
	void Release();


#pragma endregion

	/// <summary>
	/// 色変換
	/// </summary>
	/// <param name="color"></param>
	/// <returns></returns>
	Vector4 ColorCodeAdapter(unsigned int color);

	/// <summary>
    /// Resourceを作成
    /// </summary>
    /// <param name="device"></param>
    /// <param name="sizeInbyte"></param>
    /// <returns></returns>
	static ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInbyte);

	/// <summary>
	/// BufferViewを作成
	/// </summary>
	/// <param name="sizeInbyte"></param>
	/// <param name="Resource"></param>
	/// <returns></returns>
	static D3D12_VERTEX_BUFFER_VIEW CreateBufferView(size_t sizeInbyte, ID3D12Resource* Resource);

#pragma region 三角形


	/// <summary>
	/// Resource生成
	/// </summary>
	/// <returns></returns>
	ShapeResourcePeroperty  CreateShapeResource();

	/// <summary>
    /// Commands
    /// </summary>
    /// <param name="commands"></param>
	static void ShapeDrawCommands(
		Commands commands,
		ShapeResourcePeroperty Resource,
		PSOProperty Shape);


	/// <summary>
	/// 表示
	/// </summary>
	/// <param name="position"></param>
	/// <param name="Color"></param>
	/// <param name="Resource"></param>
	void ShapeDraw(
		Position position, unsigned int Color, 
		Matrix4x4 matrix,
		ShapeResourcePeroperty Resource);

	/// <summary>
	/// Resourceの解放処理
	/// </summary>
	/// <param name="Resource"></param>
	void ShapeResourceDeleate(ShapeResourcePeroperty Resource);

#pragma endregion

#pragma region 画像表示


	void SpriteDraw(
		Position position, unsigned int color,
		Matrix4x4 worldTransform,
		ShapeResourcePeroperty Resource,
		texResourceProperty tex);

	static void SpriteDrawCommands(ShapeResourcePeroperty Resource,texResourceProperty tex, Commands commands);

	void SpriteResourceRelease(ShapeResourcePeroperty Resource,texResourceProperty tex);
	
#pragma endregion


private:

	ID3D12Device* device=nullptr;
	Commands commands;

	DXCProperty dxc;

	IDxcIncludeHandler* includeHandler = nullptr;
	Shaders shader;

	PSOProperty Shape;
	PSOProperty Sprite;


	
};


