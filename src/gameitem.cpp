#include "gameitem.h"

#include <iostream>
#include <QDebug>

GameItem::GameItem(b2World *world, bool animated):
    g_body(NULL),g_world(world), g_animated(animated)
{
    mSprite = new SpriteItem();
}

GameItem::~GameItem()
{
    g_world->DestroyBody(g_body);
}

QSizeF GameItem::g_windowsize = QSizeF();
QSizeF GameItem::g_worldsize = QSizeF();

void GameItem::setGlobalSize(QSizeF worldsize, QSizeF windowsize)
{
    g_worldsize = worldsize;
    g_windowsize = windowsize;
}

void GameItem::paint()
{
    b2Vec2 pos = g_body->GetPosition();
    QPointF mappedPoint;
    mappedPoint.setX(((pos.x-g_size.width()/2) * g_windowsize.width())/g_worldsize.width());
    mappedPoint.setY((1.0f - (pos.y+g_size.height()/2)/g_worldsize.height()) * g_windowsize.height());
    mSprite->setPos(mappedPoint);
    mSprite->resetTransform();
    mSprite->setRotation(-(g_body->GetAngle()*180/3.14159));

    // parse current animation object, assign to mCurrentAnimation
    // and increment frame index
    if (g_animated) {
        foreach(const QJsonValue &val, animsArr) {
            QJsonObject obj = val.toObject();
            if (obj["animName"].toString() == mAnimName) {
                if (mCurrFrame < obj["animFrames"].toArray().size()) {
                    ++mCurrFrame;
                } else {
                    mCurrFrame = 0;
                }

                mCurrAnim = obj["animFrames"].toArray().at(mCurrFrame).toObject();

                // update mSubRect
                mSubRectArr = mCurrAnim["rect"].toArray();

                // update sprite image item (custom QGraphicsPixmapitem class)
                // partially draw image
                mSprite->setSubRegion(QRectF(mSubRectArr.at(0).toInt(),
                                             mSubRectArr.at(1).toInt(),
                                             mSubRectArr.at(2).toInt(),
                                             mSubRectArr.at(3).toInt()));
                if (spriteFlipped) mSprite->setTransform(QTransform::fromScale(-1, 1));


            }
        }
    }
}


/**
 * @brief GameItem::setSubrect
 * set new subrect on spritesheet
 * @param newRect
 */
void GameItem::setSubrect(QRect newRect) {
    mSubRect = newRect;
}

/**
 * @brief GameItem::parseAnimDescription
 * parse json file and store character sprite animation info
 * @param filename
 */
void GameItem::parseAnimDescription(QString filename) {
    // convert JSON file to object
    QFile jsonfile;
    jsonfile.setFileName(filename);
    jsonfile.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonParseError jsonError;
    QString val = jsonfile.readAll();
    chrJsonDoc = QJsonDocument::fromJson(val.toUtf8(), &jsonError);
    if (jsonError.error) {
        qWarning() << jsonError.errorString();
        return;
    }
    jsonfile.close();

    chrJsonObj = chrJsonDoc.object();

    // parse animation descriptions
    QJsonArray chrJsonArr = chrJsonObj["behaviors"].toArray();
    foreach (const QJsonValue &val, chrJsonArr) {
        QJsonObject obj = val.toObject();
        if (obj["name"].toString() == "SpriteAnimationBehavior") {
            animsArr = obj["params"].toObject()["anims"].toArray();
        }
    }
}

/**
 * @brief GameItem::startAnim
 * change the current animation,
 * update the current sub-rect to draw to match the first frame of the new animation
 * @param animName
 */

void GameItem::startAnim(QString animName) {
    mAnimName = animName;

    // parse current animation object, assign to mCurrentAnimation
    foreach(const QJsonValue &val, animsArr) {
        QJsonObject obj = val.toObject();
        if (obj["animName"].toString() == animName) {
            mCurrAnim = obj["animFrames"].toArray().at(mCurrFrame).toObject();
        }
    }

    // assign to mSubRect
    mSubRectArr = mCurrAnim["rect"].toArray();
    mSubRect = QRect(mSubRectArr.at(0).toInt(),
                     mSubRectArr.at(1).toInt(),
                     mSubRectArr.at(2).toInt(),
                     mSubRectArr.at(3).toInt());

}
