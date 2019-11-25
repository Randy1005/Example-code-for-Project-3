#include "spriteitem.h"
#include <QPainter>

SpriteItem::SpriteItem()
{

}

void SpriteItem::setPixmap(const QPixmap &pixmap) {
    m_pixmap = pixmap;
    m_boundingRect = pixmap.rect();
}

QRectF SpriteItem::boundingRect() const {
    return m_boundingRect;
}

void SpriteItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(m_target, m_pixmap, m_source);
}

void SpriteItem::setSubRegion(QRectF rect) {
    QRectF pixmapRect = m_pixmap.rect();

    if (pixmapRect.contains(rect)) {
        m_source = rect;
        m_target = QRectF(0, 0, rect.width(), rect.height());
        m_boundingRect = m_target;
        update();
    } else {

    }
}
