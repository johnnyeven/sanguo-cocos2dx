#include "BattleControllPanel.h"
#include "Joystick.h"

BattleControllPanel* BattleControllPanel::_instance = nullptr;

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

BattleControllPanel* BattleControllPanel::getInstance()
{
    if(!_instance)
    {
        _instance = BattleControllPanel::create();
    }
    return _instance;
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
    _joystick = Joystick::create("images/dPadTouchBg2.png", "images/dPadTouchBtn2.png");
    _layout->addChild(_joystick);
    _joystick->setPosition(Vec2(150,150));//設置初始位置
	_joystick->setAutoPosition(true);
    _joystick->setFailRadius(20);
    _joystick->onRun();
    
	btnNormalAttack = static_cast<Button*>(Helper::seekWidgetByName(_layout, "btnNormalAttack"));
	btnNormalAttack->addTouchEventListener(Widget::ccWidgetTouchCallback(CC_CALLBACK_2(BattleControllPanel::onButtonTouched, this)));
}

void BattleControllPanel::run()
{
	_isRunning = true;
}

void BattleControllPanel::stop()
{
	_isRunning = false;
}

void BattleControllPanel::onButtonTouched(Ref* object, Widget::TouchEventType type)
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