#pragma once

class Killable {
public:
    inline Killable(): alive(true) {}

    inline bool isAlive() const { return alive; }
    inline void kill() { alive = false; } 
protected:
    bool alive;
};