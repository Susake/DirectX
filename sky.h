#ifndef _SKY_H
#define _SKY_H

#include "sky.h"

#include <d3d9.h>
#include <d3dx9.h>

// 天空的顶点结构
struct SkyVertex
{
	float x, y, z;
	float tu, tv;
};
#define D3DFVF_SKY  (D3DFVF_XYZ | D3DFVF_TEX1)

//天空类
class Sky {
public:
	Sky(LPDIRECT3DDEVICE9 g_pd3dDevice);//构造函数初始化
	~Sky() { Shutdown(); }//析构函数释放资源
	
	void SetSky(TCHAR *up, TCHAR *down, TCHAR *left, TCHAR *right, TCHAR *front, TCHAR *back);

	void Shutdown();
public :
	LPDIRECT3DDEVICE9 GetDevice() { return m_Device; }//获取设备
public :
	LPDIRECT3DDEVICE9 m_Device;

	LPDIRECT3DVERTEXBUFFER9 up_Buffer = NULL;
	LPDIRECT3DVERTEXBUFFER9 down_Buffer = NULL;
	LPDIRECT3DVERTEXBUFFER9 front_Buffer = NULL;
	LPDIRECT3DVERTEXBUFFER9 back_Buffer = NULL;
	LPDIRECT3DVERTEXBUFFER9 left_Buffer = NULL;
	LPDIRECT3DVERTEXBUFFER9 right_Buffer = NULL;

	LPDIRECT3DTEXTURE9 up_Texture = NULL;
	LPDIRECT3DTEXTURE9 down_Texture = NULL;
	LPDIRECT3DTEXTURE9 front_Texture = NULL;
	LPDIRECT3DTEXTURE9 back_Texture = NULL;
	LPDIRECT3DTEXTURE9 left_Texture = NULL;
	LPDIRECT3DTEXTURE9 right_Texture = NULL;

	SkyVertex sky_obj[4];

	float Sky_x, Sky_y, Sky_z;
};

void ProcessSky(Sky *g_sky, float world_x, float world_y, float world_z, int size);

#endif
