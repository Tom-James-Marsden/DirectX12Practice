#include "helloTriangle.h"
#include "helperclasses.h"

helloTriangle::helloTriangle(UINT width, UINT height, std::wstring)
{
}

void helloTriangle::onInit()
{
	LoadPipeline();
	LoadAssets();
}

void helloTriangle::onUpdate()
{
}


void helloTriangle::onRender()
{
}

void helloTriangle::onDestroy()
{
}

void helloTriangle::LoadPipeline()
{
#if defined(_DEBUG)
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif

	ComPtr<IDXGIFactory4> factory;
	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&factory)));

	ComPtr<IDXGIAdapter1> hardwareAdapter;

	
	// find a hardware or software adapter that supports DirectX 12
	for (UINT i = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(i, &hardwareAdapter); ++i)
	{
		DXGI_ADAPTER_DESC1 desc;
		hardwareAdapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			// this is a software adapter
			continue;
		}

		// try to create a DirectX 12 device on this adapter
		ThrowIfFailed(D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device)));
	}

	ThrowIfFailed(D3D12CreateDevice(
		hardwareAdapter.Get(),
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&m_device)
	));


}

void helloTriangle::LoadAssets()
{
}

void helloTriangle::PopulateCommandList()
{
}

void helloTriangle::WaitForPreviousFrame()
{
}
