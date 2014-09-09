//
//  Camera.h
//  IntoSpace
//
//  Created by 李翌文 on 14-8-24.
//
//

#ifndef __IntoSpace__Camera__
#define __IntoSpace__Camera__

#include "cocos2d.h"
#include "Role.h"
#include "BattleScene.h"

USING_NS_CC;

class SceneCamera
{
public:
    static SceneCamera* getInstance();
    void setStart(float x, float y);
    void setCutStart(float x, float y);
	float getViewStartX() { return _start.x; };
	float getViewStartY() { return _start.y; };
    Vec2 getStart() { return _start; };
	float getCutViewStartX() { return _cutStart.x; };
	float getCutViewStartY() { return _cutStart.y; };
    Vec2 getCutViewStart() { return _cutStart; };
    void setScene(BattleScene* scene);
    void focusOn(Role *obj);
    Rect& getCameraView();
    Rect& getCameraCutView();
    Rect& getScreenView() { return _screenView; };
    Rect& getScreenCutView() { return _screenCutView; };
    void update(float delta);
    Vec2 getScreenPosition(float positionX, float positionY);
private:
    SceneCamera(void);
    ~SceneCamera(void);
    
    static SceneCamera* _instance;
    
	Vec2 _cutStart;
    Vec2 _start;
    Rect _screenView;
    Rect _screenCutView;
    Rect _cameraView;
    Rect _cameraCutView;
    float _x;
    float _y;
    Role* _focus;
    BattleScene* _scene;
};

#endif /* defined(__IntoSpace__Camera__) */
