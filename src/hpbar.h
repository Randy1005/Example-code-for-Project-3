#ifndef HPBAR_H
#define HPBAR_H
#include <spriteitem.h>
#include <QGraphicsScene>
#include <QDebug>

class HPbar : public SpriteItem {

public:
    HPbar(int x, int y, QPixmap pixmap, QGraphicsScene *scene);
    void update(int hp);

    QGraphicsScene *scene;
};

#endif // HPBAR_H
