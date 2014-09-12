#include "Monster.h"
#include "../behaviors/MonsterBehavior.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "RoleData.h"

using namespace rapidjson;

Monster::Monster(int id):Role(id)
{
    setBehavior(new MonsterBehavior());
}


Monster::~Monster(void)
{
}

Monster* Monster::create(int id)
{
    Monster *s = new (std::nothrow) Monster(id);
    if (s && s->init())
    {
        s->autorelease();
        return s;
    }
    CC_SAFE_DELETE(s);
    return nullptr;
}

Monster* Monster::createWithJson(const std::string& filename)
{
	if(filename.size() > 0)
	{
		Document doc;
		if(FileUtils::getInstance()->isFileExist(filename))
		{
			std::string json = FileUtils::getInstance()->getStringFromFile(filename);
			doc.Parse<rapidjson::kParseDefaultFlags>(json.c_str());
			if(!doc.HasParseError())
			{
				if(doc.HasMember("id") &&
					doc.HasMember("anchor") &&
					doc.HasMember("speed"))
				{
					rapidjson::Value& anchor = doc["anchor"];
					if(anchor.IsObject() &&
						anchor.HasMember("x") &&
						anchor.HasMember("y"))
					{
						Monster *s = new (std::nothrow) Monster(doc["id"].GetInt());
						if (s && s->init())
						{
							s->setData(new RoleData());
							s->setAnchorPoint(Vec2(anchor["x"].GetDouble(), anchor["y"].GetDouble()));
							s->setSpeed(doc["speed"].GetDouble());
							s->autorelease();
							return s;
						}
						CC_SAFE_DELETE(s);
					}
					else
					{
						log("json format error.");
					}
				}
				else
				{
					log("json format error.");
				}
			}
			else
			{
				log("GetParserError %s\n", doc.GetParseError());
			}
		}
		else
		{
			log("file not exist");
		}
	}

	return nullptr;
}

void Monster::setBehavior(MonsterBehavior* b)
{
    _behavior = b;
    _behavior->setTarget(this);
}

void Monster::update(float delta)
{
    Role::update(delta);
    
    if(_behavior)
    {
        _behavior->update(delta);
    }
}

void Monster::setAction(RoleAction value)
{
	if(_action != value)
	{
		if((value == RoleAction::ATTACK1 ||
			value == RoleAction::ATTACK2) &&
			(_action == RoleAction::ATTACK1 ||
			_action == RoleAction::ATTACK2))
		{
			return;
		}
		stopAllActions();
		_action = value;
		int index = (int)value;
		std::string name = StringUtils::format("%i_%s", getId(), GlobalConfig::action[index].c_str());
		CCAnimate* animate = CCAnimate::create(CCAnimationCache::getInstance()->getAnimation(name));
		if(index < 4)
		{
			runAction(CCRepeatForever::create(animate));
		}
		else
		{
			runAction(CCSequence::create(animate, CallFunc::create(CC_CALLBACK_0(Monster::restoreOriginalAnimation, this)), NULL));
		}
	}
}

void Monster::restoreOriginalAnimation()
{
	setAction(RoleAction::STAND);
}