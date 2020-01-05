#include "contactlistener.h"


std::vector<GameItem *> ContactListener::itemsScheduledForRemoval;

ContactListener::ContactListener(std::vector<GameItem *> itemList)
    : item_list(itemList)
{
    slimeSFX = new QMediaPlayer();
    slimeSFX->setMedia(QUrl("qrc:/sounds/hurt.mp3"));
}

void ContactListener::BeginContact(b2Contact *contact) {
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();

    if (fixtureA == nullptr || fixtureB == nullptr) return;
    if (fixtureA->GetBody()->GetUserData() == nullptr || fixtureB->GetBody()->GetUserData() == nullptr) return;

    udStruct *udstructA = static_cast<udStruct *>(fixtureA->GetBody()->GetUserData());
    udStruct *udstructB = static_cast<udStruct *>(fixtureB->GetBody()->GetUserData());




    if ((udstructA->id == ZIGGY_ID && udstructB->id == SLIME_ID) ||
        (udstructB->id == ZIGGY_ID && udstructA->id == SLIME_ID)) {
        /**
          ziggy / slime contact
          */
        if (udstructA->id == ZIGGY_ID) {
            Ziggy *zig = static_cast<Ziggy *>(udstructA->charactePtr);
            Slime *sli = static_cast<Slime *>(udstructB->charactePtr);
            zig->HPDecrement();

            float32 bounceVec = (zig->getPosition()-sli->getPosition()).x;
            zig->applyImpulse(b2Vec2(bounceVec * 200, 0));

        } else if (udstructB->id == SLIME_ID) {
            Ziggy *zig = static_cast<Ziggy *>(udstructB->charactePtr);
            Slime *sli = static_cast<Slime *>(udstructA->charactePtr);
            zig->HPDecrement();

            float32 bounceVec = (zig->getPosition()-sli->getPosition()).x;
            zig->applyImpulse(b2Vec2(bounceVec * 200, 0));
        }
    } else if ((udstructA->id == BULLET_ID && udstructB->id == SLIME_ID) ||
               (udstructB->id == BULLET_ID && udstructA->id == SLIME_ID)) {
        /**
          bullet / slime contact
          */

        if (slimeSFX->state() == QMediaPlayer::PlayingState) {
            slimeSFX->setPosition(0);
        } else if (slimeSFX->state() == QMediaPlayer::StoppedState) {
            slimeSFX->play();
        }


        if (udstructA->id == BULLET_ID) {
            BulletWave *bw = static_cast<BulletWave *>(udstructA->charactePtr);
            Slime *sli = static_cast<Slime *>(udstructB->charactePtr);
            itemsScheduledForRemoval.push_back(sli);
            itemsScheduledForRemoval.push_back(bw);


        } else if (udstructB->id == BULLET_ID) {
            BulletWave *bw = static_cast<BulletWave *>(udstructB->charactePtr);
            Slime *sli = static_cast<Slime *>(udstructA->charactePtr);
            itemsScheduledForRemoval.push_back(sli);

        }
    }




}

void ContactListener::EndContact(b2Contact *contact) {
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();

    if (fixtureA == nullptr || fixtureB == nullptr) return;
    if (fixtureA->GetBody()->GetUserData() == nullptr || fixtureB->GetBody()->GetUserData() == nullptr) return;
}




