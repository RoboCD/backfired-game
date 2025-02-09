#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/button.hpp>

namespace godot {

class GameOver : public CanvasLayer {
	GDCLASS(GameOver, CanvasLayer)
public:
	GameOver();
	~GameOver();

    void _ready() override;

	void _process(double delta) override;

    void on_restart_button_pressed();

    void set_message(String p_message);

    void set_deaths(int deaths);

protected:
	static void _bind_methods();

private:
    Ref<PackedScene> levelScene;

    bool pressed_once{false};
    Button * restart_button = nullptr;
    String message{};
};

}

#endif