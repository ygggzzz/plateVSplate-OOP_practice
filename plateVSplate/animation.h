#pragma once
#include<iostream>
#include"atlas.h"
#include"util.h"
#include"camera.h"

#include<graphics.h>
#include<functional>

//����ʵ����Ⱦͼ��������������
class Animation
{
public:
	Animation() = default;
	~Animation() = default;

	void reset() //���ö���״̬
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

	bool check_finished() //��鶯���Ƿ񲥷Ž���
	{
		if (is_loop)
			return false;

		return (idx_frame == atlas->get_size() - 1);
	}

	void on_update(int delta) //�������·���
	{
		//ÿ�θ���ʱ�ۼӶ�ʱ����ֵ ��鶨ʱ���Ƿ�ﵽ֡��� ����ﵽ���ۼ�֡���� ����鶯���Ƿ��Ѿ����ŵ�ͼ��β�� �������Ƿ�ѭ���������ö���֡�����Ǵ�ͷ��ʼ���Ǳ�����ͼ�����һ��ͼƬ��
		timer += delta;
		if (timer >= interval)
		{
			timer = 0;
			idx_frame++;
			if (idx_frame >= atlas->get_size())
			{
				idx_frame = is_loop ? 0 : atlas->get_size() - 1;
				//���֡�������￴ͼ��β�����Ҷ���û������ѭ�������һص��������� ��ִ�лص�����
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
	int timer = 0; //��ʱ��
	int interval = 0; //֡���
	int idx_frame = 0; //֡����
	bool is_loop = true; //�Ƿ�ѭ��
	Atlas* atlas = nullptr;
	std::function<void()> callback; //�ص����� function��ʾģ����
};