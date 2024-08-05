#pragma once

#include"camera.h"

#include<graphics.h>

class Scene
{
public:
	//构造函数和析构函数默认
	Scene() = default;
	~Scene() = default;

	//游戏主循环的各个阶段
	virtual void on_enter() { } //处理玩家输入
	virtual void on_update(int delta) { } //处理数据 delta表示实际过去的时间
	virtual void on_draw(const Camera& camera) { } //渲染绘图
	virtual void on_input(const ExMessage& msg) { } //场景进入时的初始化逻辑
	virtual void on_exit() { } //场景退出时的卸载逻辑

private:

};