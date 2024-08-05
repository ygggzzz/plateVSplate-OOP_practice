#pragma once
#include"scene.h"

//获得全局指针的应用
extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* selector_scene;

class SceneManager
{
public:
	enum class SceneType //标记当前的场景状态
	{
		Menu,
		Game,
		Selector
	};

public:
	SceneManager() = default;
	~SceneManager() = default;

	void set_current_scene(Scene* scene)
	{
		current_scene = scene;
		current_scene->on_enter();
	}

	void switch_to(SceneType type) //执行场景间的跳转逻辑
	{
		//1.退出当前场景
		current_scene->on_exit();
		//2.根据枚举参数找到新场景
		switch (type)
		{
		case SceneType::Menu:
			current_scene = menu_scene;
			break;
		case SceneType::Game:
			current_scene = game_scene;
			break;
		case SceneType::Selector:
			current_scene = selector_scene;
		default:
			break;
		}
		//3.进入场景
		current_scene->on_enter();
	}

	void on_update(int delta)
	{
		current_scene->on_update(delta);
	}

	void on_draw(const Camera& camera)
	{
		current_scene->on_draw(camera);
	}

	void on_input(const ExMessage& msg)
	{
		current_scene->on_input(msg);
	}

private:
	Scene* current_scene = nullptr;

};