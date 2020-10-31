#include  <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"

using namespace std;
using namespace sf;

//класс передвигащихся по карте сущностей (в будущем - абстрактный)
class Actor {
private:
	//фигура актора
	RectangleShape hero;

	//флаги для передвижения
	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;

public:

	//коэффициент скорости передвижения
	float speed = 1;

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

	// Для движения 
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

	// Прекращение движения
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

	//метод для обновления полей для каждой интерации игрового цикла
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

	//метод для обновления полей для каждой интерации игрового цикла
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
};

int main() {
	//игровое окно
	RenderWindow window(VideoMode(500, 500), "maindo");
	//характеристики актора
	Vector2f heroSize(20, 30);
	Vector2f heroPosition(10, 20);
	Color color(255, 0, 0);
	//установка характеристик
	Actor activeActor(heroSize, heroPosition, color);
	//время для движения
	Clock clock;
	//отладочная информация
	int i = 0;
	//игровой цикл
	while (window.isOpen()) {
		Event event;
		//время для движения
		float delta = clock.restart().asSeconds();
		
		//обработчик событий и нажатий клавиш
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			//отладочная информация
			cout << i++ << " " << event.type << " " << activeActor.getHero().getPosition().x << " " << activeActor.getHero().getPosition().y << endl;

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
		
		//обновляем состояние действующего актора
		activeActor.update();
		//очищаем предыдущий кадр
		window.clear();
		//создаём новое состояние экрана
		window.draw(activeActor.getHero());
		//отрисовываем новое состояние экрана
		window.display();
		//отладочная информация
		i %= 100000;
	}
	return 0;
}