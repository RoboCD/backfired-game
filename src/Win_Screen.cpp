#include "Win_Screen.h"

using namespace godot;

void WinScreen::_bind_methods() {
    // Start button signal
	ADD_SIGNAL(MethodInfo("pressed_restart"));
}

WinScreen::WinScreen() {
	// Initialize any variables here.
}

WinScreen::~WinScreen() {
	// Add your cleanup here.
}