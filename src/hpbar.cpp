#include "hpbar.h"

HPbar::HPbar(int x, int y, QPixmap pixmap, QGraphicsScene *scene)
    : scene(scene)
{
    setPixmap(pixmap);
    setPos(x, y);
    scene->addItem(this);
    setSubRegion(QRectF(0, 0, 630, 390));
}

void HPbar::update(int hp) {
    setPos(scene->sceneRect().left()+10, scene->sceneRect().top());
    setSubRegion(QRectF(0, 0, (float)630 * (hp/50.0), 390));

}

