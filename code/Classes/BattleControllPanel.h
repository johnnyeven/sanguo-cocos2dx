#ifndef _BATTLE_CONTROLL_PANEL_H_
#define _BATTLE_CONTROLL_PANEL_H_
#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class BattleControllPanel :
	public Layer
{
public:
	CREATE_FUNC(BattleControllPanel);
	virtual bool init();
	virtual void onEnter();
	void run();
	void stop();

	std::function<void(Node*)> touchBeganCallback;
	std::function<void(Node*)> touchEndCallback;
	std::function<void(Node*)> touchMoveCallback;
private:
	BattleControllPanel(void);
	~BattleControllPanel(void);

	void onButtonTouched(Node* object, Widget::TouchEventType type);

	bool _isRunning;
	Button* btnNormalAttack;
};

#endif