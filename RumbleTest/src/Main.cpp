#include <iostream>

#include <Windows.h>
#include <Xinput.h>

XINPUT_STATE GetControllerState(DWORD user);

int main(int argc, char* argv[]) {
	std::cout << "This program has many features.\n";

	while (true) {
		XINPUT_STATE state = GetControllerState(0);
		std::cout << "Controller state: X = " << state.Gamepad.sThumbLX << ", Y = " << state.Gamepad.sThumbLY << "\n";

		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

		vibration.wLeftMotorSpeed = (uint16_t)state.Gamepad.sThumbLX + 32768;
		vibration.wRightMotorSpeed = (uint16_t)state.Gamepad.sThumbLY + 32768;

		Sleep(25);
		XInputSetState(0, &vibration);
	}

	//dwResult = XInputGetBatteryInformation(0, )

	return 0;
}

XINPUT_STATE GetControllerState(DWORD user) {
	DWORD dwResult;
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	dwResult = XInputGetState(user, &state);

	if (dwResult != ERROR_SUCCESS) {
		// ERROR?
	}

	return state;
}