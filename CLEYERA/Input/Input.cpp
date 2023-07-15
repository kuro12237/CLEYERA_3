#include"Input.h"



Input::Input()
{
}

Input::~Input()
{


}

Input* Input::Instance()
{
	static Input instance;
	return &instance;


}

void Input::DirectInputObjCreate()
{
	HRESULT hr;

	hr = DirectInput8Create(
		WinApp::GetInstance()->GetWc().hInstance,
		DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&Input::Instance()->diractInput, nullptr
	);
	assert(hr);


}

void Input::KeyDeviceCreate()
{
	HRESULT hr =
		Input::Instance()->diractInput->CreateDevice(
             GUID_SysKeyboard,&Input::Instance()->InputDevice_.keybord, NULL
		);
	assert(hr);

	hr = Input::Instance()->InputDevice_.keybord->SetDataFormat(&c_dfDIKeyboard);
	assert(hr);

	hr = Input::Instance()->InputDevice_.keybord->SetCooperativeLevel(
		WinApp::GetInstance()->GetHwnd(), DISCL_FOREGROUND |
		DISCL_NONEXCLUSIVE |
		DISCL_NOWINKEY
	);
	assert(hr);

}

void Input::BeginFlame(BYTE key[256])
{

	Input::Instance()->InputDevice_.keybord->Acquire();

	Input::Instance()->InputDevice_.keybord->GetDeviceState(sizeof(key), key);

}
