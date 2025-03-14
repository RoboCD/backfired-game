#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include <godot_cpp/classes/canvas_layer.hpp>


namespace godot{

class WinScreen : public CanvasLayer {
    GDCLASS(WinScreen, CanvasLayer)
public:
    WinScreen();
    ~WinScreen();
protected:
    static void _bind_methods();
private:


};

}

#endif