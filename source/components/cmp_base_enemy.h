#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class EnemyComponent : public Component {
protected:
    float _speed;
    float _damage;
    float _health;
    float _shotTimer;
    float _flickerTimer = 0.1;
    bool _flicker = true;
	float _min;
	float _max;
    int textureWidth;
    int textureHeight; 
    int texturePos;

public:
    void update(double dt) override;
    void render() override {}
    explicit EnemyComponent(Entity* p, float speed = 1.0f, float damage = 1.0f, float health = 1.0f);
    EnemyComponent() = delete;
    
	int getTextureWidth();
    int getTextureHeight();

    int getTexturePos();

    void setTextureSize(int width, int height, int pos);

    float getHealth();
    void setHealth(float health);
    void setShot(float shotTimer);
	void setMinMax(float min, float max);
	float getMin();
	float getMax();
};