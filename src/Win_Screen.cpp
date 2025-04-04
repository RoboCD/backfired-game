#include "Win_Screen.h"

using namespace godot;

void WinScreen::_bind_methods() {
    // Main Menu button signal
	ADD_SIGNAL(MethodInfo("main_menu_new_game"));
}

WinScreen::WinScreen() {
	// Initialize any variables here.
}

WinScreen::~WinScreen() {
	// Add your cleanup here.
}