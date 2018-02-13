#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


Vector2f ballVelocity;
bool server = false;
const Keyboard::Key controls[4] = {
	Keyboard::A, //PLAYER1 UP
	Keyboard::Z, //P1 DOWN
	Keyboard::Up, //PLAYER2 UP
	Keyboard::Down //P2 DOWN
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];
void Load() {
	//Set size and origin of paddles
	for (auto &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	//Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	//Reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
	//Reset ball position2
	ball.setPosition(gameWidth / 2, gameHeight / 2);
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
	
}
void Reset() {
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
	//Reset ball position2
	ball.setPosition(gameWidth / 2, gameHeight / 2);
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
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
	//Handle paddle movement
	float directionL = 0.0f;
	float directionR = 0.0f;

	if (Keyboard::isKeyPressed(controls[0])) {
		directionL--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		directionL++;
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		directionR--;
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		directionR++;
	}

	ball.move(ballVelocity * dt);
	paddles[0].move(0, directionL* paddleSpeed * dt);
	paddles[1].move(0, directionR* paddleSpeed * dt);
	//Check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight) {
		//Bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) {
		//top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth) {
		//right wall
		Reset();
	}
	else if (bx < 0) {
		//left wall
		Reset();
	}
	else if (bx<paddleSize.x &&
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)) {
		//left paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
	}
	else if (bx > gameWidth - paddleSize.x &&
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)) {
		//left paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
	}
}
void Render(RenderWindow &window) {
	//Draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
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