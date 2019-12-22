#include "slime.h"

Slime::Slime(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
    GameItem(world, true)
{
    // Set pixmap
    mSprite->setPixmap(pixmap);

    // set to first frame
    mSprite->setSubRegion(QRectF(112, 320, 16, 16));

    // scale sprite
    mSprite->setScale(5.5);

    mSprite->setTransformOriginPoint(mSprite->boundingRect().width()/2, mSprite->boundingRect().height()/2);
    g_size = QSize(w, h);

    // create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    bodyDef.position.Set(x, y);
    bodyDef.userData = this;
    g_body = world->CreateBody(&bodyDef);
    g_body->SetFixedRotation(true);

    // define shape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(w, h);

    // define fixtures
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = SLIME_DENTSITY;
    fixtureDef.friction = SLIME_FRICTION;
    fixtureDef.restitution = SLIME_RESTITUTION;
    g_body->CreateFixture(&fixtureDef);
    g_body->SetLinearDamping(2.0);

    // parse animation description
    parseAnimDescription(":/slime_anim.json");

    // connect timer
    connect(timer, SIGNAL(timeout()), this, SLOT(paint()));

    scene->addItem(mSprite);
    startAnim("idle");

}

void Slime::setLinearVelocity(b2Vec2 velocity) {
    g_body->SetLinearVelocity(velocity);
}

void Slime::applyImpulse(b2Vec2 force) {
    g_body->ApplyLinearImpulse(force, g_body->GetWorldCenter(), true);
}
