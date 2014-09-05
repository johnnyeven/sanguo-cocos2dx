#include "Hero.h"


Hero::Hero(void):Role()
{
}


Hero::~Hero(void)
{
}

Hero* Hero::create()
{
    Hero *s = new (std::nothrow) Hero();
    if (s && s->init())
    {
        s->autorelease();
        return s;
    }
    CC_SAFE_DELETE(s);
    return nullptr;
}