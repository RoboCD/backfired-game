
#include "Bullet.h"

#include <godot_cpp/classes/kinematic_collision2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>

using namespace godot;

void Bullet::_bind_methods() {
	ClassDB::bind_method(D_METHOD("start", "position", "direction"), &Bullet::start);

    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Bullet::set_speed);
	ClassDB::bind_method(D_METHOD("get_speed"), &Bullet::get_speed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

}

Bullet::Bullet() {
	// Initialize any variables here.
	// time_passed = 0.0;
	// botCollisionShape2d = memnew(CollisionShape2D);
	// botSprite2d = memnew(AnimatedSprite2D);
	// bulletSprite2d = memnew(Sprite2D);
	// add_child(botCollisionShape2d);
	// add_child(bulletSprite2d);
	// bulletSprite2d->set_process(true);
	// botSprite2d->set_sprite_frames()
	// gravity = ProjectSettings::get_singleton()->get_setting("physics/2d/default_gravity");
	// gravity = gravity /2;
	// gravity = 20;
	// set_floor_stop_on_slope_enabled(false);
	// bulletSprite2d->set_texture(texture);
	// playerSprite2d->set_visible(true);
}

Bullet::~Bullet() {
	// Add your cleanup here.
}

void Bullet::_physics_process(double delta){
    if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
    Vector2 velocity;
    Ref<KinematicCollision2D> collision = move_and_collide( Vector2(speed,0).rotated(rotation) * delta);
    // UtilityFunctions::print("Collision: ", collision. )
    if(!collision.is_null()){
        int collision_num = get_slide_collision_count();
        String collision_class = collision->get_collider()->get_class();

        UtilityFunctions::print("Hit ", collision_class);
        if(collision_class == "Enemy"){
            Object * collider = collision->get_collider();
            Node * collider_node = Object::cast_to<Node>(collider);
            collider_node->queue_free();
            get_parent()->get_node<AudioStreamPlayer>("Enemy Hit")->play();

        }
        hide();
        // _sleep(1);
        call_deferred("queue_free");
        // queue_free();
    }
}

void Bullet::start(Vector2 position, double direction){
    UtilityFunctions::print("Zap!");
    // double rotation = direction;
    // Position = position;
    // Velocity = new Vector2(speed, 0).Rotated(Rotation);
    // CollisionShape2D * collisionNode = get_node<CollisionShape2D>("CollisionShape2D");
    // collisionNode->set_position(position);
    // set_global_position(Vector2(100,100));
    set_global_position(position);
    set_global_rotation_degrees(direction);
    set_as_top_level(true);
    set_z_index(10);
    rotation = UtilityFunctions::deg_to_rad(direction);
    // set_velocity = Vector2(speed, 0).Rotated(Rotation);

}

void Bullet::set_speed(float p_speed) {
	speed = p_speed;
}

float Bullet::get_speed() const {
	return speed;
}