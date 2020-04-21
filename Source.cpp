#include "header.h"


char input[1000];
bool exitf = false;

void enter() {
	INPUT ino;
	ino.type = INPUT_KEYBOARD;
	ino.ki.dwFlags = KEYEVENTF_SCANCODE;
	ino.ki.wScan = MapVirtualKeyA(VK_RETURN, 0);
	ino.ki.time = 100;
	ino.ki.dwExtraInfo = 0;
	SendInput(1, &ino, sizeof(ino));

}


//Types out message and sends it
void spam(char in[1000]) {
	for (int i = 0; i < strlen(in); i++) {
		INPUT inp = { 0 };
		inp.type = INPUT_KEYBOARD;
		inp.ki.wVk = VkKeyScan(in[i]);
		SendInput(1, &inp, sizeof(inp));
		ZeroMemory(&inp, sizeof(inp));
		inp.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &inp, sizeof(inp));
	}
	enter();

}

int main() {
	std::cout << "Input text you want to spam: ";
	std::cin >> input;
	std::cout << "Starting spam" << std::endl;
	while (!exitf) {
			LPCSTR windowname = "Discord (32 bit)";
			HWND dWND = FindWindow(NULL, windowname);
			//Sets mouse position and clicks on text box
			SetCursorPos(998, 859);
			INPUT input1 = { 0 };
			input1.type = INPUT_MOUSE;
			input1.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &input1, sizeof(input1));
			ZeroMemory(&input1, sizeof(input1));
			input1.type = INPUT_MOUSE;
			input1.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			while (!exitf) {
				if (GetAsyncKeyState(VK_DOWN)) {
					exitf = true;
				}
				Sleep(500);
				spam(input);
			}
	}
	return 0;
}