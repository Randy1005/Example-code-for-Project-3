#include "platform.h"

Platform::Platform(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    : GameItem(world, false)
{
    // Set pixmap
    mSprite->setPixmap(pixmap);
    mSprite->setSubRegion(QRectF(384, 32, 32, 16));
    g_size = QSize(w,h);

    // scale this subRegion
    mSprite->setScale(4.5);


    // Create body
    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);
    g_body->CreateFixture(&bodyBox,9.0f);

    scene->addItem(mSprite);
    paint();

}
