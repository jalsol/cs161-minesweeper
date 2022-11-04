#include "session.h"

Session& Session::getSessionInstance() {
    static Session session;
    return session;
}

Session::Session() {}
