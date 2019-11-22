#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);

    const float BIRD_DENSITY = 10.0f;
    const float BIRD_FRICTION = 0.2f;
    const float BIRD_RESTITUTION = 0.5f;

};

#endif // BIRD_H
