//
//  Camera.cpp
//  IntoSpace
//
//  Created by 李翌文 on 14-8-24.
//
//

#include "Camera.h"
#include "GlobalVars.h"
#include "BattleScene.h"

SceneCamera* SceneCamera::_instance = nullptr;

SceneCamera::SceneCamera(void)
{
	_focus = nullptr;
	_scene = nullptr;
	_cutStart = Vec2(0, 0);
    _start = Vec2(0, 0);
    _cameraView = Rect(0, 0, GlobalVars::scene_width, GlobalVars::scene_height);
    _cameraCutView = Rect(0, 0, GlobalVars::scene_width + 100, GlobalVars::scene_height + 100);
    _screenView = Rect(0, 0, GlobalVars::scene_width, GlobalVars::scene_height);
    _screenCutView = Rect(
                       -GlobalVars::scene_width,
                       -GlobalVars::scene_height,
                       3 * GlobalVars::scene_width,
                       3 * GlobalVars::scene_height);
}

SceneCamera::~SceneCamera(void)
{
}

SceneCamera* SceneCamera::getInstance()
{
    if(!_instance)
    {
        _instance = new SceneCamera();
    }
    return _instance;
}

void SceneCamera::setScene(BattleScene *scene)
{
    if(scene)
    {
        _scene = scene;
    }
}

void SceneCamera::focusOn(Role *obj)
{
	if(_focus)
	{
		_focus->setFocused(false);
	}
    if(obj)
    {
        obj->setFocused(true);
        _focus = obj;
        
        obj->setNormalizedPosition(Vec2(.5f, .5f));
    }
}

void SceneCamera::update(float delta)
{
    if(!_focus)
    {
        return;
    }
    Point p = _focus->getWorldPosition();
    setStart(
				p.x - (GlobalVars::scene_width >> 1),
				p.y - (GlobalVars::scene_height >> 1));

    setCutStart(
				_start.x - GlobalVars::scene_width,
                _start.y - GlobalVars::scene_height);
    
    _cameraView.setRect(
                        _start.x,
                        _start.y,
                        _cameraView.size.width,
                        _cameraView.size.height);

	_cameraCutView.setRect(
						_cutStart.x,
						_cutStart.y,
						_cameraCutView.size.width,
						_cameraCutView.size.height);
}

void SceneCamera::setStart(float x, float y)
{
    _start.x = std::max(std::min(x, _scene->getMapWidth() - GlobalVars::scene_width), 0.f);
    _start.y = 0;
}

void SceneCamera::setCutStart(float x, float y)
{
    _cutStart.x = std::max(std::min(x, _scene->getMapWidth()), 0.f);
    _cutStart.y = 0;
}

Rect& SceneCamera::getCameraCutView()
{
    return _cameraCutView;
}

Rect& SceneCamera::getCameraView()
{
    return _cameraView;
}

Vec2 SceneCamera::getScreenPosition(float positionX, float positionY)
{
	return Vec2(
				positionX - _start.x,
				positionY - _start.y);
}