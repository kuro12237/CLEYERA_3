

#include"DirectXSetup.h"

DirectXSetup::DirectXSetup()
{
}

DirectXSetup::~DirectXSetup()
{
}

DirectXSetup* DirectXSetup::GetInstance()
{
	static DirectXSetup instance;
	return &instance;
}


void DirectXSetup::CreateDXGIFactorye()
{

#ifdef _DEBUG


	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&DirectXSetup::GetInstance()->debugController))))
	{

		DirectXSetup::GetInstance()->debugController->EnableDebugLayer();


		DirectXSetup::GetInstance()->debugController->SetEnableGPUBasedValidation(TRUE);

	}

#endif

	//DXGIファクトリーの生成
	DirectXSetup::GetInstance()->dxgiFactory = nullptr;
	

	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&DirectXSetup::GetInstance()->dxgiFactory));

	assert(SUCCEEDED(hr));

	//Adapter

	//いい順にアダプタを頼む
	for (UINT i = 0; DirectXSetup::GetInstance()->dxgiFactory->EnumAdapterByGpuPreference(i,
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&DirectXSetup::GetInstance()->useAdapter)) !=
		DXGI_ERROR_NOT_FOUND; i++)
	{

		DXGI_ADAPTER_DESC3 adapterDesc{};
		hr = DirectXSetup::GetInstance()->useAdapter->GetDesc3(&adapterDesc);
		assert(SUCCEEDED(hr));


		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{

			Log(ConvertString(std::format(L"Use Adapater:{}\n", adapterDesc.Description)));
			break;
		}


		DirectXSetup::GetInstance()->useAdapter = nullptr;

	}

	assert(DirectXSetup::GetInstance()->useAdapter != nullptr);





}

void DirectXSetup::CreateDevice()
{
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_12_2,D3D_FEATURE_LEVEL_12_1,D3D_FEATURE_LEVEL_12_0
	};
	const char* featureLevelStrings[] = { "12.2","12.1","12.0" };

	//高い順に生成できるか試していく
	for (size_t i = 0; i < _countof(featureLevels); i++)
	{

		HRESULT hr = D3D12CreateDevice(DirectXSetup::GetInstance()->useAdapter, featureLevels[i], IID_PPV_ARGS(&DirectXSetup::GetInstance()->device));


		if (SUCCEEDED(hr))
		{

			Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
			break;

		}
	}

	assert(DirectXSetup::GetInstance()->device != nullptr);




}

void DirectXSetup::debugErrorInfoQueue()
{
	ID3D12InfoQueue* infoQueue = nullptr;

	if (SUCCEEDED(DirectXSetup::GetInstance()->device->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		//やばいエラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);

		//エラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);

		//警告時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

		//
		//エラーと警告の抑制


		D3D12_MESSAGE_ID denyIds[] =
		{
			//windows11でのDXGIデバッグレイヤーとDX12デバッグレイヤーの相互バグによるエラーメッセージ
			//https:,,stackoverflow.com/questions/69805245/directx-12-application-is-crashing-in-windows-11

			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};

		//抑制するレベル
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter{};

		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;

		//指定したメッセージの表示を抑制する
		infoQueue->PushStorageFilter(&filter);

		//解放
		infoQueue->Release();
	}

}

void DirectXSetup::CreateCommands()
{

	///commands
    //コマンドキューの生成
	DirectXSetup::GetInstance()->commands.Queue = nullptr;
	HRESULT hr = DirectXSetup::GetInstance()->device->CreateCommandQueue(&DirectXSetup::GetInstance()->commands.QueueDesc, IID_PPV_ARGS(&DirectXSetup::GetInstance()->commands.Queue));
	assert(SUCCEEDED(hr));

	//アローケーターの生成
	DirectXSetup::GetInstance()->commands.Allocator = nullptr;
	hr = DirectXSetup::GetInstance()->device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&DirectXSetup::GetInstance()->commands.Allocator));
	assert(SUCCEEDED(hr));

	//リストの作成
	DirectXSetup::GetInstance()->commands.List = nullptr;
	hr = DirectXSetup::GetInstance()->device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
		DirectXSetup::GetInstance()->commands.Allocator, nullptr,
		IID_PPV_ARGS(&DirectXSetup::GetInstance()->commands.List));
	assert(SUCCEEDED(hr));
}

void DirectXSetup::CreateSwapChain(const int32_t Width, const int32_t Height, HWND hwnd_)
{
	DirectXSetup::GetInstance()->swapChain.swapChain = nullptr;

	//DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//スワップチェーンの設定
	DirectXSetup::GetInstance()->swapChainDesc.Width = Width;
	DirectXSetup::GetInstance()->swapChainDesc.Height = Height;
	DirectXSetup::GetInstance()->swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	DirectXSetup::GetInstance()->swapChainDesc.SampleDesc.Count = 1;
	DirectXSetup::GetInstance()->swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	DirectXSetup::GetInstance()->swapChainDesc.BufferCount = 2;
	DirectXSetup::GetInstance()->swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;


	//スワップチェーンの生成
	HRESULT hr = DirectXSetup::GetInstance()->dxgiFactory->CreateSwapChainForHwnd(DirectXSetup::GetInstance()->commands.Queue, hwnd_, &DirectXSetup::GetInstance()->swapChainDesc,
		nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(&DirectXSetup::GetInstance()->swapChain.swapChain));

	assert(SUCCEEDED(hr));
}

