#include "debugdraw.h"

DebugDraw::DebugDraw(QGraphicsScene *scene) : scene(scene)
{

}

void DebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {

    QPolygonF poly;
    for (int i = 0; i < vertices->Length(); i++) {
        poly << QPointF(vertices[i].x, vertices[i].y);
    }

    QBrush brush;
    brush.setColor(Qt::green);
    QPen pen(Qt::green);

    scene->addPolygon(poly, pen, brush);
    scene->update();

}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {

    qDebug() << "draw call";
}


void DebugDraw::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) {

}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) {

}

void DebugDraw::DrawTransform(const b2Transform &xf) {

}

