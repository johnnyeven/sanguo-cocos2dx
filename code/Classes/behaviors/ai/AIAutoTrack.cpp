#include "AIAutoTrack.h"
#include "../../BattleScene.h"
#include "../../characters/Role.h"
#include "../../define.h"
#include "../../behaviors/IBehavior.h"
#include "IAILockable.h"

AIAutoTrack::AIAutoTrack(void):
	_target(nullptr),
	_locked(nullptr),
	_behavior(nullptr)
{
	_scene = BattleScene::getInstance();
	_maxAIWaitingTime = MAX_AI_WAITING_TIME;
}

AIAutoTrack::AIAutoTrack(int priority):
	_target(nullptr),
	_locked(nullptr),
	_behavior(nullptr),
	_priority(priority)
{
	_scene = BattleScene::getInstance();
	_maxAIWaitingTime = MAX_AI_WAITING_TIME;
}

AIAutoTrack::~AIAutoTrack(void)
{
}

void AIAutoTrack::setTarget(Role* value)
{
	_target = value;
}

void AIAutoTrack::setBehavior(IBehavior* b)
{
	if(dynamic_cast<IAILockable*>(b))
	{
		_behavior = dynamic_cast<IAILockable*>(b);
		_locked = _behavior->getLocked();
	}
	else
	{
		_behavior = nullptr;
	}
}

int AIAutoTrack::getPriority()
{
	return _priority;
}

void AIAutoTrack::setPriority(int value)
{
	_priority = value;
}

void AIAutoTrack::update(float delta)
{
	if(_target && _behavior)
	{
		if(!_locked)
		{
			std::map< int, std::vector< Role* > > teamMap = _scene->getTeamMap();
			int team = !_target->getTeam();
			std::map< int, std::vector< Role* > >::iterator it = teamMap.find(team);
			if(it != teamMap.end())
			{
				std::vector< Role* > tmpList = it->second;
				float minDistance = FLT_MAX;
				Role* role = nullptr;
				for(auto item : tmpList)
				{
					Point p1 = _target->getWorldPosition();
					Point p2 = item->getWorldPosition();
					float d = p1.distance(p2);
					if(d < minDistance)
					{
						minDistance = d;
						role = item;
					}
				}
				_locked = role;
				_behavior->setLocked(role);
			}
		}
		else
		{
			Point p1 = _target->getWorldPosition();
			Point p2 = _locked->getWorldPosition();
			if(_maxAIWaitingTime > 0)
			{
				_maxAIWaitingTime -= delta;
				return;
			}
			Point p = p2 - p1;
			if(p.length() > 5.f)
			{
				_target->setAction(RoleAction::RUN);
				Point p = p2 - p1;
				float angle = p.getAngle();
				float offsetX = _target->getSpeed() * cosf(angle) * delta;
				float offsetY = _target->getSpeed() * sinf(angle) * delta;
				float x = p1.x + offsetX;
				float y = p1.y + offsetY;
				_target->setWorldPosition(x, y);
			}
			else
			{
				_target->setAction(RoleAction::STAND);
			}
		}
	}
}