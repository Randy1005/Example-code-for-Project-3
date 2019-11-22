#include "ziggy.h"

Ziggy::Ziggy(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    : GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(w, h);

    // create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    bodyDef.position.Set(x, y);
    bodyDef.userData = this;
    g_body = world->CreateBody(&bodyDef);

    // define shape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(w, h);

    // define fixtures
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = ZIGGY_DENTSITY;
    fixtureDef.friction = ZIGGY_FRICTION;
    fixtureDef.restitution = ZIGGY_RESTITUTION;
    g_body->CreateFixture(&fixtureDef);

    // parse animation description
    parseAnimDescription(":/ziggy_anim.json");

    // connect timer
    connect(timer, SIGNAL(timeout()), this, SLOT(paint()));

    // test
    startAnim("idle");

}

void Ziggy::setLinearVelocity(b2Vec2 velocity) {
    g_body->SetLinearVelocity(velocity);
}
