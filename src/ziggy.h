#ifndef ZIGGY_H
#define ZIGGY_H

#include <gameitem.h>
#include <QPixmap>
#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>



class Ziggy : public GameItem
{
    Q_OBJECT
public:
    Ziggy(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    void applyImpulse(b2Vec2 force);
    bool eventFilter(QObject *obj, QEvent *event) override;

    const float ZIGGY_DENTSITY = 15.0f;
    const float ZIGGY_FRICTION = 1.0f;
    const float ZIGGY_RESTITUTION = 0.5f;

protected:
    bool isJumping;

};

#endif // ZIGGY_H