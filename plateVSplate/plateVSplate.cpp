﻿#include<iostream>
#include"util.h"
#include"atlas.h"
#include"scene.h"
#include"menu_scene.h"
#include"game_scene.h"
#include"scene_manager.h"
#include"selector_scene.h"
#include"platform.h"
#include"bullet.h"
#include"player.h"

#include<graphics.h>
using namespace std;

#pragma comment(lib,"Winmm.lib")

bool is_debug = false; //调试模式

//定义所需图片和图集
//-----------------------------------------------------------------------------------------------------------------------
IMAGE img_menu_background; //主菜单背景图片
IMAGE img_VS; //VS艺术字图片
IMAGE img_1P; //1P文本图片
IMAGE img_2P; //2P
IMAGE img_1P_desc; //1P键位描述图片
IMAGE img_2P_desc; //2P
IMAGE img_gravestone_left; //朝向左的墓碑图片
IMAGE img_gravestone_right; //朝向右
IMAGE img_selector_tip; //选角界面tips
IMAGE img_selector_background; //背景图
IMAGE img_1P_selector_btn_idle_left; //1P向左选择按钮默认状态图片
IMAGE img_1P_selector_btn_idle_right; //1P向右选择按钮默认状态图片
IMAGE img_1P_selector_btn_down_left; //1P向左选择按钮按下状态图片
IMAGE img_1P_selector_btn_down_right; //1P向右选择按钮按下状态图片
IMAGE img_2P_selector_btn_idle_left; //2P向左选择按钮默认状态图片
IMAGE img_2P_selector_btn_idle_right; //2P向右选择按钮默认状态图片
IMAGE img_2P_selector_btn_down_left; //2P向左选择按钮按下状态图片
IMAGE img_2P_selector_btn_down_right; //2P向右选择按钮按下状态图片
IMAGE img_peashooter_selector_background_left; //选角界面朝向左的豌豆射手背景图片
IMAGE img_peashooter_selector_background_right; //选角界面朝向右的豌豆射手背景图片
IMAGE img_sunflower_selector_background_left; //选角界面朝向左的向日葵背景图片
IMAGE img_sunflower_selector_background_right; //选角界面朝向右的向日葵背景图片

IMAGE img_sky;
IMAGE img_hills;
IMAGE img_platform_large; //大型平台
IMAGE img_platform_small; //小

IMAGE img_1P_cursor; //光标
IMAGE img_2P_cursor;

Atlas atlas_peashooter_idle_left; //豌豆射手朝向左默认动画图集
Atlas atlas_peashooter_idle_right; //豌豆射手朝向右默认动画图集
Atlas atlas_peashooter_run_left; //豌豆射手朝向左奔跑动画图集
Atlas atlas_peashooter_run_right; //豌豆射手朝向右奔跑动画图集
Atlas atlas_peashooter_attack_ex_left; //豌豆射手朝向左特殊攻击动画图集
Atlas atlas_peashooter_attack_ex_right; //豌豆射手朝向右特殊攻击动画图集
Atlas atlas_peashooter_die_left; //豌豆射手朝向左死亡动画图集
Atlas atlas_peashooter_die_right; //豌豆射手朝向右死亡动画图集

Atlas atlas_sunflower_idle_left; //向日葵朝向左默认动画图集
Atlas atlas_sunflower_idle_right; //向日葵朝向右默认动画图集
Atlas atlas_sunflower_run_left; //向日葵朝向左奔跑动画图集
Atlas atlas_sunflower_run_right; //向日葵朝向右奔跑动画图集
Atlas atlas_sunflower_attack_ex_left; //向日葵朝向左特殊攻击动画图集
Atlas atlas_sunflower_attack_ex_right; //向日葵朝向右特殊攻击动画图集
Atlas atlas_sunflower_die_left; //向日葵朝向左死亡动画图集
Atlas atlas_sunflower_die_right; //向日葵朝向右死亡动画图集

IMAGE img_pea; //豌豆图片
Atlas atlas_pea_break; //豌豆破碎
Atlas atlas_sun; //阳光动画
Atlas atlas_sun_break;
Atlas atlas_sun_explode; //阳光爆炸
Atlas atlas_sun_ex; //阳光特殊攻击
Atlas atlas_sun_ex_explode;
Atlas atlas_sun_text;

Atlas atlas_run_effect;
Atlas atlas_jump_effect;
Atlas atlas_land_effect;

IMAGE img_1P_winnner;
IMAGE img_2P_winnner;
IMAGE img_winnner_bar; //获胜文本背景

IMAGE img_avatar_peashooter; //豌豆射手头像
IMAGE img_avatar_sunflower;
//-----------------------------------------------------------------------------------------------------------------------

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* selector_scene = nullptr;

Camera main_camera;
SceneManager scene_manager;

vector<Bullet*>bullet_list;
vector<Platform> platform_list;

Player* player_1 = nullptr;
Player* player_2 = nullptr;

IMAGE* img_player_1_avatar = nullptr;
IMAGE* img_player_2_avatar = nullptr;

void flip_atlas(Atlas& src, Atlas& dst) //图集翻转
{
	dst.clear();
	for (int i = 0; i < src.get_size(); i++)
	{
		IMAGE img_flpipped;
		flip_image(src.get_image(i), &img_flpipped);
		dst.add_image(img_flpipped);
	}
}

