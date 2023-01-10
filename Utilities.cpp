#include "Utilities.h"
#include <time.h>
using std::vector;

namespace Utilities 
{

String pickName()
{
	srand(time(0));

	vector<String> names;

	names.push_back("VeryGoodGame");
	names.push_back("Maindo");
	names.push_back("Unfinished");
	names.push_back("what");
	names.push_back("Why are we still here");
	names.push_back("ovhl 1.xx <----> this string is useless");
	names.push_back("LOL LOL LOL LOL LOL LOL");
	names.push_back("Mine is better");
	names.push_back("Also try Terraria!");
	names.push_back("When I was / A young boy / My father / Took me into the city");
	names.push_back("Hajimemashite, chikyuujin-san!");
	names.push_back("Cookie ^_^");
	names.push_back("Ore wa Emilia ga suki da");
	names.push_back("My neck, my back...");
	names.push_back("3 things I hate in life: 1.Lists 2.C++ 3.Irony");
	names.push_back("Also try Minecraft!");
	names.push_back("Warning C4244: 'argument': conversion from 'int' to 'T', possible loss of data");
	names.push_back("<-----DO NOT TOUCH----->");
	names.push_back("Eighth Wonder of the World");
	names.push_back("Sometimes I pull so hard on it, I rip the skin");
	names.push_back("Angrily taking a shit");
	names.push_back("You want my property - you can't have it!");
	names.push_back("Dorimin chuchu / Chocola-ta-ta-ta-ta!");
	names.push_back("Certainly not a case of lupus");
	names.push_back("Soretomo...	wa...ta...shi?");
	names.push_back("...'cause we'll be doing this till 6 in the morning"); //whoops
	names.push_back("Full sail ahead!");
	names.push_back("cout << vector.x << " " << vector.y << endl;");
	names.push_back("For $%@^$%^# sake, would you work already?");
	names.push_back("NULL");
	names.push_back("JOJO!-da-da-da-dum-dum-dum-dum-dum-GOLD WIND!");
	names.push_back("Bangarang!");
	names.push_back("This game is not suitable for children or those who are easily disturbed");
	names.push_back(" ");
	names.push_back("It's because the heart of mine has made it here before my body");
	names.push_back("Seven circles of OOP");
	names.push_back("Sleep is overrated");
	names.push_back("Number 15: Burger King foot lettuce");
	names.push_back("O - ya - su - mi");
	names.push_back("Back in the zenzenzense till this day been looking everywhere for you...");
	names.push_back("pickName()");
	names.push_back("Welcome back, Commander");
	names.push_back("Daijoubu da yo!");
	names.push_back("B7 flat 9 flat 13");
	names.push_back("I guess you guys aren't ready for that yet... but your kids are gonna love it");
	names.push_back("F - Fm - C");
	names.push_back("Microsoft C++ exception: std::length_error at memory location 0x0055BA50");
	names.push_back("Please be quiet");
	names.push_back("Error C2398: Element '1': conversion from 'int' to 'T' requires a narrowing conversion");
	names.push_back("Debug Assertion Failed!");
	names.push_back("Stretching and shrinking and stretching and shrinking");
	names.push_back("forward_list<Projectile> projectiles");
	names.push_back("----textures----textures----textures----textures----textures----textures----");
	names.push_back("git add --all");
	names.push_back("Premature optimization is the root of all evil");
	names.push_back("names.push_back(names.push_back(names.push_back(names.push_back(names.push_back(names.push_back('a'))))))");
	names.push_back("And they were roommates...");
	names.push_back("return names.at(rand() % names.size());");
	names.push_back("Paint.net is my best friend!");
	names.push_back("Tell me if I go straight on to morning / Would there be somebody there waiting for me?");
	names.push_back("If you can't understand it then it lies beyond your understanding");
	names.push_back("Citizens of Dalaran! Raise your eyes to the skies and observe!");
	names.push_back("All around the Stactus plant the stalker chased the bandit");
	names.push_back("Soap trusted you. I thought I could too.");
	names.push_back("Is it summertime already?");
	names.push_back("The fastest goodbye song");
	names.push_back("What's cookin' good lookin'?");


	return names.at(rand() % names.size());
}


float getTimeDiff(const Clock& clock, const float& time)
{
	return clock.getElapsedTime().asSeconds() - time;
}


void setOpacity(BasicObject& object, int opacity)
{
	Color tmp = object.body.getFillColor();
	object.body.setFillColor(Color(tmp.r, tmp.g, tmp.b, opacity));
	tmp = object.body.getOutlineColor();
	object.body.setOutlineColor(Color(tmp.r, tmp.g, tmp.b, opacity));
}


Vector2f getCenterAlignment(const Sprite& insideSprite, const Vector2f& outsideAreaSize)
{
	const FloatRect insideBounds = insideSprite.getGlobalBounds();

	const float x = (outsideAreaSize.x - insideBounds.width) / 2;
	const float y = (outsideAreaSize.y - insideBounds.height) / 2;

	return { x,y };
}


Vector2f getCenterAlignment(const Sprite& insideSprite, const Sprite& outsideSprite)
{
	const FloatRect insideBounds = insideSprite.getGlobalBounds();
	const FloatRect outsideBounds = outsideSprite.getGlobalBounds();

	const float x = (outsideBounds.width - insideBounds.width) / 2;
	const float y = (outsideBounds.height - insideBounds.height) / 2;

	return { x,y };
}

// get center point of a RectangleShape
Vector2f getCenter(RectangleShape rectangle)
{
    return rectangle.getPosition() + rectangle.getSize() / 2.f;
}

}