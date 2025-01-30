#include "Player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/marker2d.hpp>

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

	// ADD_SIGNAL(MethodInfo("payer_died"));

}

Player::Player() {
	// Initialize any variables here.
	time_passed = 0.0;
	// botCollisionShape2d = memnew(CollisionShape2D);
	// botSprite2d = memnew(AnimatedSprite2D);
	playerSprite2d = memnew(Sprite2D);
	// add_child(botCollisionShape2d);
	add_child(playerSprite2d);
	playerSprite2d->set_process(true);
	// botSprite2d->set_sprite_frames()
	gravity = ProjectSettings::get_singleton()->get_setting("physics/2d/default_gravity");
	// gravity = gravity /2;
	// gravity = 20;
	set_floor_stop_on_slope_enabled(false);
	playerSprite2d->set_texture(texture);
	// playerSprite2d->set_visible(true);

	bulletScene = ResourceLoader::get_singleton()->load("res://bullet.tscn");
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
	// return texture;
	return playerSprite2d->get_texture();
}


void Player::_process(double delta) {
	time_passed += delta;

	// Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

	// set_position(new_position);
}

void Player::_physics_process(double p_delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
	Input *input = Input::get_singleton();

	Vector2 velocity = get_velocity();

	double rotation = get_global_rotation_degrees();
	bool shoot{false};

	if (is_on_floor()){
		velocity = add_friction(velocity);
		// velocity.x = 0;
	}

	if(input->is_action_just_pressed("shoot")){
		shoot = true;
		// shoot_beam();
		// Spawn bullet
		// Bullet * bullet = memnew(Bullet);
		// add_child(bullet);

		// // bullet->
		// SceneTree* scene_tree = get_tree();
		// Ref<PackedScene> bulletScene = ResourceLoader::get_singleton()->load("res://level-1.tscn");
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
		// velocity.x = -1*speed;
		// velocity = velocity.x.rotated(rotation_rad);
	}
	else {
		velocity.y += (gravity * p_delta);
	}

	// UtilityFunctions::print("Velocity: " + String(velocity) );
	// UtilityFunctions::print("Rotation: ", rotation);
    // Marker2D * muzzle = get_node<Marker2D>("Marker2D");
	// UtilityFunctions::print("Muzzle position: ", String(muzzle->get_position()), "Rotation: ", muzzle->get_rotation_degrees());
	//
	int collision_num = get_slide_collision_count();

	for (int i = 0; i < collision_num; i++){
		Ref<KinematicCollision2D> collision = get_slide_collision(i);
		// if(!collision.is_null()){
        String collision_class = collision->get_collider()->get_class();

        UtilityFunctions::print("Hit Player: ", collision_class);
        if(collision_class == "Enemy"){
			// Die
			queue_free();
            // Object * collider = collision->get_collider();
            // Node * collider_node = Object::cast_to<Node>(collider);
            // collider_node->queue_free();
        }
    }

	set_velocity(velocity);
	if (shoot){
		shoot_beam();
	}
	move_and_slide();


}

void Player::shoot_beam(){
	// C#
	// var b = (Bullet)_bullet.Instantiate();
	// b.Start(GetNode<Node2D>("Muzzle").GlobalPosition, Rotation);
	// GetTree().Root.AddChild(b);

	// Ref<PackedScene> bullet_instance =
	Node* bullet_instance = bulletScene->instantiate();
	SceneTree* scene_tree = get_tree();
	Bullet* bulletNode = bullet_instance->get_node<Bullet>(".");
	// ("Bullet");
	Marker2D* muzzle = get_node<Marker2D>("Marker2D");
	Vector2 muzzlePosition = muzzle->get_global_position();
	double muzzleRotation = muzzle->get_global_rotation_degrees();
	UtilityFunctions::print("Muzzle position: ", String(muzzlePosition), "Rotation: ", muzzleRotation);

	// bulletNode->set_global_position(muzzlePosition);
	scene_tree->get_current_scene()->add_child(bullet_instance);
	// bullet_instance->set_physics_process(false);
	// bulletNode->set_position(muzzlePosition);
	// bulletNode->call_deferred("set_position",muzzlePosition);

	// scene_tree->get_current_scene()->get_child(2)->get_node<Bullet>("Bullet")->start(muzzlePosition, muzzleRotation);
	// if (oneShot){
	bulletNode->start(muzzlePosition, muzzleRotation);
	// bullet_instance->set_physics_process(true);
	// 	oneShot = false;
	// }
    // bulletScene.Bullet.start();
	// start_button = get_node<Button>("StartButton");

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

// void Player::die(){
// 	UtilityFunctions::print("Player died");
// 	emit_signal("payer_died",this,true);
// 	// on_start_button_pressed();

// }