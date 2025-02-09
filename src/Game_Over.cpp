#include "Game_Over.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include <gdextension_interface.h>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/label.hpp>

using namespace godot;

void GameOver::_bind_methods() {
    // Start button signal
	ADD_SIGNAL(MethodInfo("pressed_restart"));
}

GameOver::GameOver() {
	// Initialize any variables here.
}

GameOver::~GameOver() {
	// Add your cleanup here.
}

void GameOver::_ready(){
    set_visible(false);
    restart_button = get_node<Button>("RestartButton");
    pressed_once = false;
    message = "GAME OVER";
}

void GameOver::_process(double delta) {
    if ((restart_button->is_pressed()) && pressed_once != true){
        pressed_once = true;
        UtilityFunctions::print("Restart Button emit");
        emit_signal("pressed_restart");
    }
}

void GameOver::on_restart_button_pressed(){
    UtilityFunctions::print("Restart Button Pressed!");
    SceneTree* scene_tree = get_tree();
    levelScene = ResourceLoader::get_singleton()->load("res://level-1.tscn");
    scene_tree->change_scene_to_packed(levelScene);
}

void GameOver::set_message(String p_message){
    message = p_message;
    get_node<Label>("Message")->set_text(message);
}

void GameOver::set_deaths(int deaths){

    Label* death_label = get_node<Label>("Deaths");
    death_label->set_text(String("Deaths: " +String::num(deaths)));
    death_label->show();
}