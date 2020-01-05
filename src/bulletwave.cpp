#include "bulletwave.h"

BulletWave::BulletWave(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) :
    GameItem(world, true), m_contacting(false), scene(scene)
{
    // define userDataStruct
    udstruct = new udStruct;
    udstruct->id = 2;
    udstruct->charactePtr = this;

    // Set pixmap
    mSprite->setPixmap(pixmap);

    // set to first frame
    mSprite->setSubRegion(QRectF(64, 290, 20, 10));

    // scale sprite
    mSprite->setScale(5.5);

    mSprite->setTransformOriginPoint(mSprite->boundingRect().width()/2, mSprite->boundingRect().height()/2);
    g_size = QSize(w, h);

    // create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    bodyDef.position.Set(x, y);
    bodyDef.userData = (void *)udstruct;
    g_body = world->CreateBody(&bodyDef);
    g_body->SetFixedRotation(true);

    // define shape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(w, h);

    // define fixtures
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = BULLET_DENSITY;
    fixtureDef.friction = BULLET_FRICTION;
    fixtureDef.restitution = BULLET_RESTITUTION;
    fixtureDef.isSensor = true;
    g_body->CreateFixture(&fixtureDef);
    g_body->SetLinearDamping(2.0);

    // parse animation description
    parseAnimDescription(":/bullet_anim.json");

    // connect timer
    connect(timer, SIGNAL(timeout()), this, SLOT(paint()));

    scene->addItem(mSprite);
    startAnim("travel");
}

BulletWave::~BulletWave() {

}

void BulletWave::applyImpulse(b2Vec2 force) {
    g_body->ApplyLinearImpulse(force, g_body->GetWorldCenter(), true);
}

b2Vec2 BulletWave::getPosition() {
    return g_body->GetPosition();
}


