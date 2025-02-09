#include "Main_Menu.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include <gdextension_interface.h>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

void MainMenu::_bind_methods() {
    // Start button signal
	ADD_SIGNAL(MethodInfo("pressed_start"));
}

MainMenu::MainMenu() {
	// Initialize any variables here.
}

MainMenu::~MainMenu() {
	// Add your cleanup here.
}

void MainMenu::_ready(){

    start_button = get_node<Button>("StartButton");

    UtilityFunctions::print("Main Menu Start");
}

void MainMenu::_process(double delta) {
    if (start_button->is_pressed()){
        UtilityFunctions::print("Start Button emit");
        emit_signal("pressed_start");
    }
}
