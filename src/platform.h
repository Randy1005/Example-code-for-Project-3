#ifndef PLATFORM_H
#define PLATFORM_H
#include <gameitem.h>
#include <QGraphicsScene>
#include <commonInfo.h>

class Platform : public GameItem
{
public:
    Platform(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

protected:
    udStruct *udstruct;

};

#endif // PLATFORM_H
