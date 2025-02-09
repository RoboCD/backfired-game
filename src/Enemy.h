#ifndef ENEMY_H
#define ENEMY_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

namespace godot {

class Enemy : public CharacterBody2D {
	GDCLASS(Enemy, CharacterBody2D)
public:
	Enemy();
	~Enemy();

	virtual void _physics_process(double p_delta) override;

	void _process(double delta) override;

protected:
	static void _bind_methods();

private:
	double time_passed;
	double gravity = 980;
};

}

#endif