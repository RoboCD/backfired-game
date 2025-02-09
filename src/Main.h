#ifndef MAIN_H
#define MAIN_H

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

protected:
	static void _bind_methods();

private:
    bool signals_connected{false};

    int numTries{0};
};

}

#endif