#include <iostream>

#include <Windows.h>
#include <Xinput.h>

XINPUT_STATE GetControllerState(DWORD user);

int main(int argc, char* argv[]) {
	std::cout << "This program has many features.\n";

	while (true) {
		XINPUT_STATE state = GetControllerState(0);
		//std::cout << "Controller state: L = " << (int)state.Gamepad.bLeftTrigger << ", R = " << (int)state.Gamepad.bRightTrigger << "\n";

		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

		XINPUT_BATTERY_INFORMATION battery;
		ZeroMemory(&battery, sizeof(XINPUT_BATTERY_INFORMATION));


		XInputGetBatteryInformation(0, 0, &battery);
		//std::cout << "Battery type: " << (int)battery.BatteryType << ", Level: " << (int)battery.BatteryLevel << "\n";

		XINPUT_CAPABILITIES capabilities;
		ZeroMemory(&capabilities, sizeof(XINPUT_CAPABILITIES));

		vibration.wLeftMotorSpeed = (uint16_t)state.Gamepad.bRightTrigger * 256;
		vibration.wRightMotorSpeed = (uint16_t)state.Gamepad.bLeftTrigger * 256;

		XInputGetCapabilities(0, 0, &capabilities);
		std::cout << "Vibration: L = " << vibration.wLeftMotorSpeed << ", R = " << vibration.wRightMotorSpeed << "      \r";

		Sleep(25);
		XInputSetState(0, &vibration);
	}

	return 0;
}

XINPUT_STATE GetControllerState(DWORD user) {
	DWORD dwResult;
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(user, &state);

	if (dwResult != ERROR_SUCCESS) {
		// ERROR?
	}

	return state;
}