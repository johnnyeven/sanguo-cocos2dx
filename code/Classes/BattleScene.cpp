#include "BattleScene.h"
#include "characters/Hero.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "Joystick.h"
#include "Camera.h"
#include "characters/Hero.h"

BattleScene* BattleScene::_instance = nullptr;

USING_NS_CC;
using namespace rapidjson;

Scene* BattleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BattleScene::getInstance();
    SceneCamera::getInstance()->setScene(layer);

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
    
    _backgroundLayer = Layer::create();
    addChild(_backgroundLayer);
	_midgroundLayer = Layer::create();
	addChild(_midgroundLayer);
	_characterLayer = Layer::create();
	addChild(_characterLayer);
    _foregroundLayer = Layer::create();
    addChild(_foregroundLayer);
	_currentMapId = new std::string();
	_limitArea = new Rect(0, 0, 0, 0);
    
    return true;
}

void BattleScene::onEnter()
{
    Layer::onEnter();
	
//	srand(time(0));
	loadRoleAnimation("images/roles/p1_s2/p1_s2.json");
//
//    for(int i = 0; i < 20; ++i)
//    {
//        auto s = Hero::create();
//        addChild(s);
//        s->setPosition(rand() % 960, rand() % 640);
//        s->setAction(RoleAction::RUN);
//    }
	
	/*
	CCAnimate* animate = CCAnimate::create(CCAnimationCache::getInstance()->getAnimation("wait"));
	auto s = Sprite::create();
	addChild(s);
	s->setPosition(960 / 2, 640 / 2);
	s->runAction(Sequence::create(animate, NULL));
	*/
    
    loadMapConfig("images/maps/1001.json");
    _mapWidth = 4000.f;
    _mapHeight = 640.f;
    
    _joystick = Joystick::create("images/dPadTouchBg2.png", "images/dPadTouchBtn2.png");
    addChild(_joystick);
    _joystick->setPosition(Vec2(150,150));//設置初始位置
    _joystick->setFailRadius(30);
    _joystick->onRun();
    
    auto s = Hero::create();
    _characterLayer->addChild(s);
	s->setSpeed(250.f);
	s->setWorldPosition(960 / 2, 640 / 2);
    s->setPosition(960 / 2, 640 / 2);
    s->setAction(RoleAction::STAND);
    setPlayer(s);
	
    SceneCamera::getInstance()->focusOn(_player);
    scheduleUpdate();
}

void BattleScene::update(float delta)
{
    Layer::update(delta);
    
    SceneCamera::getInstance()->update(delta);
	updateMap(delta);

	if(_player)
	{
		_player->update(delta);
	}

	auto camera = SceneCamera::getInstance();
}

void BattleScene::updateMap(float delta)
{
	auto camera = SceneCamera::getInstance();
	Point start = camera->getStart();
	log("x=%f, y=%f", start.x, start.y);

	_backgroundLayer->setPosition(-start.x, -start.y);
	_midgroundLayer->setPosition(-start.x, -start.y);
	_foregroundLayer->setPosition(-start.x, -start.y);
}

void BattleScene::loadMapConfig(const std::string& filename)
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
				if(doc.IsObject() && doc.HasMember("plistFile") &&
					doc.HasMember("width") &&
					doc.HasMember("height") &&
					doc.HasMember("minY") &&
					doc.HasMember("maxY"))
				{
					_mapWidth = doc["width"].GetDouble();
					_mapHeight = doc["height"].GetDouble();
					float minY = doc["minY"].GetDouble();
					float maxY = doc["maxY"].GetDouble();
					_limitArea->setRect(0, minY, _mapWidth, maxY - minY);
					loadMap(doc["plistFile"].GetString());
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
}

bool BattleScene::loadMap(const std::string& id)
{
    if(id.size() > 0)
    {
        auto cache = SpriteFrameCache::getInstance();
        if (_currentMapId && _currentMapId->size() > 0)
        {
            cache->removeSpriteFramesFromFile(*_currentMapId);
        }
        else
        {
            _currentMapId = new std::string();
        }
        cache->addSpriteFramesWithFile(id);
        _currentMapId->assign(id);
        
        auto hou = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("hou.png"));
        hou->setAnchorPoint(Vec2(0.f, 0.f));
        _backgroundLayer->addChild(hou);
        auto zhong = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("zhong.png"));
        zhong->setAnchorPoint(Vec2(0.f, 0.f));
        _midgroundLayer->addChild(zhong);
        auto qian = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("qian.png"));
        qian->setAnchorPoint(Vec2(0.f, 0.f));
        _foregroundLayer->addChild(qian);
        
        return true;
    }
    return false;
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
									log("load %s", animation["animateName"].GetString());
									SpriteFrameCache::getInstance()->addSpriteFramesWithFile(animation["plistFilePath"].GetString());
									log("plist %s", animation["plistFilePath"].GetString());
									CCAnimation* a = CCAnimation::create();
									std::string format = animation["fileFormat"].GetString();
									log("format %s", format.c_str());
									for(int i = 0; i < (animation["frameTotal"].GetInt()); ++i)
									{
										a->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format.c_str(), i)));
										log("add frame %s", StringUtils::format(format.c_str(), i).c_str());
									}
									a->setDelayPerUnit(animation["delay"].GetDouble());
									log("delay %f", animation["delay"].GetDouble());
									a->setRestoreOriginalFrame(animation["restoreOriginalFrame"].GetBool());
									log("restore %i", animation["restoreOriginalFrame"].GetBool());
									CCAnimationCache::getInstance()->addAnimation(a, animation["animateName"].GetString());
									log("end %s\n", animation["animateName"].GetString());
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

void BattleScene::setPlayer(Hero *value)
{
    _player = value;
}

Point& BattleScene::getScreenPosition(float x, float y)
{
	Point start = SceneCamera::getInstance()->getStart();
	return Point(
		x - start.x,
		x - start.y);
}
