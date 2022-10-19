// CGT 215 LAB 7-EVAN YODER.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	int thudCount(0);

	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));
	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(200, 300));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	window.draw(ball); 


	// Create center rectangle
	PhysicsRectangle square;
	square.setCenter(Vector2f(400, 300));
	square.setSize(Vector2f(200, 200));
	square.setStatic(true);
	world.AddPhysicsBody(square);
	window.draw(square);
	int bangCount(0);
	
	square.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
	};
	
	// Create left wall
	PhysicsRectangle wall1;
	wall1.setSize(Vector2f(20,560));
	wall1.setCenter(Vector2f(0,300));
	wall1.setStatic(true);
	world.AddPhysicsBody(wall1);
	window.draw(wall1); 
	wall1.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	// Create celing
	PhysicsRectangle celing;
	celing.setSize(Vector2f(800,20));
	celing.setCenter(Vector2f(400, 10));
	celing.setStatic(true);
	world.AddPhysicsBody(celing);
	window.draw(celing);
	celing.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	// Create right wall
	PhysicsRectangle wall2;
	wall2.setSize(Vector2f(20, 560));
	wall2.setCenter(Vector2f(800, 300));
	wall2.setStatic(true);
	world.AddPhysicsBody(wall2);
	window.draw(wall2);
	wall2.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};
	ball.applyImpulse(Vector2f(0.50, 0));
	

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(square);
		window.draw(floor);
		window.draw(wall1);
		window.draw(celing);
		window.draw(wall2);
		window.display();
		if (bangCount == 3) {
			exit(0);
		}
	}
	

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
