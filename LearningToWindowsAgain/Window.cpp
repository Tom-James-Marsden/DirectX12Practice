#include "Window.h"
#include <iostream>
#include <fstream>

Window::Window(HINSTANCE hInstance, LPCWSTR winName) :
	hInstance(hInstance), height(600), width(800)
{

	className = L"MyWindowClass";
	windowName = winName;

	//Initialising window class
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	wc.hIconSm = NULL;
	RegisterClassEx(&wc);

	//Creating the window
	hwnd = CreateWindowEx(0, className, windowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_SHOW);
}

Window::~Window()
{
	DestroyWindow(hwnd);
	UnregisterClass(className, hInstance);
}

void Window::RunMessageLoop()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::Initialise()
{
	initDevice();
	initCommandQueue();
}

LRESULT Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void Window::initDevice()
{
	ComPtr<IDXGIFactory6> factory;
	ComPtr<IDXGIAdapter1> adapter;

	std::wofstream MyFile("TEST.txt");

	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));

	if (SUCCEEDED(hr))
	{
		// find a hardware or software adapter that supports DirectX 12
		for (UINT i = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(i, &adapter); ++i)
		{
			DXGI_ADAPTER_DESC1 desc;
			adapter->GetDesc1(&desc);

			MyFile << desc.Description;

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				// this is a software adapter
				continue;
			}

			// try to create a DirectX 12 device on this adapter
			hr = D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

			if (SUCCEEDED(hr))
			{
				// we found a device, so break out of the loop
				break;
			}
			else {
				MessageBox(hwnd, L"Could not create device, FATAL", NULL, MB_OKCANCEL);
			}
		}
	}

	MyFile.close();

}

void Window::initCommandQueue()
{
	D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;

	HRESULT hr = device->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue));

	if(FAILED(hr)){
		MessageBox(hwnd, L"Could not create command queue FATAL", NULL, MB_OKCANCEL);
	}

	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));

	if (FAILED(hr)) {
		MessageBox(hwnd, L"Could not create command allocator FATAL", NULL, MB_OKCANCEL);
	}

	hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList));

	if (FAILED(hr)) {
		MessageBox(hwnd, L"Could not create command allocator FATAL", NULL, MB_OKCANCEL);
	}

}
