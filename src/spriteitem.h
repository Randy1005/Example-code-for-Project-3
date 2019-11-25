#ifndef SPRITEITEM_H
#define SPRITEITEM_H
#include <QGraphicsPixmapItem>

class SpriteItem : public QGraphicsPixmapItem
{
public:
    SpriteItem();
    void setPixmap(const QPixmap &pixmap);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setSubRegion(QRectF rect);

protected:
    QPixmap m_pixmap;
    QRectF m_boundingRect;
    QRectF m_target;
    QRectF m_source;
};

#endif // SPRITEITEM_H
