#ifndef PLATFORM_H
#define PLATFORM_H
#include <gameitem.h>
#include <QGraphicsScene>

class Platform : public GameItem
{
public:
    Platform(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // PLATFORM_H