ID3D12DescriptorHeap* DirectXSetup::CreateDescriptorHeap( D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible)
{
	ID3D12DescriptorHeap* descriptHeap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
	descriptorHeapDesc.Type = heapType;
	descriptorHeapDesc.NumDescriptors = numDescriptors;
	descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	HRESULT hr = DirectXSetup::GetInstance()->device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptHeap));
	assert(SUCCEEDED(hr));
	return descriptHeap;

}

void DirectXSetup::CreatertvDescritorHeap()
{
	
	DirectXSetup::GetInstance()->rtv.DescritorHeap = CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 2, false);
	DirectXSetup::GetInstance()->srvDescriptorHeap = CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 128, true);



}

void DirectXSetup::CreateSwapChainResorce()
{
	HRESULT hr = DirectXSetup::GetInstance()->swapChain.swapChain->GetBuffer(0, IID_PPV_ARGS(&DirectXSetup::GetInstance()->swapChain.Resource[0]));


	assert(SUCCEEDED(hr));

	hr = DirectXSetup::GetInstance()->swapChain.swapChain->GetBuffer(1, IID_PPV_ARGS(&DirectXSetup::GetInstance()->swapChain.Resource[1]));

	assert(SUCCEEDED(hr));
}

void DirectXSetup::SettingandCreateRTV()
{

	DirectXSetup::GetInstance()->rtv.rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	DirectXSetup::GetInstance()->rtv.rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	DirectXSetup::GetInstance()->rtv.rtvStartHandle = DirectXSetup::GetInstance()->rtv.DescritorHeap->GetCPUDescriptorHandleForHeapStart();

	DirectXSetup::GetInstance()->rtv.rtvHandles[0] = DirectXSetup::GetInstance()->rtv.rtvStartHandle;
	DirectXSetup::GetInstance()->device->CreateRenderTargetView(DirectXSetup::GetInstance()->swapChain.Resource[0], &DirectXSetup::GetInstance()->rtv.rtvDesc,
		DirectXSetup::GetInstance()->rtv.rtvHandles[0]);


	DirectXSetup::GetInstance()->rtv.rtvHandles[1].ptr = DirectXSetup::GetInstance()->rtv.rtvHandles[0].ptr + DirectXSetup::GetInstance()->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	DirectXSetup::GetInstance()->device->CreateRenderTargetView(DirectXSetup::GetInstance()->swapChain.Resource[1], &DirectXSetup::GetInstance()->rtv.rtvDesc, DirectXSetup::GetInstance()->rtv.rtvHandles[1]);


}

void DirectXSetup::CreateFence()
{
	//フェンスの作成
	DirectXSetup::GetInstance()->fence = nullptr;
	DirectXSetup::GetInstance()->fenceValue = 0;
	HRESULT hr = DirectXSetup::GetInstance()->device->CreateFence(DirectXSetup::GetInstance()->fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&DirectXSetup::GetInstance()->fence));
	assert(SUCCEEDED(hr));


	DirectXSetup::GetInstance()->fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(DirectXSetup::GetInstance()->fenceEvent != nullptr);


}




void DirectXSetup::BeginFlame()
{
	//書き込むスワップチェーンのindexをとる
	UINT backBufferIndex = DirectXSetup::GetInstance()->swapChain.swapChain->GetCurrentBackBufferIndex();

	//バリア
	DirectXSetup::GetInstance()->barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	DirectXSetup::GetInstance()->barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	DirectXSetup::GetInstance()->barrier.Transition.pResource = DirectXSetup::GetInstance()->swapChain.Resource[backBufferIndex];
	DirectXSetup::GetInstance()->barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	DirectXSetup::GetInstance()->barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	DirectXSetup::GetInstance()->commands.List->ResourceBarrier(1, &DirectXSetup::GetInstance()->barrier);

	//描画先のRTYを設定
	DirectXSetup::GetInstance()->commands.List->OMSetRenderTargets(1, &DirectXSetup::GetInstance()->rtv.rtvHandles[backBufferIndex], false, nullptr);

	float clearColor[] = { 0.1f,0.25f,0.5f,1.0f };
	//float clearColor[] = { 1.0f,0.0f,0.0f,1.0f };
	DirectXSetup::GetInstance()->commands.List->ClearRenderTargetView(DirectXSetup::GetInstance()->rtv.rtvHandles[backBufferIndex], clearColor, 0, nullptr);

}

