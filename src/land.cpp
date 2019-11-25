#include "land.h"

Land::Land(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world, false)
{
    // Set pixmap
    mSprite->setPixmap(pixmap);
    mSprite->setSubRegion(QRectF(0, 0, mSprite->boundingRect().width(), mSprite->boundingRect().height()));
    g_size = QSize(w,h);


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
