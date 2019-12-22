#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H
#include <Box2D/Box2D.h>
#include <QDebug>


class ContactListener : public b2ContactListener
{
public:
    ContactListener();
    virtual void BeginContact(b2Contact *contact) override;
    virtual void EndContact(b2Contact *contact) override;
};

#endif // CONTACTLISTENER_H
