#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/visible_on_screen_notifier2d.hpp>

namespace godot {

class Player : public CharacterBody2D {
	GDCLASS(Player, CharacterBody2D)
public:
	Player();
	~Player();

    void _ready() override;

	void set_speed(float p_speed);
	float get_speed() const;

	void set_gravity(float p_gravity);
	float get_gravity() const;

	void set_friction(float p_friction);
	float get_friction() const;

	void set_texture(const Ref<Texture2D> &p_texture);
	Ref<Texture2D> get_texture() const;

	virtual void _physics_process(double p_delta) override;

	void _process(double delta) override;

	void shoot_beam();

    void set_dead(bool p_dead);

	void pause_all_animations(bool p_pause);

protected:
	static void _bind_methods();

private:

	Vector2 add_friction(Vector2 velcoity);

	void die();

	double time_passed;

	float speed = 600.0;

	double gravity;

	double friction = 10;

	Sprite2D *playerSprite2d = nullptr;
    VisibleOnScreenNotifier2D* notifier = nullptr;
	Ref<Texture2D> texture;

	Ref<PackedScene> bulletScene;
    bool oneShot = true;
	bool dead = false;
};

}

#endif