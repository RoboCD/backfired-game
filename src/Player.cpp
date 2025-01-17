#include "Player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/project_settings.hpp>

using namespace godot;

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Player::set_speed);
	ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

	ClassDB::bind_method(D_METHOD("set_gravity", "gravity"), &Player::set_gravity);
	ClassDB::bind_method(D_METHOD("get_gravity"), &Player::get_gravity);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity"), "set_gravity", "get_gravity");

}

Player::Player() {
	// Initialize any variables here.
	time_passed = 0.0;
	// botCollisionShape2d = memnew(CollisionShape2D);
	// botSprite2d = memnew(AnimatedSprite2D);
	// botSprite2d = memnew(Sprite2D);
	// add_child(botCollisionShape2d);
	// add_child(botSprite2d);

	// botSprite2d->set_sprite_frames()
	// gravity = ProjectSettings::get_singleton()->get_setting("physics/2d/default_gravity");
	// gravity = gravity /2;
	gravity = 20;
}

Player::~Player() {
	// Add your cleanup here.
}

void Player::set_speed(float p_speed) {
	speed = p_speed;
}

float Player::get_speed() const {
	return speed;
}

void Player::set_gravity(float p_gravity){
	gravity = p_gravity;
}

float Player::get_gravity() const{
	return gravity;
}

void Player::_process(double delta) {
	time_passed += delta;

	// Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

	// set_position(new_position);
}

void Player::_physics_process(double p_delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
	Input *input = Input::get_singleton();

	Vector2 velocity;
	double velocity_input{0};
    // if (input->is_action_pressed("ui_up")) {
	// 	velocity.y -= 1.0;
    // } else if (input->is_action_pressed("ui_down")) {
	// 	velocity.y += 1.0;
	// } else if (input->is_action_pressed("ui_left")) {
	// 	velocity.x -= 1.0;
	// } else if (input->is_action_pressed("ui_right")) {
	// 	velocity.x += 1.0;
	// }
	// velocity.y = (gravity * p_delta);
	double rotation = get_rotation_degrees();
	bool shoot{false};
	if(input->is_action_just_pressed("shoot")){
		// velocity_input = -1.0;
		shoot = true;
	}

	if (input->is_action_pressed("ui_left")) {
		rotation += 5.0;
	} else if (input->is_action_pressed("ui_right")) {
		rotation -= 5.0;
	}
	double rotation_rad = UtilityFunctions::deg_to_rad(rotation);

	if (shoot){
		velocity.x = UtilityFunctions::cos(rotation_rad) * -1 * speed;
		// if (velocity_input < 0.0){

		velocity.y = UtilityFunctions::sin(rotation_rad) * -1 * speed;
	}
	else {
		velocity.x = 0;
		velocity.y = 0;
	}

	if (!is_on_floor()){
		velocity.y += (gravity * p_delta);
	}
	UtilityFunctions::print("Velocity: " + String(velocity) );
	// }

	set_rotation_degrees(rotation);
	set_velocity(velocity);

	move_and_slide();
}
