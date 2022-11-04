#ifndef SESSION_H
#define SESSION_H

#include "table.h"

struct Session {
public:
    static Session& getSessionInstance();

private:
    Session();

    Session(const Session&) = delete;
    Session(Session&&) = delete;
    Session& operator=(const Session&) = delete;
    Session& operator=(Session&&) = delete;
};

#endif  // SESSION_H