void DirectXSetup::EndFlame()
{

	DirectXSetup::GetInstance()->barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	DirectXSetup::GetInstance()->barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

	DirectXSetup::GetInstance()->commands.List->ResourceBarrier(1, &DirectXSetup::GetInstance()->barrier);
	HRESULT hr = DirectXSetup::GetInstance()->commands.List->Close();
	assert(SUCCEEDED(hr));


	ID3D12CommandList* commandLists[] = { DirectXSetup::GetInstance()->commands.List };

	DirectXSetup::GetInstance()->commands.Queue->ExecuteCommandLists(1, commandLists);
	DirectXSetup::GetInstance()->swapChain.swapChain->Present(0, 1);


	//Fence数値加算
	DirectXSetup::GetInstance()->fenceValue++;

	//GPUにシグナル
	DirectXSetup::GetInstance()->commands.Queue->Signal(DirectXSetup::GetInstance()->fence, DirectXSetup::GetInstance()->fenceValue);


	if (DirectXSetup::GetInstance()->fence->GetCompletedValue() < DirectXSetup::GetInstance()->fenceValue)
	{

		DirectXSetup::GetInstance()->fence->SetEventOnCompletion(DirectXSetup::GetInstance()->fenceValue, DirectXSetup::GetInstance()->fenceEvent);


		WaitForSingleObject(DirectXSetup::GetInstance()->fenceEvent, INFINITE);

	}

	DirectXSetup::GetInstance()->swapChain.swapChain->Present(1, 0);


	hr = DirectXSetup::GetInstance()->commands.Allocator->Reset();
	assert(SUCCEEDED(hr));

	hr = DirectXSetup::GetInstance()->commands.List->Reset(DirectXSetup::GetInstance()->commands.Allocator, nullptr);
	assert(SUCCEEDED(hr));

}

void DirectXSetup::ScissorViewCommand(const int32_t kClientWidth, const int32_t kClientHeight)
{
	D3D12_VIEWPORT viewport{};

	viewport = viewportSetting(kClientWidth, kClientHeight);

	//シザー矩形
	D3D12_RECT scissorRect{};
	scissorRect = scissorRectSetting(kClientWidth, kClientHeight);

	//コマンドを積む
	DirectXSetup::GetInstance()->commands.List->RSSetViewports(1, &viewport); //
	DirectXSetup::GetInstance()->commands.List->RSSetScissorRects(1, &scissorRect);

}


void DirectXSetup::FeanceReleace(ID3D12Fence* fence, HANDLE fenceEvent)
{
	CloseHandle(fenceEvent);
	fence->Release();
}

void DirectXSetup::DescripterRelease(RTV rtv, ID3D12DescriptorHeap* srvDescriptorHeap)
{

	rtv.DescritorHeap->Release();
	srvDescriptorHeap->Release();
}

void DirectXSetup::SwapChainRelease(SwapChain swapChain)
{
	swapChain.Resource[0]->Release();
	swapChain.Resource[1]->Release();
	swapChain.swapChain->Release();

}

void DirectXSetup::CommandsRelease(Commands commands)
{
	commands.List->Release();
	commands.Allocator->Release();
	commands.Queue->Release();
}

void DirectXSetup::Release()
{
	FeanceReleace(DirectXSetup::GetInstance()->fence, DirectXSetup::GetInstance()->fenceEvent);
	DescripterRelease(DirectXSetup::GetInstance()->rtv, DirectXSetup::GetInstance()->srvDescriptorHeap);
	SwapChainRelease(DirectXSetup::GetInstance()->swapChain);
	CommandsRelease(DirectXSetup::GetInstance()->commands);
	DirectXSetup::GetInstance()->device->Release();
	DirectXSetup::GetInstance()->useAdapter->Release();
	DirectXSetup::GetInstance()->dxgiFactory->Release();

	DirectXSetup::GetInstance()->debugController->Release();
}

void DirectXSetup::ReleaseChack()
{
	IDXGIDebug1* debug;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug))))
	{
		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		debug->Release();
	}


}

D3D12_VIEWPORT DirectXSetup::viewportSetting(int32_t kClientWidth, int32_t kClientHeight)
{

	D3D12_VIEWPORT viewport;

	//クライアント領域のサイズを一緒にして画面全体に表示
	viewport.Width = float(kClientWidth);
	viewport.Height = float(kClientHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;



	return viewport;
}

D3D12_RECT DirectXSetup::scissorRectSetting(int32_t kClientWidth, int32_t kClientHeight)
{
	//シザー矩形
	D3D12_RECT scissorRect{};

	//基本的にビューポートと同じ矩形が構成されるようにする
	scissorRect.left = 0;
	scissorRect.right = kClientWidth;
	scissorRect.top = 0;
	scissorRect.bottom = kClientHeight;


	return scissorRect;

}
