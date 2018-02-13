#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;
const int gameWidth = 800;
const int gameHeight = 600;
void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spriteshet!" << std::endl;
	}
}
void Update(RenderWindow &window) {
	//Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//Check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	//Quit Via ESC KEY
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}
void Render(RenderWindow &window) {
}
int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}