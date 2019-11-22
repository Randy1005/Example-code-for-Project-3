#ifndef SPRITEITEM_H
#define SPRITEITEM_H
#include <QGraphicsPixmapItem>

class SpriteItem : public QGraphicsPixmapItem
{
public:
    SpriteItem();
    void setPixmap(const QPixmap pixmap);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setSubRegion(QRect rect);
};

#endif // SPRITEITEM_H
