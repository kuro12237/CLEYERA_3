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


struct DXCProperty
{
	IDxcUtils* Utils;
	IDxcCompiler3* Compiler;

};


struct Shaders
{
	IDxcBlob* vertexBlob;
	IDxcBlob* pixelBlob;
};


class Model
{
public:
	Model();
	~Model();


	void Initialize();

	void SetDevice(ID3D12Device* device_);
	void SetCommands(Commands command);

	void dxcInitialize();

	void InitializeDfIncludeHandler();


	/// <summary>
    /// シェーダーコンパイル
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

	void CompileShaders();


private:

	ID3D12Device* device=nullptr;
	Commands commands;

	DXCProperty dxc;
	IDxcIncludeHandler* includeHandler = nullptr;
	Shaders shader;
};


