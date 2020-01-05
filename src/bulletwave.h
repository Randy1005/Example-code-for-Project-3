#ifndef BULLETWAVE_H
#define BULLETWAVE_H
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <commonInfo.h>

class BulletWave : public GameItem
{
    Q_OBJECT
public:
    BulletWave(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    ~BulletWave();
    void applyImpulse(b2Vec2 force);
    b2Vec2 getPosition();
    void selfDestroy();


    const float BULLET_DENSITY = 1.0f;
    const float BULLET_FRICTION = 1.0f;
    const float BULLET_RESTITUTION = 0.5f;

protected:
    bool m_contacting;
    udStruct *udstruct;
    QGraphicsScene *scene;

};

#endif // BULLETWAVE_H
