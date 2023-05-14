#pragma once
#include <Windows.h>
#include <wrl.h>
#include<d3d12.h>
#include <dxgi1_6.h>

using namespace Microsoft::WRL;


class Window
{
public:
	Window(HINSTANCE hInstance, LPCWSTR winName);
	
	~Window();

	void RunMessageLoop();
	void Initialise();

private:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void initDevice();
	void initCommandQueue();


	HWND hwnd;
	HINSTANCE hInstance;
	LPCWSTR className;
	LPCWSTR windowName;
	int width, height;


	ComPtr<ID3D12Device> device;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
};

