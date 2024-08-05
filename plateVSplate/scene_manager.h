#pragma once
#include"scene.h"

//���ȫ��ָ���Ӧ��
extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* selector_scene;

class SceneManager
{
public:
	enum class SceneType //��ǵ�ǰ�ĳ���״̬
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

	void switch_to(SceneType type) //ִ�г��������ת�߼�
	{
		//1.�˳���ǰ����
		current_scene->on_exit();
		//2.����ö�ٲ����ҵ��³���
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
		//3.���볡��
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