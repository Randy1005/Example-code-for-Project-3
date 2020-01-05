#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H
#include <Box2D/Box2D.h>
#include <QDebug>
#include <ziggy.h>
#include <bulletwave.h>
#include <slime.h>



class ContactListener : public b2ContactListener
{
public:
    ContactListener(std::vector<GameItem *> itemList);
    virtual void BeginContact(b2Contact *contact) override;
    virtual void EndContact(b2Contact *contact) override;

    static std::vector<GameItem *> itemsScheduledForRemoval;

    std::vector<GameItem *> item_list;
    QMediaPlayer *slimeSFX;
};



#endif // CONTACTLISTENER_H
