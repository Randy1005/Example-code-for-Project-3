#ifndef ZIGGY_H
#define ZIGGY_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>



class Ziggy : public GameItem
{

public:
    Ziggy(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);

    const float ZIGGY_DENTSITY = 10.0f;
    const float ZIGGY_FRICTION = 0.2f;
    const float ZIGGY_RESTITUTION = 0.5f;

};

#endif // ZIGGY_H
