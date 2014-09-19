#include "BattleScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "Joystick.h"
#include "Camera.h"
#include "BattleControllPanel.h"
#include "characters/Hero.h"
#include "characters/Monster.h"
#include "characters/RoleData.h"
#include "BattleRoundData.h"
#include "BattleMonsterData.h"
#include "behaviors/MonsterBehavior.h"
#include "behaviors/ai/AIAutoTrack.h"
#include "behaviors/ai/AIAutoAttackActive.h"

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
    srand(time(0));
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
	_displayList = Vector< Sprite* >();
	_teamMap = std::map< int, std::vector< Role* > >();
	_mapRounds = std::vector< BattleRoundData* >();

    return true;
}

void BattleScene::onEnter()
{
    Layer::onEnter();

	BattleControllPanel* control = BattleControllPanel::getInstance();
	addChild(control);
	control->touchBeganCallback = CC_CALLBACK_1(BattleScene::onBattleControlTouchBegan, this);
	control->run();

	loadRoleAnimation("images/roles/1001/1001.json");
    loadMapConfig("config/maps/1001.json");
	loadRound(0);
    
    auto s = Hero::create(1001);
	s->setTeam(RoleTeam::PLAYER);
	addDisplay(s);
	s->setData(new RoleData());
    s->setAnchorPoint(Vec2(.5f, .35f));
	s->setSpeed(300.f);
	s->setWorldPosition(_roleStartX, _roleStartY);
    s->setAction(RoleAction::WAIT);
    setPlayer(s);
	
    SceneCamera::getInstance()->focusOn(_player);
    scheduleUpdate();
}

void BattleScene::update(float delta)
{
    Layer::update(delta);
    
    SceneCamera::getInstance()->update(delta);
	updateMap(delta);

	for(Sprite* r : _displayList)
	{
		r->update(delta);
	}

	auto camera = SceneCamera::getInstance();
}

void BattleScene::updateMap(float delta)
{
	auto camera = SceneCamera::getInstance();
	Point start = camera->getStart();
//	log("x=%f, y=%f", start.x, start.y);

	_backgroundLayer->setPosition(-start.x * BACKGROUND_OFFSETRATE, -start.y);
	_midgroundLayer->setPosition(-start.x, -start.y);
	_foregroundLayer->setPosition(-start.x * FOREGROUND_OFFSETRATE, -start.y);
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
                    doc.HasMember("maxY") &&
                    doc.HasMember("startX") &&
                    doc.HasMember("startY") &&
					doc.HasMember("rounds"))
				{
					_mapWidth = doc["width"].GetDouble();
					_mapHeight = doc["height"].GetDouble();
                    _roleStartX = doc["startX"].GetDouble();
                    _roleStartY = doc["startY"].GetDouble();
					float minY = doc["minY"].GetDouble();
					float maxY = doc["maxY"].GetDouble();
					_limitArea->setRect(0, minY, _mapWidth, maxY - minY);
					loadMap(doc["plistFile"].GetString());

					//rounds
					rapidjson::Value& rounds = doc["rounds"];
					if(rounds.IsArray())
					{
						for(int i = 0; i < rounds.Size(); ++i)
						{
							rapidjson::Value& round = rounds[i];
							if(round.IsObject() &&
								round.HasMember("limitArea") &&
								round.HasMember("monsters"))
							{
								BattleRoundData* roundData = new BattleRoundData();
								rapidjson::Value& limitArea = round["limitArea"];
								rapidjson::Value& monsters = round["monsters"];

								if(limitArea.IsObject() &&
									limitArea.HasMember("x") &&
									limitArea.HasMember("y") &&
									limitArea.HasMember("width") &&
									limitArea.HasMember("height"))
								{
									roundData->limitArea.setRect(
										limitArea["x"].GetDouble(),
										limitArea["y"].GetDouble(),
										limitArea["width"].GetDouble(),
										limitArea["height"].GetDouble());
								}

								if(monsters.IsArray())
								{
									for(int j = 0; j < monsters.Size(); ++j)
									{
										rapidjson::Value& monster = monsters[j];
										if(monster.IsObject() &&
											monster.HasMember("id") &&
											monster.HasMember("count") &&
											monster.HasMember("x") &&
											monster.HasMember("y") &&
											monster.HasMember("flipX"))
										{
											BattleMonsterData* monsterData = new BattleMonsterData(
												monster["id"].GetInt(),
												monster["count"].GetInt(),
												monster["x"].GetDouble(),
												monster["y"].GetDouble(),
												monster["flipX"].GetBool());

											roundData->monsters.push_back(monsterData);
										}
									}
								}

								_mapRounds.push_back(roundData);
							}
						}
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
        Size s = hou->getContentSize();
        int w = (int)ceilf(_mapWidth * BACKGROUND_OFFSETRATE / s.width);
        for(int i = 1; i < w; ++i)
        {
            auto hou = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("hou.png"));
            hou->setAnchorPoint(Vec2(0.f, 0.f));
            hou->setPosition(i * s.width, 0);
            _backgroundLayer->addChild(hou);
        }
        
        auto zhong = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("zhong.png"));
        zhong->setAnchorPoint(Vec2(0.f, 0.f));
        _midgroundLayer->addChild(zhong);
        s = zhong->getContentSize();
        w = (int)ceilf(_mapWidth / s.width);
        for(int i = 1; i < w; ++i)
        {
            auto zhong = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("zhong.png"));
            zhong->setAnchorPoint(Vec2(0.f, 0.f));
            zhong->setPosition(i * s.width, 0);
            _midgroundLayer->addChild(zhong);
        }
        
        auto qian = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("qian.png"));
        qian->setAnchorPoint(Vec2(0.f, 0.f));
        _foregroundLayer->addChild(qian);
        s = qian->getContentSize();
        w = (int)ceilf(_mapWidth * FOREGROUND_OFFSETRATE / s.width);
        for(int i = 1; i < w; ++i)
        {
            auto qian = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("qian.png"));
            qian->setAnchorPoint(Vec2(0.f, 0.f));
            qian->setPosition(i * s.width, 0);
            _foregroundLayer->addChild(qian);
        }
        
        return true;
    }
    return false;
}

