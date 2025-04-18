#ifndef MAIN_H
#define MAIN_H

#include "Game_Over.h"
#include "Win_Screen.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

namespace godot {

class Main : public Node {
	GDCLASS(Main, Node)
public:
	Main();
	~Main();

    void _ready() override;

	void _process(double delta) override;

    void start_game();

    void game_over(Node* p_node);

    void restart_game();

    void game_won(Node* p_node);

    void main_menu();

protected:
	static void _bind_methods();

private:
    bool start_signals_connected{false};
    bool game_over_signal_connect{false};
    bool win_screen_signal_connect{false};

    int numTries{0};

    Ref<PackedScene> game_over_screen;
    Ref<PackedScene> win_screen;
};

}

#endif