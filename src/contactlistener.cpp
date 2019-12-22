#include "contactlistener.h"

ContactListener::ContactListener()
{

}

void ContactListener::BeginContact(b2Contact *contact) {
    qDebug() << "begin::fixture A: " << contact->GetFixtureA()->GetBody()->GetUserData();
    qDebug() << "begin::fixture B: " << contact->GetFixtureB()->GetBody()->GetUserData();
}

void ContactListener::EndContact(b2Contact *contact) {
    qDebug() << "begin::fixture A: " << contact->GetFixtureA()->GetBody()->GetUserData();
    qDebug() << "begin::fixture B: " << contact->GetFixtureB()->GetBody()->GetUserData();
}
