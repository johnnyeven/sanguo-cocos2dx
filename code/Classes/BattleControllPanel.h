#ifndef _BATTLE_CONTROLL_PANEL_H_
#define _BATTLE_CONTROLL_PANEL_H_
#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class Joystick;
class BattleControllPanel :
	public Layer
{
public:
    static BattleControllPanel* getInstance();
	CREATE_FUNC(BattleControllPanel);
	virtual bool init();
	virtual void onEnter();
	void run();
	void stop();
	Joystick* getJoystick() { return _joystick; };

	std::function<void(Ref*)> touchBeganCallback;
	std::function<void(Ref*)> touchEndCallback;
	std::function<void(Ref*)> touchMoveCallback;
private:
	BattleControllPanel(void);
	~BattleControllPanel(void);

	void onButtonTouched(Ref* object, Widget::TouchEventType type);

	virtual void onTouchesBegan(std::vector<Touch*>, Event*);
	virtual void onTouchesMoved(std::vector<Touch*>, Event*);
	virtual void onTouchesEnded(std::vector<Touch*>, Event*);

    static BattleControllPanel* _instance;
	bool _isRunning;
    Joystick* _joystick;
	Button* btnNormalAttack;
    EventListenerTouchOneByOne* btnNormalAttackListener;
};

#endif