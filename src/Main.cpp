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
	// ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Main::set_speed);
	// ClassDB::bind_method(D_METHOD("get_speed"), &Main::get_speed);

	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
    // PackedScene
    ClassDB::bind_method(D_METHOD("set_scene", "p_scene"), &Main::set_scene);
    ClassDB::bind_method(D_METHOD("get_scene"), &Main::get_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "example_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_scene", "get_scene");

    ClassDB::bind_method(D_METHOD("start_game"), &Main::start_game);
    ClassDB::bind_method(D_METHOD("game_over", "p_node"), &Main::game_over);
    ClassDB::bind_method(D_METHOD("restart_game"), &Main::restart_game);
    ClassDB::bind_method(D_METHOD("game_won", "p_node"), &Main::game_won);

}

Main::Main() {
	// Initialize any variables here.
	// time_passed = 0.0;5
	// botCollisionShape2d = memnew(CollisionShape2D);
	// botSprite2d = memnew(AnimatedSprite2D);
	// botSprite2d = memnew(Sprite2D);
	// add_child(botCollisionShape2d);
	// add_child(botSprite2d);

	// botSprite2d->set_sprite_frames()
}

Main::~Main() {
	// Add your cleanup here.
}

// void Main::set_speed(float p_speed) {
// 	speed = p_speed;
// }

// float Main::get_speed() const {
// 	return speed;
// }

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

    // if (mainScene == nullptr)
    // {
    //     return;
    // }
    // // Instantiate Scene
    // Node *inst = mainScene->instantiate();
    // // Type checking
    // if (typeid(*inst) == typeid(Sprite2D))
    // {
    //     UtilityFunctions::print("Node is a Sprite 2D");
    // }
    // else
    // {
    //     UtilityFunctions::print("Node is NOT a Sprite 2D");
    // }
    // // add instanced scene
    // add_child(inst);
    // // Print name for no reason :)
    // UtilityFunctions::print(inst->get_name());
}

void Main::_process(double delta) {
    SceneTree* scene_tree = get_tree();

    Node * curr_scene = scene_tree->get_current_scene();
    // UtilityFunctions::print("Current Scene ", curr_scene->get_name());
    // if (!levelLoaded){
    Node* level_1_scene = get_node_or_null(NodePath(String("Level-1_"+String::num(numTries))));
    // curr_scene->print_tree();
    if (level_1_scene == nullptr){
        // UtilityFunctions::print("level 1 null");
        // curr_scene->print_tree();
        return;
    }
    if ((signals_connected == false))
    {
        UtilityFunctions::print("main connect signals");
        Player * player = level_1_scene->get_node<Player>("Player");
        // Node * player = curr_scene->find_child("Player");
        // Player * player = Node::cast_to<Player>(player_node);
        Error error = player->connect("player_died", Callable(this, "game_over"));
        UtilityFunctions::print("main player signal connect");
        if (error != OK) {
            UtilityFunctions::print(String("Failed to connect signal: ") + error);
        }
        else{
            // levelLoaded = true;
            signals_connected = true;
        }
        GameOver * game_over_node = player->get_node<GameOver>("GameOver");
        Error error_go = game_over_node->connect("pressed_restart", Callable(this, "restart_game"));
        UtilityFunctions::print("game over node signal connect");
        if (error_go != OK) {
            UtilityFunctions::print(String("Failed to connect signal: ") + error);
        }
        else{
            // levelLoaded = true;
            signals_connected = true;
        }

        Area2D * exit_area = level_1_scene->get_node<Area2D>("Exit");
        Error error_exit = exit_area->connect("body_entered", Callable(this, "game_won"));
        UtilityFunctions::print("game won node signal connect");
        if (error_exit != OK) {
            UtilityFunctions::print(String("Failed to connect exit area signal: ") + error);
        }
        else{
            // levelLoaded = true;
            signals_connected = true;
        }
    }

    // }

    // if (curr_scene->get_name() == String("Level-1")){


    //     Ref<PackedScene> game_over_scene = ResourceLoader::get_singleton()->load("res://game_over.tscn");
    //     Node* game_over_inst = game_over_scene->instantiate();
    //     GameOver* game_over_node = game_over_inst->get_node<GameOver>(".");
    //     curr_scene->get_node<Player>("Player")->add_child(game_over_node);

    // }

	// time_passed += delta;
    // if (firstLoop){
    // Ref<PackedScene> packed_scene;
    // packed_scene = ResourceLoader::get_singleton()->load("res://main.tscn");
    // if (packed_scene == nullptr){
    //     UtilityFunctions::print("current packed scene null");
    // }
    // else{
    //     Node * packedInst = packed_scene->instantiate();
    //     if (firstLoop){
    //         UtilityFunctions::print("Current packed scene name: " + packedInst->get_name());
    //     }
    //     firstLoop = false;
    // }

	// // Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

	// // set_position(new_position);
    // Ref<PackedScene> curScene = get_scene();

    // if (curScene == nullptr && nullLoop == false){
    //     UtilityFunctions::print("current scene null");
    //     nullLoop = true;
    // }
    // else{
    //     Node * currInst = curScene->instantiate();
    //     if (firstLoop){
    //         UtilityFunctions::print("Current scene name: " + currInst->get_name());
    //     }
    //     firstLoop = false;
    // }
    // }
}

