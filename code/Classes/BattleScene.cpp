#include "BattleScene.h"
#include "json/rapidjson.h"
#include "json/document.h"

BattleScene* BattleScene::_instance = nullptr;

USING_NS_CC;
using namespace rapidjson;

Scene* BattleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BattleScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

BattleScene* BattleScene::getInstance()
{
	if(!_instance)
	{
		_instance = BattleScene::create();
	}
	return _instance;
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
	loadRoleAnimation("images/roles/p1_s2/p1_s2.json");
	
	CCAnimate* animate = CCAnimate::create(CCAnimationCache::getInstance()->getAnimation("stand"));
	auto s = Sprite::create();
	addChild(s);
	s->setPosition(960 / 2, 640 / 2);
	s->runAction(CCRepeatForever::create(animate));
	
    return true;
}

bool BattleScene::loadRoleAnimation(const std::string& filename)
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
				if(doc.IsObject())
				{
					if(doc.HasMember("animations"))
					{
						const rapidjson::Value& animations = doc["animations"];
						if(animations.IsArray())
						{
							int size = animations.Size();
							for(int i = 0; i < size; ++i)
							{
								const rapidjson::Value& animation = animations[i];
								if(animation.IsObject() &&
									animation.HasMember("animateName") &&
									animation.HasMember("plistFilePath") &&
									animation.HasMember("frameTotal") &&
									animation.HasMember("delay") &&
									animation.HasMember("restoreOriginalFrame"))
								{
									//log("load %s", animation["animateName"].GetString());
									SpriteFrameCache::getInstance()->addSpriteFramesWithFile(animation["plistFilePath"].GetString());
									//log("plist %s", animation["plistFilePath"].GetString());
									CCAnimation* a = CCAnimation::create();
									std::string format = animation["fileFormat"].GetString();
									//log("format %s", format.c_str());
									for(int i = 0; i < (animation["frameTotal"].GetInt()); ++i)
									{
										a->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format.c_str(), i)));
										//log("add frame %s", StringUtils::format(format.c_str(), i).c_str());
									}
									a->setDelayPerUnit(animation["delay"].GetDouble());
									//log("delay %f", animation["delay"].GetDouble());
									a->setRestoreOriginalFrame(animation["restoreOriginalFrame"].GetBool());
									//log("restore %i", animation["restoreOriginalFrame"].GetBool());
									CCAnimationCache::getInstance()->addAnimation(a, animation["animateName"].GetString());
									//log("end %s\n", animation["animateName"].GetString());
								}
							}
						}
					}
					else
					{
						log("json format error.");
					}
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

	return false;
}
