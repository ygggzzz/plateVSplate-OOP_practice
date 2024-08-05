#pragma once

#include"camera.h"

#include<graphics.h>

class Scene
{
public:
	//���캯������������Ĭ��
	Scene() = default;
	~Scene() = default;

	//��Ϸ��ѭ���ĸ����׶�
	virtual void on_enter() { } //�����������
	virtual void on_update(int delta) { } //�������� delta��ʾʵ�ʹ�ȥ��ʱ��
	virtual void on_draw(const Camera& camera) { } //��Ⱦ��ͼ
	virtual void on_input(const ExMessage& msg) { } //��������ʱ�ĳ�ʼ���߼�
	virtual void on_exit() { } //�����˳�ʱ��ж���߼�

private:

};