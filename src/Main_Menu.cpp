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
	// ClassDB::bind_method(D_METHOD("set_speed", "speed"), &MainMenu::set_speed);
	// ClassDB::bind_method(D_METHOD("get_speed"), &MainMenu::get_speed);

	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
    // PackedScene
    ClassDB::bind_method(D_METHOD("set_scene", "p_scene"), &MainMenu::set_scene);
    ClassDB::bind_method(D_METHOD("get_scene"), &MainMenu::get_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "example_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_scene", "get_scene");

    // Start button signal
    // ClassDB::bind_method(D_METHOD("on_start_button_pressed"), &MainMenu::on_start_button_pressed);
	ADD_SIGNAL(MethodInfo("pressed_start"));

}

MainMenu::MainMenu() {
	// Initialize any variables here.
	// time_passed = 0.0;5
	// botCollisionShape2d = memnew(CollisionShape2D);
	// botSprite2d = memnew(AnimatedSprite2D);
	// botSprite2d = memnew(Sprite2D);
	// add_child(botCollisionShape2d);
	// add_child(botSprite2d);

	// botSprite2d->set_sprite_frames()
}

MainMenu::~MainMenu() {
	// Add your cleanup here.
}

// void MainMenu::set_speed(float p_speed) {
// 	speed = p_speed;
// }

// float MainMenu::get_speed() const {
// 	return speed;
// }

void MainMenu::_ready(){

    start_button = get_node<Button>("StartButton");

    // Error error = start_button->connect("pressed", Callable(this, "on_start_button_pressed"));
    // if (error != OK) {
    //    UtilityFunctions::print(String("Failed to connect signal: ") + error);
    // }
    UtilityFunctions::print("Should work!?");
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

void MainMenu::_process(double delta) {
    // UtilityFunctions::print("Main menu process start");

    if (start_button->is_pressed()){
        UtilityFunctions::print("Start Button emit");
        emit_signal("pressed_start");
        // on_start_button_pressed();
    }
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

// void MainMenu::_physics_process(double p_delta){
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

void MainMenu::set_scene(Ref<PackedScene> p_scene)
{
    mainScene = p_scene;
}

Ref<PackedScene> MainMenu::get_scene()
{
    return mainScene;
}

// void MainMenu::on_start_button_pressed(){
//     UtilityFunctions::print("Start Button Pressed!");
//     SceneTree* scene_tree = get_tree();
//     levelScene = ResourceLoader::get_singleton()->load("res://level-1.tscn");
//     scene_tree->change_scene_to_packed(levelScene);

// }
