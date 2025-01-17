#include "Player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Player::set_speed);
	ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
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

void Player::_process(double delta) {
	// time_passed += delta;

	// Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

	// set_position(new_position);
}

void Player::_physics_process(double p_delta){
	Input *input = Input::get_singleton();

	Vector2 velocity;
    if (input->is_action_pressed("ui_up")) {
		velocity.y -= 1.0;
    } else if (input->is_action_pressed("ui_down")) {
		velocity.y += 1.0;
	} else if (input->is_action_pressed("ui_left")) {
		velocity.x -= 1.0;
	} else if (input->is_action_pressed("ui_right")) {
		velocity.x += 1.0;
	}

	set_velocity(velocity.normalized() * speed);

	move_and_slide();
}
