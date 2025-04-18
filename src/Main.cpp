#include "Main.h"

#include "Main_Menu.h"
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
    ClassDB::bind_method(D_METHOD("main_menu"), &Main::main_menu);
    ClassDB::bind_method(D_METHOD("incrementEnemiesKilled"), &Main::incrementEnemiesKilled);
}


Main::Main():
    numDeaths(0),
    numGames(0),
    numEnemiesKilled(0),
    level1NodeName("Level-1_"+String::num(numGames)+"_"+String::num(numDeaths)) {
	// Initialize any variables here.
    game_over_screen = ResourceLoader::get_singleton()->load("res://game_over.tscn");
	win_screen = ResourceLoader::get_singleton()->load("res://win_screen.tscn");

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

    Node* level_1_scene = get_node_or_null(NodePath(level1NodeName));

    if (level_1_scene == nullptr){
        return;
    }
    Player * player = level_1_scene->get_node<Player>("Player");
    if (start_signals_connected == false)
    {
        UtilityFunctions::print("start signals connect");

        Error error = player->connect("player_died", Callable(this, "game_over"));
        UtilityFunctions::print("main player signal connect");
        if (error != OK) {
            UtilityFunctions::print(String("Failed to connect signal: ") + error);
        }
        else{
            start_signals_connected = true;
        }
        Area2D * exit_area = level_1_scene->get_node<Area2D>("Exit");
        Error error_exit = exit_area->connect("body_entered", Callable(this, "game_won"));
        UtilityFunctions::print("game won node signal connect");
        if (error_exit != OK) {
            UtilityFunctions::print(String("Failed to connect exit area signal: ") + error_exit);
        }
        else{
            start_signals_connected = true;
        }
        // Enemies death signal
        TypedArray<Node> enemies = level_1_scene->get_children();
        for (int i = 0; i < enemies.size(); i++){
            Node* enemy = Object::cast_to<Node>(enemies[i]);
            if (enemy && enemy->has_signal("enemy_hit")){
                UtilityFunctions::print(String("Enemy hit signal connect: ") + String::num(i));
                enemy->connect("enemy_hit", Callable(this,"incrementEnemiesKilled"));
            }
        }
    }
    if (curr_scene->has_node("./GameOver") && game_over_signal_connect == false){

        GameOver * game_over_node = curr_scene->get_node<GameOver>("GameOver");
        Error error_go = game_over_node->connect("pressed_restart", Callable(this, "restart_game"));
        UtilityFunctions::print("game over node signal connect");
        if (error_go != OK) {
            UtilityFunctions::print(String("Failed to connect signal: ") + error_go);
        }
        else{
            game_over_signal_connect = true;
        }
    }
    if (curr_scene->has_node("./WinScreen") && win_screen_signal_connect == false){

        WinScreen * win_screen_node = curr_scene->get_node<WinScreen>("WinScreen");
        Error error_win = win_screen_node->connect("main_menu_new_game", Callable(this, "main_menu"));
        UtilityFunctions::print("main menu new game signal connect");
        if (error_win != OK) {
            UtilityFunctions::print(String("Failed to connect signal: ") + error_win);
        }
        else{
            win_screen_signal_connect = true;
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
    level1NodeName = "Level-1_"+String::num(numGames)+"_"+String::num(numDeaths);
    level_1_node->set_name(level1NodeName);
    curr_scene->add_child(level_1_node);
    MainMenu* main_menu = curr_scene->get_node<MainMenu>("MainMenu");
    main_menu->hide();
}

void Main::game_over(Node* p_node){
    UtilityFunctions::print("Game Over!");
	Node* game_over_instance = game_over_screen->instantiate();
    SceneTree* scene_tree = get_tree();

    GameOver* game_over_node = game_over_instance->get_node<GameOver>(".");

    scene_tree->get_current_scene()->add_child(game_over_instance);
    game_over_node->show();

    // p_node->get_node<GameOver>("GameOver")->show();
}

void Main::restart_game(){
    UtilityFunctions::print("Restart Game");
    SceneTree* scene_tree = get_tree();
    Node * curr_scene = scene_tree->get_current_scene();

    CanvasLayer* level_1_node = curr_scene->get_node<CanvasLayer>(level1NodeName);
    level_1_node->queue_free();
    curr_scene->get_node<GameOver>("GameOver")->queue_free();
    start_signals_connected = false;
    game_over_signal_connect = false;
    numDeaths++;

    start_game();
}

void Main::game_won(Node* p_node){
    String node_name = p_node->get_name();
    UtilityFunctions::print("Node ", node_name, " entered exit area");
    if (node_name != "Player"){
        return;
    }
    Player *player_node = Object::cast_to<Player>(p_node);

    UtilityFunctions::print("You Won!");
    Node* win_screen_instance = win_screen->instantiate();
    SceneTree* scene_tree = get_tree();

    WinScreen* win_screen_node = win_screen_instance->get_node<WinScreen>(".");

    scene_tree->get_current_scene()->add_child(win_screen_instance);
    win_screen_node->show();
    player_node->set_velocity(Vector2(0,0));
    player_node->set_dead(true);

    win_screen_node->set_deaths(numDeaths);
    win_screen_node->set_kills(numEnemiesKilled);

    // TODO: Pause all bullets in the scene, possibly including animation?
}

void Main::main_menu(){
    UtilityFunctions::print("Back to Main Menu");
    SceneTree* scene_tree = get_tree();
    Node * curr_scene = scene_tree->get_current_scene();

    CanvasLayer* level_1_node = curr_scene->get_node<CanvasLayer>(level1NodeName);
    level_1_node->queue_free();
    TypedArray<Node> children = curr_scene->get_children();
    for (int i = 0; i< children.size(); i++){
        Node* child = Object::cast_to<Node>(children[i]);
        if (child->get_class() == "WinScreen"){
            child->queue_free();
        }

    }
    // Reset signals and numbers tracked
    start_signals_connected = false;
    game_over_signal_connect = false;
    win_screen_signal_connect = false;

    numGames++;
    numDeaths = 0;
    numEnemiesKilled = 0;

    // start_game();
    MainMenu* main_menu = curr_scene->get_node<MainMenu>("MainMenu");
    main_menu->show();
}

void Main::incrementEnemiesKilled(){
    numEnemiesKilled++;
    UtilityFunctions::print(String("Current Enemies killed: ") + String::num(numEnemiesKilled));
}