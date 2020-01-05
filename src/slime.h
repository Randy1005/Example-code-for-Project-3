#ifndef SLIME_H
#define SLIME_H
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <commonInfo.h>

class Slime : public GameItem
{
public:
    Slime(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    ~Slime() override;
    void setLinearVelocity(b2Vec2 velocity);
    void applyImpulse(b2Vec2 force);
    b2Vec2 getPosition();
    void die();

    const float SLIME_DENTSITY = 12.0f;
    const float SLIME_FRICTION = 1.0f;
    const float SLIME_RESTITUTION = 0.5f;

protected:
    udStruct *udstruct;
    QGraphicsScene *scene;
};

#endif // SLIME_H
