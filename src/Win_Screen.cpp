#include "Win_Screen.h"
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

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

void WinScreen::_ready(){
    set_visible(false);
    main_menu_button = get_node<Button>("MainButton");
    pressed_once = false;
}

void WinScreen::_process(double delta) {
    if ((main_menu_button->is_pressed()) && pressed_once != true){
        pressed_once = true;
        UtilityFunctions::print("Main Menu Button emit");
        emit_signal("main_menu_new_game");
    }
}

void WinScreen::set_deaths(int deaths){
    Label* death_label = get_node<Label>("Deaths");
    death_label->set_text(String("Deaths: " +String::num(deaths)));
    death_label->show();
}

void WinScreen::on_main_menu_button_pressed(){
    UtilityFunctions::print("Main Menu Button Pressed!");
    SceneTree* scene_tree = get_tree();
    mainMenuScene = ResourceLoader::get_singleton()->load("res://main_menu.tscn");
    scene_tree->change_scene_to_packed(mainMenuScene);
}
