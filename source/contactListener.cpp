#pragma once
#include "Box2D/Box2D.h"
#include <vector>
#include <algorithm>
#include <iostream>

class MyContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact) {
        //check if fixture A was a ball
        void* bodyUserData = contact->GetFixtureA()->GetUserData();
        std::cout << bodyUserData << std::endl;
        if (bodyUserData)
        {
            std::cout << "A" << std::endl;
        }

        //check if fixture B was a ball
        bodyUserData = contact->GetFixtureB()->GetUserData();
        std::cout << bodyUserData << std::endl;
        if (bodyUserData)
        {
            std::cout << "B" << std::endl;
        }

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