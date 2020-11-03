#include <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
#include "Actor.h"
#include "Kevin.h"
#include "NPC.h"
#include "Robot.h"
#include "Weapon.h"

using namespace std;
using namespace sf;



int main() {
	//игровое окно
	RenderWindow window(VideoMode(640, 310), "Maindo");
	//характеристики актора
	Vector2f heroSize(20, 30);
	Vector2f heroPosition(0, 0);
	Color color(255, 0, 0);
	//установка характеристик
	Kevin activeActor(heroSize, heroPosition, color);
	activeActor.speed = 100;
	//вид камеры можно задать как хочется
	View alternativeView;
	//утсанавливаем центр камеры
	alternativeView.setCenter(activeActor.getHero().getPosition());
	//устанавливаем размер области попадающей в камеру
	//alternativeView.setSize(sf::Vector2f(1280, 720));
	//зум камеры 
	//alternativeView.zoom(4.f);
	//расположение окна камеры
	alternativeView.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));

	RectangleShape mapBounds;
	mapBounds.setPosition(50, 50);
	mapBounds.setSize(Vector2f(400, 400));
	mapBounds.setFillColor(Color(255, 255, 255, 0));
	mapBounds.setOutlineThickness(4);
	mapBounds.setOutlineColor(Color(0, 255, 0));


	//время для движения
	Clock clock;
	//отладочная информация
	int i = 0;
	//игровой цикл
	while (window.isOpen()) {
		Event event;
		//время для движения
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		
		//обработчик событий и нажатий клавиш
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			//отладочная информация
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
		
		//обновляем состояние действующего актора
		activeActor.update(time);

		//проверяем коллизии
		activeActor.collisionCheck(&mapBounds, &time);

		//очищаем предыдущий кадр
		window.clear();

		//ставим центр камеры так, чтобы камера следила за игроком
		alternativeView.setCenter(activeActor.getHero().getPosition());
		//обязаельное действие: установка вида как текущее
		//window.setView(alternativeView);

		//создаём новое состояние экрана
		window.draw(mapBounds);
		window.draw(activeActor.getHero());
		
		//отрисовываем новое состояние экрана
		window.display();


		//отладочная информация
		i %= 100000;
	}

	return 0;
}