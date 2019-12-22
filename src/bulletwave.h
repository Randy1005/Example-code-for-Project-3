#ifndef BULLETWAVE_H
#define BULLETWAVE_H
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>


class BulletWave : public GameItem
{
    Q_OBJECT
public:
    BulletWave(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void applyImpulse(b2Vec2 force);
    b2Vec2 getPosition();

    // contact methods
    void startContact();
    void endContact();


    // destroy self : travelled some distance / bump into enemies

    const float BULLET_DENSITY = 1.0f;
    const float BULLET_FRICTION = 1.0f;
    const float BULLET_RESTITUTION = 0.5f;

protected:
    bool m_contacting;
};

#endif // BULLETWAVE_H
