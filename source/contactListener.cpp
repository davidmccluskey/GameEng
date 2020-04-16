#pragma once
#include "Box2D/Box2D.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "components/cmp_physics.h"

class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) {
		//check if fixture A was a ball
		void* bodyA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyB = contact->GetFixtureB()->GetBody()->GetUserData();

		static_cast<PhysicsComponent*>(bodyA)->collisionResponse(bodyB);

		static_cast<PhysicsComponent*>(bodyB)->collisionResponse(bodyA);

	}

	void EndContact(b2Contact* contact) {

		//check if fixture A was a ball
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
		{
		}

		//check if fixture B was a ball
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
		{
		}

	}
};