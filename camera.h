#ifndef _CAMERA_H
#define _CAMERA_H

#include <d3d9.h>
#include <d3dx9.h>

class Camera {
public :
	Camera(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DXMATRIX *g_viewMatrix);//构造函数初始化
	~Camera() { Shutdown(); }//析构函数释放资源

	void SetCamera(D3DXVECTOR3 *eye, D3DXVECTOR3 *tar, int width, int height);//设置摄像机

	void Shutdown();
public :
	void xMove(float x_dis);//x轴移动
	void yMove(float y_dis);//y轴移动
	void zMove(float z_dis);//z轴移动

	void xRoation(float x_angle);//x轴旋转
	void yRoation(float y_angle);//y轴旋转
	void zRoation(float z_angle);//z轴旋转

	void CalculateViewMatrix(D3DXMATRIX *pMatrix);//取景变换
public :
	LPDIRECT3DDEVICE9 m_Device;

	D3DXVECTOR3 camera_x;	//x轴方向
	D3DXVECTOR3 camera_y;	//y轴方向
	D3DXVECTOR3 camera_z;	//z轴方向
	D3DXVECTOR3 camera_poition;  //摄像机位置
	D3DXVECTOR3 target_position; //目标位置

	D3DXMATRIX m_viewMatrix;//视图矩阵
};

#endif
