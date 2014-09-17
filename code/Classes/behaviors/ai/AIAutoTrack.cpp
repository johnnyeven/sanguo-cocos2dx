#include "AIAutoTrack.h"
#include "../../BattleScene.h"
#include "../../characters/Role.h"
#include "../../define.h"

AIAutoTrack::AIAutoTrack(void):
	_target(nullptr),
	_locked(nullptr)
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

void AIAutoTrack::setLocked(Role* value)
{
	_locked = value;
}

void AIAutoTrack::update(float delta)
{
	if(_target)
	{
		if(!_locked)
		{
			//选取敌对阵营离自己最近的角色锁定
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
			
			if(p1 != p2)
			{
				Point p = p2 - p1;
				float angle = p.getAngle();
				float offsetX = _target->getSpeed() * cosf(angle) * delta;
				float offsetY = _target->getSpeed() * sinf(angle) * delta;
				float x = p1.x + offsetX;
				float y = p1.y + offsetY;
				if(abs(p2.x - x) < offsetX)
					x = p2.x;
				if(abs(p2.y - y) < offsetY)
					y = p2.y;
				_target->setWorldPosition(x, y);
			}
		}
	}
}