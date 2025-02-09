#include "Main.h"
#include "Main_Menu.h"
#include "Game_Over.h"
#include "Player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include <gdextension_interface.h>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/area2d.hpp>

using namespace godot;

void Main::_bind_methods() {
    ClassDB::bind_method(D_METHOD("start_game"), &Main::start_game);
    ClassDB::bind_method(D_METHOD("game_over", "p_node"), &Main::game_over);
    ClassDB::bind_method(D_METHOD("restart_game"), &Main::restart_game);
    ClassDB::bind_method(D_METHOD("game_won", "p_node"), &Main::game_won);
}

Main::Main() {
	// Initialize any variables here.
}

Main::~Main() {
	// Add your cleanup here.
}

void Main::_ready(){
    UtilityFunctions::print("Main start");

    MainMenu* main_menu = get_node<MainMenu>("MainMenu");
    UtilityFunctions::print("Got main menu");
    main_menu->set_process(true);
    Error error = main_menu->connect("pressed_start", Callable(this, "start_game"));
    UtilityFunctions::print("main menu signal connect");
    if (error != OK) {
       UtilityFunctions::print(String("Failed to connect signal: ") + error);
    }
    UtilityFunctions::print("Main node started");

}

void Main::_process(double delta) {
    SceneTree* scene_tree = get_tree();

    Node * curr_scene = scene_tree->get_current_scene();

    Node* level_1_scene = get_node_or_null(NodePath(String("Level-1_"+String::num(numTries))));

    if (level_1_scene == nullptr){
        return;
    }
    if (signals_connected == false)
    {
        UtilityFunctions::print("main connect signals");
        Player * player = level_1_scene->get_node<Player>("Player");

        Error error = player->connect("player_died", Callable(this, "game_over"));
        UtilityFunctions::print("main player signal connect");
        if (error != OK) {
            UtilityFunctions::print(String("Failed to connect signal: ") + error);
        }
        else{
            signals_connected = true;
        }
        GameOver * game_over_node = player->get_node<GameOver>("GameOver");
        Error error_go = game_over_node->connect("pressed_restart", Callable(this, "restart_game"));
        UtilityFunctions::print("game over node signal connect");
        if (error_go != OK) {
            UtilityFunctions::print(String("Failed to connect signal: ") + error);
        }
        else{
            signals_connected = true;
        }

        Area2D * exit_area = level_1_scene->get_node<Area2D>("Exit");
        Error error_exit = exit_area->connect("body_entered", Callable(this, "game_won"));
        UtilityFunctions::print("game won node signal connect");
        if (error_exit != OK) {
            UtilityFunctions::print(String("Failed to connect exit area signal: ") + error);
        }
        else{
            signals_connected = true;
        }
    }
}

void Main::start_game(){
    UtilityFunctions::print("Start Game Pressed!");
    SceneTree* scene_tree = get_tree();
    Node * curr_scene = scene_tree->get_current_scene();

    Ref<PackedScene> level1Scene = ResourceLoader::get_singleton()->load("res://level-1.tscn");

    Node* level_1_inst = level1Scene->instantiate();
    CanvasLayer* level_1_node = level_1_inst->get_node<CanvasLayer>(".");
    level_1_node->set_name("Level-1_"+String::num(numTries));
    curr_scene->add_child(level_1_node);
    MainMenu* main_menu = curr_scene->get_node<MainMenu>("MainMenu");
    main_menu->hide();
}

void Main::game_over(Node* p_node){
    UtilityFunctions::print("Game Over!");
    p_node->get_node<GameOver>("GameOver")->show();
}

void Main::restart_game(){
    SceneTree* scene_tree = get_tree();
    Node * curr_scene = scene_tree->get_current_scene();

    CanvasLayer* level_1_node = curr_scene->get_node<CanvasLayer>("Level-1_"+String::num(numTries));
    level_1_node->get_node<Player>("Player")->get_node<GameOver>("GameOver")->hide();
    level_1_node->queue_free();
    signals_connected = false;
    numTries++;

    start_game();
}

void Main::game_won(Node* p_node){
    String node_name = p_node->get_name();
    UtilityFunctions::print("Node ", node_name, " entered exit area");
    if (node_name != "Player"){
        return;
    }
    UtilityFunctions::print("You Won!");
    SceneTree* scene_tree = get_tree();
    Node * curr_scene = scene_tree->get_current_scene();
    CanvasLayer* level_1_node = curr_scene->get_node<CanvasLayer>("Level-1_"+String::num(numTries));
    Player* player_node = level_1_node->get_node<Player>("Player");
    GameOver* end_screen = player_node->get_node<GameOver>("GameOver");

    // Change message
    end_screen->set_message("You Escaped!");
    end_screen->set_deaths(numTries);
    end_screen->get_node<Button>("RestartButton")->hide();
    end_screen->show();
    player_node->set_velocity(Vector2(0,0));
    player_node->set_dead(true);
}
