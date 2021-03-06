#include "Hero.h"
#include "../behaviors/HeroBehavior.h"


Hero::Hero(int id):Role(id)
{
    setBehavior(new HeroBehavior());
}


Hero::~Hero(void)
{
}

Hero* Hero::create(int id)
{
    Hero *s = new (std::nothrow) Hero(id);
    if (s && s->init())
    {
        s->autorelease();
        return s;
    }
    CC_SAFE_DELETE(s);
    return nullptr;
}

void Hero::setBehavior(HeroBehavior* b)
{
    _behavior = b;
    _behavior->setTarget(this);
}

void Hero::update(float delta)
{
    Role::update(delta);
    
    if(_behavior)
    {
        _behavior->update(delta);
    }
}