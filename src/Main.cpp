#include "Main.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include <gdextension_interface.h>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

using namespace godot;

void Main::_bind_methods() {
	// ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Main::set_speed);
	// ClassDB::bind_method(D_METHOD("get_speed"), &Main::get_speed);

	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
    // PackedScene
    ClassDB::bind_method(D_METHOD("set_scene", "p_scene"), &Main::set_scene);
    ClassDB::bind_method(D_METHOD("get_scene"), &Main::get_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "example_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_scene", "get_scene");
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