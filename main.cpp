#include "header.cpp"
class MyGame : public utilities::TGame {
public:
	MyGame() = default;
	virtual void update() override {
		std::cout << "HELLO";
	}
	void mainloop(std::function<void()> func) override
	{
		while (!RunTime)
		{
			func();
		}
	}

};

int main() {
	MyGame game;
	auto update = game.update;
	game.mainloop(update);
}