void BattleScene::loadRound(int round)
{
	if(round < _mapRounds.size())
	{
		_mapCurrentRound = round;
		BattleRoundData* roundData = _mapRounds.at(_mapCurrentRound);
		if(roundData)
		{
			Rect area = roundData->limitArea;
			_limitArea->setRect(
				area.getMinX(),
				area.getMinY(),
				area.getMaxX() - area.getMinX(),
				area.getMaxY() - area.getMinY());

			for(int i = 0; i < roundData->monsters.size(); ++i)
			{
				BattleMonsterData* monsterData = roundData->monsters.at(i);
				if(monsterData)
				{
					loadRoleAnimation(StringUtils::format("images/roles/%i/%i.json", monsterData->id, monsterData->id));

					auto m = Monster::createWithJson(StringUtils::format("config/monsters/%i.json", monsterData->id));
					auto b = new MonsterBehavior();
					b->addAI(new AIAutoTrack(998));
					b->addAI(new AIAutoAttackActive(999));
					m->setBehavior(b);
					m->setTeam(RoleTeam::MONSTER);
					addDisplay(m);
					m->setWorldPosition(monsterData->x, monsterData->y);
					m->setAction(RoleAction::STAND);
					m->setFlippedX(monsterData->flipX);
				}
			}
		}
	}
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

void BattleScene::addDisplay(Sprite* obj)
{
	int index = _displayList.getIndex(obj);
	if(index < 0)
	{
		_displayList.pushBack(obj);
		if(dynamic_cast<Role*>(obj))
		{
			Role* role = dynamic_cast<Role*>(obj);
			_characterLayer->addChild(role);

			int team = role->getTeam();
			std::map< int, std::vector< Role* > >::iterator it = _teamMap.find(team);
			if(it == _teamMap.end())
			{
				std::vector< Role* > tmpList = std::vector< Role* >();
				tmpList.push_back(role);
				_teamMap.insert(std::map< int, std::vector< Role* > >::value_type(team, tmpList));
			}
			else
			{
				std::vector< Role* >* tmpList = &it->second;
				tmpList->push_back(role);
			}
		}
	}
}

void BattleScene::removeDisplay(Sprite* obj)
{
	int index = _displayList.getIndex(obj);
	if(index >= 0)
	{
		_displayList.erase(index);
		if(dynamic_cast<Role*>(obj))
		{
			Role* role = dynamic_cast<Role*>(obj);
			_characterLayer->removeChild(role);
			
			int team = role->getTeam();
			std::map< int, std::vector< Role* > >::iterator it = _teamMap.find(team);
			if(it != _teamMap.end())
			{
				std::vector< Role* > tmpList = it->second;
				std::vector< Role* >::iterator i = std::find(tmpList.begin(), tmpList.end(), role);
				if(i != tmpList.end())
				{
					tmpList.erase(i);
					if(tmpList.size() == 0)
					{
						_teamMap.erase(it);
					}
				}
			}
		}
	}
}

Point BattleScene::getScreenPosition(float x, float y) const
{
	Point start = SceneCamera::getInstance()->getStart();
	return Point(
		x - start.x,
		y - start.y);
}

void BattleScene::onBattleControlTouchBegan(Ref* object)
{
	int i = rand() % 5 + 4;
	_player->setAction(RoleAction(i));
}