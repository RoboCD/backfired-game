#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
// #include <godot_cpp/classes/character_body2d.hpp>
// #include <godot_cpp/classes/animated_sprite2d.hpp>
// #include <godot_cpp/classes/collision_shape2d.hpp>
// #include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/button.hpp>

namespace godot {

class MainMenu : public CanvasLayer {
	GDCLASS(MainMenu, CanvasLayer)
public:
	MainMenu();
	~MainMenu();

    void _ready() override;

	void _process(double delta) override;

    void set_scene(Ref<PackedScene> p_scene);
    Ref<PackedScene> get_scene();
    void on_start_button_pressed();

protected:
	static void _bind_methods();

private:
    Ref<PackedScene> mainScene;
    Ref<PackedScene> levelScene;
    bool firstLoop{true};
    bool nullLoop{false};

    Button * start_button = nullptr;
};

}

#endif