#ifndef MAIN_H
#define MAIN_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
// #include <godot_cpp/classes/character_body2d.hpp>
// #include <godot_cpp/classes/animated_sprite2d.hpp>
// #include <godot_cpp/classes/collision_shape2d.hpp>
// #include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class Main : public Node {
	GDCLASS(Main, Node)
public:
	Main();
	~Main();

    void _ready() override;

	void _process(double delta) override;

    void set_scene(Ref<PackedScene> p_scene);
    Ref<PackedScene> get_scene();
    void start_game();
    void game_over(Node* p_node);
    void restart_game();
protected:
	static void _bind_methods();

private:
    Ref<PackedScene> mainScene;
    // Ref<PackedScene> main_menu;
    bool firstLoop{true};
    bool nullLoop{false};
    bool levelLoaded{false};
    bool player_died_sig_connect{false};
    bool game_over_sig_connect{false};
    int numTries{0};
};

}

#endif