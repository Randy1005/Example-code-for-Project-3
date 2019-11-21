#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

class GameItem : public QObject
{
    Q_OBJECT
public:
    GameItem(b2World *world);
    ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);
    void parseAnimDescription(QString);
    void setSubrect(QRect);

    // character json description
    QJsonObject chrJsonObj;
    QJsonDocument chrJsonDoc;


    // sprite subrect / sprite origin
    QRect mSubRect;

    // current animation / frame / subrect json array
    QJsonObject mCurrAnim;
    QJsonArray animsArr;
    QJsonArray mSubRectArr;

    QString mAnimName;
    int mCurrFrame;

public slots:
    void paint();
    // TODO virtual void collide();

protected:
    b2Body *g_body;
    QGraphicsPixmapItem g_pixmap;
    QSizeF g_size;
    b2World *g_world;
    static QSizeF g_worldsize, g_windowsize;
};

#endif // GAMEITEM_H
