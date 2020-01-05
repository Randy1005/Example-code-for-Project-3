#ifndef RESETBALL_H
#define RESETBALL_H
#include <gameitem.h>
#include <QGraphicsScene>
#include <QTimer>

class ResetBall : public GameItem
{
public:
    ResetBall(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    const float BALL_DENSITY = 10.0f;
    const float BALL_FRICTION = 0.2f;
    const float BALL_RESTITUTION = 0.5f;
    QGraphicsScene *scene;

};

#endif // RESETBALL_H
