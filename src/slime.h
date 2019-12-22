#ifndef SLIME_H
#define SLIME_H
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class Slime : public GameItem
{
public:
    Slime(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    void applyImpulse(b2Vec2 force);
    b2Vec2 getPosition();

    const float SLIME_DENTSITY = 12.0f;
    const float SLIME_FRICTION = 1.0f;
    const float SLIME_RESTITUTION = 0.5f;
};

#endif // SLIME_H
