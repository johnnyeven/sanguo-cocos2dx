#ifndef __BATTLESCENE_H__
#define __BATTLESCENE_H__

#include "cocos2d.h"
class Joystick;
class Hero;
class BattleRoundData;

USING_NS_CC;

class BattleScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	static BattleScene* getInstance();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void update(float delta);
    virtual void onEnter();

	void loadMapConfig(const std::string&);
    bool loadMap(const std::string&);
	void loadRound(int round);
	void updateMap(float delta);
	bool loadRoleAnimation(const std::string&);
    float getMapWidth() { return _mapWidth; };
    float getMapHeight() { return _mapHeight; };
    void setPlayer(Hero*);
    Hero* getPlayer() { return _player; };
	Rect* getLimitArea() { return _limitArea; };
	Point getScreenPosition(float x, float y) const;
	void addDisplay(Sprite*);
	void removeDisplay(Sprite*);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BattleScene);
private:
	static BattleScene* _instance;
    Hero* _player;
    std::string* _currentMapId;
	std::vector<BattleRoundData*> _mapRounds;
	int _mapCurrentRound;
    float _mapWidth;
	float _mapHeight;
    float _roleStartX;
    float _roleStartY;
	Rect* _limitArea;
    Layer* _backgroundLayer;
	Layer* _midgroundLayer;
	Layer* _characterLayer;
    Layer* _foregroundLayer;
	Vector<Sprite*> _displayList;

	void onBattleControlTouchBegan(Ref* object);
};

#endif // __BATTLESCENE_H__
