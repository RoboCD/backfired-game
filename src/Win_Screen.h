#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/button.hpp>


namespace godot{

class WinScreen : public CanvasLayer {
    GDCLASS(WinScreen, CanvasLayer)
public:
    WinScreen();
    ~WinScreen();

    void _ready() override;

	void _process(double delta) override;

    void set_deaths(int deaths);

    void on_main_menu_button_pressed();
protected:
    static void _bind_methods();
private:
    Ref<PackedScene> mainMenuScene;
    Button * main_menu_button = nullptr;
    bool pressed_once{false};


};

}

#endif