#include "Player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include "Bullet.h"

using namespace godot;

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Player::set_speed);
	ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

	ClassDB::bind_method(D_METHOD("set_gravity", "gravity"), &Player::set_gravity);
	ClassDB::bind_method(D_METHOD("get_gravity"), &Player::get_gravity);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity"), "set_gravity", "get_gravity");

	ClassDB::bind_method(D_METHOD("set_friction", "friction"), &Player::set_friction);
	ClassDB::bind_method(D_METHOD("get_friction"), &Player::get_friction);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "friction"), "set_friction", "get_friction");

	ClassDB::bind_method(D_METHOD("set_texture", "texture"), &Player::set_texture);
	ClassDB::bind_method(D_METHOD("get_texture"), &Player::get_texture);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");

	ADD_SIGNAL(MethodInfo("player_died", PropertyInfo(Variant::OBJECT, "node")));
}

Player::Player() {
	// Initialize any variables here.
	time_passed = 0.0;

	playerSprite2d = memnew(Sprite2D);

	add_child(playerSprite2d);
	playerSprite2d->set_process(true);

	gravity = ProjectSettings::get_singleton()->get_setting("physics/2d/default_gravity");

	set_floor_stop_on_slope_enabled(false);
	playerSprite2d->set_texture(texture);

	bulletScene = ResourceLoader::get_singleton()->load("res://bullet.tscn");
}

Player::~Player() {
	// Add your cleanup here.
}

void Player::_ready(){
	show();
	dead = false;
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

void Player::set_friction(float p_friction){
	friction = p_friction;
}

float Player::get_friction() const{
	return friction;
}

void Player::set_texture(const Ref<Texture2D> &p_texture){
	texture = p_texture;
	playerSprite2d->set_texture(p_texture);
}

Ref<Texture2D> Player::get_texture() const{
	return playerSprite2d->get_texture();
}

void Player::_process(double delta) {
	time_passed += delta;

	Vector2 position = get_global_position();
	if (position.y > 1000){
		die();
	}
}

void Player::_physics_process(double p_delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
	if (dead){
		return;
	}
	Input *input = Input::get_singleton();

	Vector2 velocity = get_velocity();

	double rotation = get_global_rotation_degrees();
	bool shoot{false};

	if (is_on_floor()){
		velocity = add_friction(velocity);
	}

	if(input->is_action_just_pressed("shoot")){
		shoot = true;
	}

	if (input->is_action_pressed("ui_left")) {
		rotation -= 5.0;
	} else if (input->is_action_pressed("ui_right")) {
		rotation += 5.0;
	}
	set_global_rotation_degrees(rotation);
	double rotation_rad = UtilityFunctions::deg_to_rad(rotation);

	if (shoot){
		velocity.x = UtilityFunctions::cos(rotation_rad) * -1 * speed;
		velocity.y = UtilityFunctions::sin(rotation_rad) * -1 * speed;
	}
	else {
		velocity.y += (gravity * p_delta);
	}

	int collision_num = get_slide_collision_count();

	for (int i = 0; i < collision_num; i++){
		Ref<KinematicCollision2D> collision = get_slide_collision(i);
        String collision_class = collision->get_collider()->get_class();

        if(collision_class == "Enemy"){
			UtilityFunctions::print("Hit Player: ", collision_class);
			// Die
			velocity.x = 0;
			velocity.y = 0;
			set_velocity(velocity);
			die();
        }
    }

	set_velocity(velocity);
	if (shoot){
		shoot_beam();
	}
	move_and_slide();
}

void Player::shoot_beam(){
	Node* bullet_instance = bulletScene->instantiate();
	SceneTree* scene_tree = get_tree();
	Bullet* bulletNode = bullet_instance->get_node<Bullet>(".");

	Marker2D* muzzle = get_node<Marker2D>("Marker2D");
	Vector2 muzzlePosition = muzzle->get_global_position();
	double muzzleRotation = muzzle->get_global_rotation_degrees();
	UtilityFunctions::print("Muzzle position: ", String(muzzlePosition), "Rotation: ", muzzleRotation);

	add_child(bullet_instance);
	bulletNode->start(muzzlePosition, muzzleRotation);

	// Play sound
	get_node<AudioStreamPlayer>("Lazer Sound")->play();
}

Vector2 Player::add_friction(Vector2 velcoity){
	double x_magnitude = std::fabs(velcoity.x);

	if (x_magnitude > friction){
		x_magnitude -= friction;
		velcoity.x = std::copysign(x_magnitude,velcoity.x);
	}
	else
	{
		velcoity.x = 0;
	}

	return velcoity;
}

void Player::die(){
	if (!dead){
		UtilityFunctions::print("Player died");
		set_dead(true);
		emit_signal("player_died",this);

		hide();
		get_node<AudioStreamPlayer>("Death Sound")->play();
	}
}

void Player::set_dead(bool p_dead){
	dead = p_dead;
}


void Player::pause_all_animations(bool p_pause){
    TypedArray<Node> node_list = get_children();
    for (int i = 0; i < node_list.size(); i++){
        Bullet* bullet = Object::cast_to<Bullet>(node_list[i]);
        if (bullet){
            bullet->pause_animation(true);
        }
     }
}
