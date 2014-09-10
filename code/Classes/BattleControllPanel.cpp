#include "BattleControllPanel.h"


BattleControllPanel::BattleControllPanel(void)
{
	touchBeganCallback = nullptr;
	touchEndCallback = nullptr;
	touchMoveCallback = nullptr;
	_isRunning = false;
}


BattleControllPanel::~BattleControllPanel(void)
{
}

bool BattleControllPanel::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	return true;
}

void BattleControllPanel::onEnter()
{
	Layer::onEnter();
	auto _layout = static_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("images/ui/battle_scene/BattleUI_controller.ExportJson"));
	addChild(_layout);
	
	btnNormalAttack = static_cast<Button*>(Helper::seekWidgetByName(_layout, "btnNormalAttack"));
	btnNormalAttack->addTouchEventListener(this, toucheventselector(BattleControllPanel::onButtonTouched));
}

void BattleControllPanel::run()
{
	_isRunning = true;
}

void BattleControllPanel::stop()
{
	_isRunning = false;
}

void BattleControllPanel::onButtonTouched(Node* object, Widget::TouchEventType type)
{
	if(_isRunning)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			if(touchBeganCallback)
			{
				touchBeganCallback(object);
			}
			break;
		case Widget::TouchEventType::MOVED:
			if(touchMoveCallback)
			{
				touchMoveCallback(object);
			}
			break;
		case Widget::TouchEventType::ENDED:
			if(touchEndCallback)
			{
				touchEndCallback(object);
			}
			break;
		default:
			break;
		}
	}
}