void load_game_resources() //直接加载需要的素材
{
	//加载游戏字体 加载并处理图片素材 加载音乐音效
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

	loadimage(&img_menu_background, _T("resources/menu_background.png"));

	loadimage(&img_VS, _T("resources/VS.png"));
	loadimage(&img_1P, _T("resources/1P.png"));
	loadimage(&img_2P, _T("resources/2P.png"));
	loadimage(&img_1P_desc, _T("resources/1P_desc.png"));
	loadimage(&img_2P_desc, _T("resources/2P_desc.png"));
	loadimage(&img_gravestone_right, _T("resources/gravestone.png"));
	flip_image(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_selector_tip, _T("resources/selector_tip.png"));
	loadimage(&img_selector_background, _T("resources/selector_background.png"));
	loadimage(&img_1P_selector_btn_idle_right, _T("resources/1P_selector_btn_idle.png"));
	flip_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
	loadimage(&img_1P_selector_btn_down_right, _T("resources/1P_selector_btn_down.png"));
	flip_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);
	loadimage(&img_2P_selector_btn_idle_right, _T("resources/2P_selector_btn_idle.png"));
	flip_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
	loadimage(&img_2P_selector_btn_down_right, _T("resources/2P_selector_btn_down.png"));
	flip_image(&img_2P_selector_btn_down_right, &img_2P_selector_btn_down_left);
	loadimage(&img_peashooter_selector_background_right, _T("resources/peashooter_selector_background.png"));
	flip_image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
	loadimage(&img_sunflower_selector_background_right, _T("resources/sunflower_selector_background.png"));
	flip_image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);

	loadimage(&img_sky, _T("resources/sky.png"));
	loadimage(&img_hills, _T("resources/hills.png"));
	loadimage(&img_platform_large, _T("resources/platform_large.png"));
	loadimage(&img_platform_small, _T("resources/platform_small.png"));

	atlas_peashooter_idle_right.load_from_file(_T("resources/peashooter_idle_%d.png"), 9);
	flip_atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	atlas_peashooter_run_right.load_from_file(_T("resources/peashooter_run_%d.png"), 5);
	flip_atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);
	atlas_peashooter_attack_ex_right.load_from_file(_T("resources/peashooter_attack_ex_%d.png"), 3);
	flip_atlas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);
	atlas_peashooter_die_right.load_from_file(_T("resources/peashooter_die_%d.png"), 4);
	flip_atlas(atlas_peashooter_die_right, atlas_peashooter_die_left);

	atlas_sunflower_idle_right.load_from_file(_T("resources/sunflower_idle_%d.png"), 8);
	flip_atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
	atlas_sunflower_run_right.load_from_file(_T("resources/sunflower_run_%d.png"), 5);
	flip_atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);
	atlas_sunflower_attack_ex_right.load_from_file(_T("resources/sunflower_attack_ex_%d.png"), 9);
	flip_atlas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);
	atlas_sunflower_die_right.load_from_file(_T("resources/sunflower_die_%d.png"), 2);
	flip_atlas(atlas_sunflower_die_right, atlas_sunflower_die_left);

	loadimage(&img_pea, _T("resources/pea.png"));
	atlas_pea_break.load_from_file(_T("resources/pea_break_%d.png"), 3);
	atlas_sun.load_from_file(_T("resources/sun_%d.png"), 5);
	atlas_sun_explode.load_from_file(_T("resources/sun_explode_%d.png"), 5);
	atlas_sun_ex.load_from_file(_T("resources/sun_ex_%d.png"), 5);
	atlas_sun_ex_explode.load_from_file(_T("resources/sun_ex_explode_%d.png"), 5);
	atlas_sun_text.load_from_file(_T("resources/sun_text_%d.png"), 6);

	atlas_run_effect.load_from_file(_T("resources/run_effect_%d.png"), 4);
	atlas_jump_effect.load_from_file(_T("resources/jump_effect_%d.png"), 5);
	atlas_land_effect.load_from_file(_T("resources/land_effect_%d.png"), 2);

	loadimage(&img_1P_winnner, _T("resources/1P_winner.png"));
	loadimage(&img_2P_winnner, _T("resources/2P_winner.png"));
	loadimage(&img_winnner_bar, _T("resources/winnner_bar.png"));

	loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
	loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));

	//借助alias指令定义不同别名
	mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
	mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);
}

int main()
{
	ExMessage msg;
	const int FPS = 60;

	load_game_resources();

	initgraph(1280, 720,EW_SHOWCONSOLE);

	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT); //设置文本框透明

	BeginBatchDraw();
	
	//初始化
	menu_scene = new MenuScene();
	game_scene = new GameScene();
	selector_scene = new SelectorScene();

	scene_manager.set_current_scene(menu_scene);

	while (true)
	{
		DWORD frame_start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
		}

		//计算上一次调用on_update和这一次调用的时间间隔作为逻辑更新的时间
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;
		scene_manager.on_update(delta_tick);
		last_tick_time = current_tick_time;

		cleardevice();
		scene_manager.on_draw(main_camera);
		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < 1000 / FPS)
		{
			Sleep(1000 / FPS - frame_delta_time);
		}
	}

	EndBatchDraw();
}