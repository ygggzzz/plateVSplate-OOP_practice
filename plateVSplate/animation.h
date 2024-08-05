#pragma once
#include<iostream>
#include"atlas.h"
#include"util.h"
#include"camera.h"

#include<graphics.h>
#include<functional>

//决定实际渲染图集的轻量控制器
class Animation
{
public:
	Animation() = default;
	~Animation() = default;

	void reset() //重置动画状态
	{
		timer = 0;
		idx_frame = 0;
	}

	void set_atlas(Atlas* new_atlas)
	{
		reset();
		atlas = new_atlas;
	}

	void set_loop(bool flag)
	{
		is_loop = flag;
	}

	void set_interval(int ms)
	{
		interval = ms;
	}

	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}

	int get_idx_frame()
	{
		return idx_frame;
	}

	IMAGE* get_frame()
	{
		return atlas->get_image(idx_frame);
	}

	bool check_finished() //检查动画是否播放结束
	{
		if (is_loop)
			return false;

		return (idx_frame == atlas->get_size() - 1);
	}

	void on_update(int delta) //动画更新方法
	{
		//每次更新时累加定时器的值 检查定时器是否达到帧间隔 如果达到则累加帧索引 最后检查动画是否已经播放到图集尾部 并根据是否循环播放设置动画帧索引是从头开始还是保留在图集最后一张图片上
		timer += delta;
		if (timer >= interval)
		{
			timer = 0;
			idx_frame++;
			if (idx_frame >= atlas->get_size())
			{
				idx_frame = is_loop ? 0 : atlas->get_size() - 1;
				//如果帧索引到达看图集尾部并且动画没有设置循环播放且回调函数存在 则执行回调函数
				if (!is_loop && callback)
				{
					callback();
				}
			}
		}
	}

	void on_draw(const Camera& camera,int x, int y) const
	{
		putimage_alpha(camera, x, y, atlas->get_image(idx_frame));
	}

private:
	int timer = 0; //计时器
	int interval = 0; //帧间隔
	int idx_frame = 0; //帧索引
	bool is_loop = true; //是否循环
	Atlas* atlas = nullptr;
	std::function<void()> callback; //回调函数 function表示模板类
};