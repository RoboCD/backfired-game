#include "Enemy.h"
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Enemy::_bind_methods() {
    ADD_SIGNAL(MethodInfo("enemy_hit"));
}

Enemy::Enemy(){
	gravity = ProjectSettings::get_singleton()->get_setting("physics/2d/default_gravity");
}

Enemy::~Enemy(){
}

void Enemy::_process(double delta){
}

void Enemy::_physics_process(double p_delta){
    if (Engine::get_singleton()->is_editor_hint()) return;
    Vector2 velocity = get_velocity();
    if(is_on_floor()){
        velocity.y = 0;
    }
    else{
        velocity.y += (gravity * p_delta);
    }
	set_velocity(velocity);
	move_and_slide();
}

void Enemy::die(){
    UtilityFunctions::print("emit enemy_hit");
    emit_signal("enemy_hit");
    hide();
    call_deferred("queue_free");
}
