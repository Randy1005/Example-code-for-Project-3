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
#include <spriteitem.h>

class GameItem : public QObject
{
    Q_OBJECT
public:
    GameItem(b2World *world, bool animated);
    ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);
    void parseAnimDescription(QString);
    void startAnim(QString);
    void setSubrect(QRect);

    // character json animation description
    QJsonObject chrJsonObj;
    QJsonDocument chrJsonDoc;


    // sprite subrect
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
    bool g_animated;
    bool spriteFlipped;
    b2Body *g_body;
    SpriteItem *mSprite;
    QSizeF g_size;
    b2World *g_world;
    static QSizeF g_worldsize, g_windowsize;
};

#endif // GAMEITEM_H
