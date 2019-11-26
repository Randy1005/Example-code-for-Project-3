#include "bird.h"

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
    GameItem(world, false)
{
    // Set pixmap
    mSprite->setPixmap(pixmap);
    mSprite->setTransformOriginPoint(mSprite->boundingRect().width()/2, mSprite->boundingRect().height()/2);
    g_size = QSize(radius*2, radius*2);


    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bind timer
    connect(timer, SIGNAL(timeout()), this, SLOT(paint()));

    scene->addItem(mSprite);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}
