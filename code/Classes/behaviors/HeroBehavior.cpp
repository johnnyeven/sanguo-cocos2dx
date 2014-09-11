//
//  HeroBehavior.cpp
//  Sanguo
//
//  Created by 李翌文 on 14-9-7.
//
//

#include "HeroBehavior.h"
#include "BattleScene.h"
#include "Joystick.h"
#include "GlobalVars.h"
#include "BattleControllPanel.h"
#include "../characters/Hero.h"

HeroBehavior::HeroBehavior()
{
	_target = nullptr;
	_scene = BattleScene::getInstance();
	_joystick = BattleControllPanel::getInstance()->getJoystick();
	_halfScreenWidth = GlobalVars::scene_width >> 1;
	_halfScreenHeight = GlobalVars::scene_height >> 1;
}

HeroBehavior::~HeroBehavior()
{
    
}

void HeroBehavior::update(float delta)
{
	RoleAction a = _target->getAction();
	if(a == RoleAction::ATTACK1 ||
		 a == RoleAction::ATTACK2 ||
		 a == RoleAction::ATTACK3 ||
		 a == RoleAction::ATTACK4 ||
		 a == RoleAction::ATTACK5)
	{
		return;
	}
	if(GlobalVars::behavior_mode == BehaviorMode::MANUAL && _joystick)
	{
		//Manual controll
		JoystickEnum d = _joystick->getDirection();
		if(d != JoystickEnum::DEFAULT)
		{
			if(a == RoleAction::ATTACK1 ||
				 a == RoleAction::ATTACK2 ||
				 a == RoleAction::ATTACK3 ||
				 a == RoleAction::ATTACK4 ||
				 a == RoleAction::ATTACK5)
			{
				return;
			}
			_target->setAction(RoleAction::RUN);
			Point p = _target->getWorldPosition();
			float angle;
			if(d == JoystickEnum::D_LEFT)
			{
				_target->setBackWalk(true);
				float x = p.x - _target->getSpeed() * delta;
				_target->setWorldPosition(x, p.y);
			}
			else if(d == JoystickEnum::D_RIGHT)
			{
				_target->setBackWalk(false);
				float x = p.x + _target->getSpeed() * delta;
				_target->setWorldPosition(x, p.y);
			}
			else if(d == JoystickEnum::D_UP)
			{
				float y = p.y + _target->getSpeed() * delta;
				_target->setWorldPosition(p.x, y);
			}
			else if(d == JoystickEnum::D_DOWN)
			{
				float y = p.y - _target->getSpeed() * delta;
				_target->setWorldPosition(p.x, y);
			}
            else if(d == JoystickEnum::D_LEFT_UP)
            {
				angle = CC_DEGREES_TO_RADIANS(150.f);
                _target->setBackWalk(true);
				float x = p.x + _target->getSpeed() * cosf(angle) * delta;
				float y = p.y + _target->getSpeed() * sinf(angle) * delta;
				_target->setWorldPosition(x, y);
            }
            else if(d == JoystickEnum::D_LEFT_DOWN)
            {
				angle = CC_DEGREES_TO_RADIANS(-150.f);
                _target->setBackWalk(true);
				float x = p.x + _target->getSpeed() * cosf(angle) * delta;
				float y = p.y + _target->getSpeed() * sinf(angle) * delta;
				_target->setWorldPosition(x, y);
            }
            else if(d == JoystickEnum::D_RIGHT_UP)
            {
				angle = CC_DEGREES_TO_RADIANS(30.f);
                _target->setBackWalk(false);
				float x = p.x + _target->getSpeed() * cosf(angle) * delta;
				float y = p.y + _target->getSpeed() * sinf(angle) * delta;
				_target->setWorldPosition(x, y);
            }
            else if(d == JoystickEnum::D_RIGHT_DOWN)
            {
				angle = CC_DEGREES_TO_RADIANS(-30.f);
                _target->setBackWalk(false);
				float x = p.x + _target->getSpeed() * cosf(angle) * delta;
				float y = p.y + _target->getSpeed() * sinf(angle) * delta;
				_target->setWorldPosition(x, y);
            }
		}
		else
		{
			if(a == RoleAction::RUN)
			{
				_target->setAction(RoleAction::WAIT);
			}
		}
	}
	else
	{
		//Auto controll
	}

	updatePosition(delta);
}

void HeroBehavior::updatePosition(float delta)
{
	if(_target)
	{
		float targetX, targetY;
		Point p = _target->getWorldPosition();
		if(_target->getFocused())
		{
			targetX = p.x < _halfScreenWidth ? p.x : _halfScreenWidth;
			targetY = p.y < _halfScreenHeight ? p.y : _halfScreenHeight;

			targetX = p.x > (_scene->getMapWidth() - _halfScreenWidth) ? (p.x - (_scene->getMapWidth() - GlobalVars::scene_width)) : targetX;
			targetY = p.y > (_scene->getMapHeight() - _halfScreenHeight) ? (p.x - (_scene->getMapHeight() - GlobalVars::scene_height)) : targetY;
		}
		else
		{
			Point screenPosition = _scene->getScreenPosition(p.x, p.y);
			targetX = screenPosition.x;
			targetY = screenPosition.y;
		}

		_target->setPosition(targetX, targetY);
	}
}

void HeroBehavior::setTarget(Hero* value)
{
    _target = value;
}