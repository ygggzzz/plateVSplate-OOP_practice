#pragma once
//存放工具函数
#include"camera.h"
#include"vector2.h"
#include<graphics.h>
#pragma comment(lib,"MSIMG32.LIB")

inline void line(const Camera& camera, int x1, int y1, int x2, int y2)
{
	const Vector2& pos_camera = camera.get_position();
	line((int)(x1 - pos_camera.x), (int)(y1 - pos_camera.y), (int)(x2 - pos_camera.x), (int)(y2 - pos_camera.y));
}

inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img) //将带有透明度的图片绘制到目标位置上
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA }); //将一个图像的部分区域（带有透明度信息）绘制到另一个图像上
}

inline void putimage_alpha(int dst_x, int dst_y, int width, int height,IMAGE* img, int src_x, int src_y) //将带有透明度的图片绘制到目标位置上
{
	int w = width > 0 ? width : img->getwidth();
	int h = height > 0 ? height : img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h, GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA }); //将一个图像的部分区域（带有透明度信息）绘制到另一个图像上
}

inline void putimage_alpha(const Camera& camera, int dst_x, int dst_y, IMAGE* img) //将带有透明度的图片绘制到目标位置上
{
	int w = img->getwidth();
	int h = img->getheight();
	const Vector2& pos_camera = camera.get_position();
	AlphaBlend(GetImageHDC(GetWorkingImage()), (int)(dst_x - pos_camera.x), (int)(dst_y - pos_camera.y), w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA }); //将一个图像的部分区域（带有透明度信息）绘制到另一个图像上
}

inline void flip_image(IMAGE* src, IMAGE* dst) //水平翻转图片
{
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx_src = y * w + x;
			int idx_dst = y * w + (w - x - 1);
			dst_buffer[idx_dst] = src_buffer[idx_src];
		}
	}
}

inline void sketch_image(IMAGE* src, IMAGE* dst) //将图片处理为纯白色剪影
{
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx = y * w + x;
			dst_buffer[idx] = BGR(RGB(255, 255, 255)) | (src_buffer[idx] & 0xFF000000);
		}
	}
}