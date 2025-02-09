#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/button.hpp>

namespace godot {

class MainMenu : public CanvasLayer {
	GDCLASS(MainMenu, CanvasLayer)
public:
	MainMenu();
	~MainMenu();

    void _ready() override;

	void _process(double delta) override;

protected:
	static void _bind_methods();

private:
    Button * start_button = nullptr;
};

}

#endif