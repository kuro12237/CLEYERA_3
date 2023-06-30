#pragma once

#include"../externals/DirectXTex/DirectXTex/d3dx12.h"
#include"../externals/DirectXTex/DirectXTex/DirectXTex.h"
#include"../Log/Log.h"
#include"../Setup/DX/DirectXSetup.h"


struct texResourceProperty
{
	D3D12_GPU_DESCRIPTOR_HANDLE SrvHandleGPU;
	ID3D12Resource* Resource;

};


class TexManager
{
public:
	TexManager();
	~TexManager();


	void Initialize();

	void Finalize();


	static DirectX::ScratchImage CreateMipImage(const std::string& filePath);

	void UploadTexData(ID3D12Resource* tex, const DirectX::ScratchImage& mipImage);



	/// <summary>
    ///	���\�[�X�̐ݒ� 
    /// </summary>
    /// <param name="metadata"></param>
    /// <returns></returns>
	static D3D12_RESOURCE_DESC SettingResource(const DirectX::TexMetadata& metadata);

	/// <summary>
	/// �q�[�v�̐ݒ�
	/// </summary>
	/// <returns></returns>
	static D3D12_HEAP_PROPERTIES SettingHeap();
	
	
	ID3D12Resource* CreateTexResource(const DirectX::TexMetadata& metadata, DirectXSetup* DXSetup_);


	/// <summary>
	/// ���ۂɎg������
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	texResourceProperty LoadTexture(const std::string& filePath, DirectXSetup* DxSetup_);



private:

	
};
