#include  <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"

using namespace std;
using namespace sf;

//класс передвигащихс€ по карте сущностей (в будущем - абстрактный)
class Actor {
private:
	//фигура актора
	RectangleShape hero;

	//флаги дл€ передвижени€
	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;

public:

	//коэффициент скорости передвижени€
	float speed = 0.5;

	Actor(Vector2f& size, Vector2f& position, Color& color) {
		hero.setSize(size);
		hero.setPosition(position);
		hero.setFillColor(color);
		leftPressed = false;
		rightPressed = false;
		upPressed = false;
		downPressed = false;
	}

	RectangleShape getHero() {
		return hero;
	}

	// ƒл€ движени€ 
	void moveLeft() {
		leftPressed = true;
	}

	void moveRight() {
		rightPressed = true;
	}

	void moveUp() {
		upPressed = true;
	}

	void moveDown() {
		downPressed = true;
	}

	// ѕрекращение движени€
	void stopLeft() {
		leftPressed = false;
	}

	void stopRight() {
		rightPressed = false;
	}

	void stopUp() {
		upPressed = false;
	}

	void stopDown() {
		downPressed = false;
	}

	// (не уверен, что правильно возвращаю ссылку)
	//возвращает информацию о направлении движени€
	Vector2f& getDirection() {
		float x, y;
		if (leftPressed)
			x = -1;
		else if (rightPressed)
			x = 1;
		else
			x = 0;

		if (upPressed)
			y = -1;
		else if (downPressed)
			y = 1;
		else
			y = 0;
		
		Vector2f direction(x, y);

		return direction;
	}

	//метод дл€ обновлени€ полей дл€ каждой интерации игрового цикла
	//с учетом времени
	void update(float elapsedTime) {
		if (leftPressed)
			hero.move(-speed * elapsedTime, 0);

		if (rightPressed)
			hero.move(speed * elapsedTime, 0);

		if (upPressed)
			hero.move(0, -speed * elapsedTime);

		if (downPressed)
			hero.move(0, speed * elapsedTime);
	}

	//метод дл€ обновлени€ полей дл€ каждой интерации игрового цикла
	//без учета времени
	void update() {
		if (leftPressed)
			hero.move(-speed, 0);

		if (rightPressed)
			hero.move(speed, 0);

		if (upPressed)
			hero.move(0, -speed);

		if (downPressed)
			hero.move(0, speed);
	}

	void shiftPosition(float x, float y) {
		hero.move(x, y);
	}
};

int main() {
	//игровое окно
	RenderWindow window(VideoMode(500, 500), "maindo");
	//характеристики актора
	Vector2f heroSize(20, 30);
	Vector2f heroPosition(0, 0);
	Color color(255, 0, 0);
	//установка характеристик
	Actor activeActor(heroSize, heroPosition, color);

	RectangleShape mapBounds;
	mapBounds.setPosition(50, 50);
	mapBounds.setSize(Vector2f(400, 400));
	mapBounds.setFillColor(Color(255, 255, 255, 0));
	mapBounds.setOutlineThickness(4);
	mapBounds.setOutlineColor(Color(0, 255, 0));


	//врем€ дл€ движени€
	Clock clock;
	//отладочна€ информаци€
	int i = 0;
	//игровой цикл
	while (window.isOpen()) {
		Event event;
		//врем€ дл€ движени€
		float delta = clock.restart().asSeconds();
		
		//обработчик событий и нажатий клавиш
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			//отладочна€ информаци€
			//cout << i++ << " " << event.type << " " << activeActor.getHero().getPosition().x << " " << activeActor.getHero().getPosition().y << endl;

			if (Keyboard::isKeyPressed(Keyboard::A))
				activeActor.moveLeft();

			if (event.type == Event::KeyReleased)
				if (event.key.code == Keyboard::A)
					activeActor.stopLeft();
			
			if (Keyboard::isKeyPressed(Keyboard::D))
				activeActor.moveRight();
			
			if (event.type == Event::KeyReleased)
				if (event.key.code == Keyboard::D)
					activeActor.stopRight();

			if (Keyboard::isKeyPressed(Keyboard::S))
				activeActor.moveDown();
			
			if (event.type == Event::KeyReleased)
				if (event.key.code == Keyboard::S)
					activeActor.stopDown();

			if (Keyboard::isKeyPressed(Keyboard::W))
				activeActor.moveUp();
			
			if (event.type == Event::KeyReleased)
				if (event.key.code == Keyboard::W)
					activeActor.stopUp();
		}
		
		//обновл€ем состо€ние действующего актора
		activeActor.update();

		if (activeActor.getHero().getGlobalBounds().intersects(mapBounds.getGlobalBounds())) {
			//отладочна€ информаци€
			cout << mapBounds.getGlobalBounds().height << " " << mapBounds.getGlobalBounds().width << endl;
			//направление, в котором дальнейшее движение запрещено
			Vector2f forbiddenDirection = activeActor.getDirection();

			//cout << forbiddenDirection.x << " " << forbiddenDirection.y << endl;
			if (forbiddenDirection.x == 1) {
				activeActor.shiftPosition(-activeActor.speed, 0);
				activeActor.stopRight();
			}
			else if (forbiddenDirection.x == -1) {
				activeActor.shiftPosition(activeActor.speed, 0);
				activeActor.stopLeft();
			}
			if (forbiddenDirection.y == 1) {
				activeActor.shiftPosition(0, -activeActor.speed);
				activeActor.stopDown();
			}
			else if (forbiddenDirection.y == -1) {
				activeActor.shiftPosition(0, activeActor.speed);
				activeActor.stopUp();
			}
		}

		//очищаем предыдущий кадр
		window.clear();
		//создаЄм новое состо€ние экрана
		window.draw(mapBounds);
		window.draw(activeActor.getHero());
		
		//отрисовываем новое состо€ние экрана
		window.display();
		//отладочна€ информаци€
		i %= 100000;
	}
	return 0;
}