// void Main::_physics_process(double p_delta){
// 	Input *input = Input::get_singleton();

// 	Vector2 velocity;
//     if (input->is_action_pressed("ui_up")) {
// 		velocity.y -= 1.0;
//     } else if (input->is_action_pressed("ui_down")) {
// 		velocity.y += 1.0;
// 	} else if (input->is_action_pressed("ui_left")) {
// 		velocity.x -= 1.0;
// 	} else if (input->is_action_pressed("ui_right")) {
// 		velocity.x += 1.0;
// 	}

// 	set_velocity(velocity.normalized() * speed);

// 	move_and_slide();
// }

void Main::set_scene(Ref<PackedScene> p_scene)
{
    mainScene = p_scene;
}

Ref<PackedScene> Main::get_scene()
{
    return mainScene;
}

void Main::start_game(){
    UtilityFunctions::print("Start Game Pressed!");
    SceneTree* scene_tree = get_tree();
    Node * curr_scene = scene_tree->get_current_scene();
    // if (levelLoaded){
    //     curr_scene->get_node<Player>("Player")->get_node<GameOver>("GameOver")->hide();
    //     // scene_tree->reload_current_scene();
    //     curr_scene->queue_free();
    // }
    // else
    // {
    Ref<PackedScene> level1Scene = ResourceLoader::get_singleton()->load("res://level-1.tscn");
    // scene_tree->change_scene_to_packed(level1Scene);
    Node* level_1_inst = level1Scene->instantiate();
    CanvasLayer* level_1_node = level_1_inst->get_node<CanvasLayer>(".");
    level_1_node->set_name("Level-1_"+String::num(numTries));
    curr_scene->add_child(level_1_node);
    MainMenu* main_menu = curr_scene->get_node<MainMenu>("MainMenu");
    main_menu->hide();
    // }

}

void Main::game_over(Node* p_node){
// void Main::game_over(){
    UtilityFunctions::print("Game Over!");
    p_node->get_node<GameOver>("GameOver")->show();

}

void Main::restart_game(){
    SceneTree* scene_tree = get_tree();
    Node * curr_scene = scene_tree->get_current_scene();
    // if (levelLoaded){
    CanvasLayer* level_1_node = curr_scene->get_node<CanvasLayer>("Level-1_"+String::num(numTries));
    level_1_node->get_node<Player>("Player")->get_node<GameOver>("GameOver")->hide();
    level_1_node->queue_free();
    signals_connected = false;
    numTries++;
    // scene_tree->reload_current_scene();
    start_game();
    // MainMenu* main_menu = curr_scene->get_node<MainMenu>("MainMenu");
    // main_menu->show();
    // }
    // start_game();
}

void Main::game_won(Node* p_node){
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
