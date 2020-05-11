#include "header.h"
char input[1000];
bool exitf = false;
POINT txb = { 998, 859 };
char out[17] = { ':', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '"', '~', '<', '>' };
//Sets the mouse position
void setMouse() {
	LPCSTR windowname = "Discord (32 bit)";
	HWND dWND = FindWindow(NULL, windowname);
	HDC wdc = GetDC(dWND);
	SetCursorPos(txb.x, txb.y);
	INPUT input1 = { 0 };
	input1.type = INPUT_MOUSE;
	input1.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input1, sizeof(input1));
	ZeroMemory(&input1, sizeof(input1));
	input1.type = INPUT_MOUSE;
	input1.mi.dwFlags = MOUSEEVENTF_LEFTUP;
}
//Presses enter
void enter() {
	INPUT ino;
	ino.type = INPUT_KEYBOARD;
	ino.ki.dwFlags = KEYEVENTF_SCANCODE;
	ino.ki.wScan = MapVirtualKeyA(VK_RETURN, 0);
	ino.ki.time = 100;
	ino.ki.dwExtraInfo = 0;
	SendInput(1, &ino, sizeof(ino));

}
//Releases shift
void shiftR() {
	INPUT op;
	op.type = INPUT_KEYBOARD;
	op.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	op.ki.wScan = MapVirtualKey(VK_LSHIFT, 0);
	op.ki.time = 0;
	SendInput(1, &op, sizeof(op));
}
//Presses down on shift
void shift() {
	INPUT op;
	op.type = INPUT_KEYBOARD;
	op.ki.dwFlags = KEYEVENTF_SCANCODE;
	op.ki.wScan = MapVirtualKey(VK_LSHIFT, 0);
	op.ki.time = 0;
	SendInput(1, &op, sizeof(op));
	op.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &op, sizeof(op));
}

//Types out message and sends it
void spam(char in[1000]) {
	
	for (int i = 0; i < strlen(in); i++) {
		//Looking for caps and outlier characters
		for (int j = 0; j < strlen(out); j++) {
			if (in[i] == out[j] || isupper(in[i])) {
				shift();
			}
		}
		//Sending the input
		INPUT inp = { 0 };
		inp.type = INPUT_KEYBOARD;
		auto vkvalue = VkKeyScan(in[i]);
		inp.ki.wVk = VkKeyScan(in[i]);
		SendInput(1, &inp, sizeof(inp));
		ZeroMemory(&inp, sizeof(inp));
		inp.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &inp, sizeof(inp));
		shiftR();
	}
	
	enter();

}
//Sets cursor position
void setTxb() {
	std::cout << "Move cursor to textbox?Y/N";
	std::cin.getline(input, 10);
	if (input[0] == 'y' || input[0] == 'Y') {
		LPCSTR windowname1 = "Discord (32 bit)";
		HWND win = FindWindow(NULL, windowname1);
		HDC dci = GetDC(win);
		GetCursorPos(&txb);
		ScreenToClient(win, &txb);
		std::cout << "X: " << txb.x << "Y:" << txb.y << std::endl;
		ReleaseDC(win, dci);
	}
}
//Spamming thread
void spamit() {
	while (!exitf) {
		setMouse();
		spam(input);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
int main() {
	setTxb();
	std::cin.sync();
	std::cout << "Input text you want to spam: ";
	std::cin.getline(input, 1000);
	std::cin.sync();
	std::cout << input << std::endl;
	std::cout << "Starting spam" << std::endl;
	std::thread spammer(spamit);
	while (!exitf) {
		if (GetAsyncKeyState(VK_DOWN)) {
				exitf = true;
		}
		
		
			
	}
	spammer.join();
	return 0;
}