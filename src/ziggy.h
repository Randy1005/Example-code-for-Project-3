#ifndef ZIGGY_H
#define ZIGGY_H

#include <gameitem.h>
#include <QPixmap>
#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <bulletwave.h>
#include <hpbar.h>
#include <commonInfo.h>
#include <QMediaPlayer>



class Ziggy : public GameItem
{
    Q_OBJECT
public:
    Ziggy(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    ~Ziggy() override;
    void setLinearVelocity(b2Vec2 velocity);
    void applyImpulse(b2Vec2 force);
    b2Vec2 getPosition();
    HPbar* getHPBar();
    int getHP();
    void fire();
    void HPDecrement();
    bool eventFilter(QObject *obj, QEvent *event) override;

    const float ZIGGY_DENTSITY = 12.0f;
    const float ZIGGY_FRICTION = 1.0f;
    const float ZIGGY_RESTITUTION = 0.5f;

protected:
    bool isSwingingSword;
    QTimer *tmr;
    b2World *world;
    QGraphicsScene *scene;
    udStruct *udstruct;
    int HP;
    HPbar *hpbar;
    QMediaPlayer *bulletWaveSFX;
    QMediaPlayer *oofSFX;

};

#endif // ZIGGY_H
