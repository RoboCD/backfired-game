#ifndef BULLET_H
#define BULLET_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class Bullet : public CharacterBody2D {
	GDCLASS(Bullet, CharacterBody2D)
public:
	Bullet();
	~Bullet();

	virtual void _physics_process(double p_delta) override;

    void start(Vector2 position, double direction);

protected:
	static void _bind_methods();

private:
	float speed = 600.0;
	Sprite2D *bulletSprite2d = nullptr;
    double rotation{0};
};

}

#endif
