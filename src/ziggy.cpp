#include "ziggy.h"

/**
 * @brief Ziggy::Ziggy
 * @param x
 * @param y
 * @param w
 * @param h
 * @param timer
 * @param pixmap
 * @param world
 * @param scene
 */
Ziggy::Ziggy(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
    GameItem(world, true), isJumping(false)
{
    spriteFlipped = false;

    // Set pixmap
    mSprite->setPixmap(pixmap);

    // set to first frame
    mSprite->setSubRegion(QRectF(0, 256, 16, 16));

    // scale sprite
    mSprite->setScale(5.2);

    mSprite->setTransformOriginPoint(mSprite->boundingRect().width()/2, mSprite->boundingRect().height()/2);
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
    g_body->SetLinearDamping(2.0);

    // parse animation description
    parseAnimDescription(":/ziggy_anim.json");

    // connect timer
    connect(timer, SIGNAL(timeout()), this, SLOT(paint()));

    scene->addItem(mSprite);
    startAnim("idle");

}

/**
 * @brief Ziggy::setLinearVelocity
 * set the velocity of this game item
 * @param velocity
 */
void Ziggy::setLinearVelocity(b2Vec2 velocity) {
    g_body->SetLinearVelocity(velocity);
}

/**
 * @brief Ziggy::applyImpulse
 * @param force
 */
void Ziggy::applyImpulse(b2Vec2 force) {
    g_body->ApplyLinearImpulse(force, g_body->GetWorldCenter(), true);
}


/**
 * @brief Ziggy::eventFilter
 * @param obj
 * @param event
 * @return
 */
bool Ziggy::eventFilter(QObject *obj, QEvent *event) {

    // may need a FSM here if we want more sophisticated animations

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Right) {
            setLinearVelocity(b2Vec2(8, 0));
            startAnim("move_right");
        } else if (keyEvent->key() == Qt::Key_Left) {
            setLinearVelocity(b2Vec2(-8, 0));
            startAnim("move_right");
        } else if (keyEvent->key() == Qt::Key_Up && !isJumping) {

        }

        return true;
    } else if (event->type() == QEvent::KeyRelease) {
        startAnim("idle");
    }

    return false;
}