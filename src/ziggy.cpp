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
    GameItem(world, true), isSwingingSword(false), tmr(timer), world(world), scene(scene)
{

    HP = 50;
    bulletWaveSFX = new QMediaPlayer();
    bulletWaveSFX->setMedia(QUrl("qrc:/sounds/pew.wav"));
    oofSFX = new QMediaPlayer();
    oofSFX->setMedia(QUrl("qrc:/sounds/oof.wav"));

    // define userDataStruct
    udstruct = new udStruct;
    udstruct->id = 999;
    udstruct->charactePtr = this;

    spriteFlipped = false;

    // new HP bar
    hpbar = new HPbar(scene->sceneRect().left()+10,
                      scene->sceneRect().top(),
                      QPixmap(":/sprites/hpbar.png"),
                      scene);


    // Set pixmap
    mSprite->setPixmap(pixmap);

    // set to first frame
    mSprite->setSubRegion(QRectF(0, 256, 16, 16));

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

Ziggy::~Ziggy() {
    g_world->DestroyBody(g_body);
    scene->removeItem(mSprite);
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

b2Vec2 Ziggy::getPosition() {
    return g_body->GetPosition();
}

HPbar* Ziggy::getHPBar() {
    return hpbar;
}


int Ziggy::getHP() {
    return HP;
}

void Ziggy::fire() {
    BulletWave *newBullet = new BulletWave(this->getPosition().x, this->getPosition().y, 0.15f, 0.15f, tmr, QPixmap(":/sprites/industrial.v2.png"), world, scene);
    newBullet->applyImpulse(b2Vec2(4, 0));

    if (bulletWaveSFX->state() == QMediaPlayer::PlayingState) {
        bulletWaveSFX->setPosition(0);
    } else if (bulletWaveSFX->state() == QMediaPlayer::StoppedState) {
        bulletWaveSFX->play();
    }
}

void Ziggy::HPDecrement() {
    HP-=5;
    if (oofSFX->state() == QMediaPlayer::PlayingState) {
        oofSFX->setPosition(0);
    } else if (oofSFX->state() == QMediaPlayer::StoppedState) {
        oofSFX->play();
    }

    if (HP < 0) {
        HP = 50;
    }
}

/**
 * @brief Ziggy::eventFilter
 * @param obj
 * @param event
 * @return
 */
bool Ziggy::eventFilter(QObject *obj, QEvent *event) {
    Q_UNUSED(obj)


    // may need a FSM here if we want more sophisticated animations
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Right) {
            setLinearVelocity(b2Vec2(8, 0));
            startAnim("move_right");
        } else if (keyEvent->key() == Qt::Key_Left) {
            setLinearVelocity(b2Vec2(-8, 0));
            startAnim("move_right");
        } else if (keyEvent->key() == Qt::Key_Up){
            applyImpulse(b2Vec2(0, 200));
        } else if (keyEvent->key() == Qt::Key_Space) {
            startAnim("attack");
            isSwingingSword = true;
        } else if (keyEvent->key() == Qt::Key_S) {
            startAnim("hadouken");
            fire();
        }

        return true;
    } else if (event->type() == QEvent::KeyRelease) {
        startAnim("idle");
        isSwingingSword = false;
        return true;
    }

    return false;
}
