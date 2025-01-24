#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

namespace godot {

class Player : public CharacterBody2D {
	GDCLASS(Player, CharacterBody2D)
public:
	Player();
	~Player();

	void set_speed(float p_speed);
	float get_speed() const;

	void set_gravity(float p_gravity);
	float get_gravity() const;

	void set_texture(const Ref<Texture2D> &p_texture);
	Ref<Texture2D> get_texture() const;

	virtual void _physics_process(double p_delta) override;

	void _process(double delta) override;

	void shoot_beam();

protected:
	static void _bind_methods();

private:
	double time_passed;

	float speed = 600.0;

	double gravity;

	// AnimatedSprite2D *botSprite2d;
	Sprite2D *playerSprite2d = nullptr;
	Ref<Texture2D> texture;
    // CollisionShape2D *botCollisionShape2d;
    Ref<PackedScene> bulletScene;
    bool oneShot = true;

};

}

#endif