#include "sky.h"

Sky::Sky(LPDIRECT3DDEVICE9 g_pd3dDevice) {
	m_Device = g_pd3dDevice;
}

void Sky::SetSky(TCHAR *up, TCHAR *down, TCHAR *left, TCHAR *right, TCHAR *front, TCHAR *back) {
	D3DXCreateTextureFromFile(m_Device, up, &up_Texture);
	m_Device->CreateVertexBuffer(4 * sizeof(sky_obj),0,D3DFVF_SKY,D3DPOOL_DEFAULT,&up_Buffer,NULL);

	D3DXCreateTextureFromFile(m_Device, down, &down_Texture);
	m_Device->CreateVertexBuffer(4 * sizeof(sky_obj), 0, D3DFVF_SKY, D3DPOOL_DEFAULT, &down_Buffer, NULL);

	D3DXCreateTextureFromFile(m_Device, left, &left_Texture);
	m_Device->CreateVertexBuffer(4 * sizeof(sky_obj), 0, D3DFVF_SKY, D3DPOOL_DEFAULT, &left_Buffer, NULL);

	D3DXCreateTextureFromFile(m_Device, right, &right_Texture);
	m_Device->CreateVertexBuffer(4 * sizeof(sky_obj), 0, D3DFVF_SKY, D3DPOOL_DEFAULT, &right_Buffer, NULL);

	D3DXCreateTextureFromFile(m_Device, front, &front_Texture);
	m_Device->CreateVertexBuffer(4 * sizeof(sky_obj), 0, D3DFVF_SKY, D3DPOOL_DEFAULT, &front_Buffer, NULL);

	D3DXCreateTextureFromFile(m_Device, back, &back_Texture);
	m_Device->CreateVertexBuffer(4 * sizeof(sky_obj), 0, D3DFVF_SKY, D3DPOOL_DEFAULT, &back_Buffer, NULL);
}

void ProcessSky(Sky *g_sky, float world_x, float world_y, float world_z, int size) {
	LPDIRECT3DDEVICE9 Device = g_sky->GetDevice();

	g_sky->Sky_x = world_x;
	g_sky->Sky_y = world_y;
	g_sky->Sky_z = world_z;

	//天空(世界矩阵)
	D3DXMATRIX matSkyBox;
	D3DXMatrixTranslation(&matSkyBox, g_sky->Sky_x, g_sky->Sky_y, g_sky->Sky_z);
	Device->SetTransform(D3DTS_WORLD, &matSkyBox);

	//绘制天空
	//上
	g_sky->sky_obj[0] = { -size / 2 + g_sky->Sky_x, size + g_sky->Sky_y, -size / 2 + g_sky->Sky_z, 0.0f, 0.0f };
	g_sky->sky_obj[1] = { -size / 2 + g_sky->Sky_x, size + g_sky->Sky_y, size / 2 + g_sky->Sky_z, 0.0f, 1.0f };
	g_sky->sky_obj[2] = { size / 2 + g_sky->Sky_x, size + g_sky->Sky_y, size / 2 + g_sky->Sky_z, 1.0f, 1.0f };
	g_sky->sky_obj[3] = { size / 2 + g_sky->Sky_x, size + g_sky->Sky_y, -size / 2 + g_sky->Sky_z, 1.0f, 0.0f };

	void *ptr1;
	g_sky->up_Buffer->Lock(0, sizeof(ptr1), (void**)&ptr1, 0);
	memcpy(ptr1, g_sky->sky_obj, sizeof(g_sky->sky_obj));
	g_sky->up_Buffer->Unlock();

	Device->SetTexture(0, g_sky->up_Texture);
	Device->SetStreamSource(0, g_sky->up_Buffer, 0, sizeof(SkyVertex));
	Device->SetFVF(D3DFVF_SKY);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//下
	g_sky->sky_obj[0] = { -size / 2 + g_sky->Sky_x, 1000.0f + g_sky->Sky_y, size / 2 + g_sky->Sky_z, 0.0f, 1.0f };
	g_sky->sky_obj[1] = { -size / 2 + g_sky->Sky_x, 1000.0f + g_sky->Sky_y, -size / 2 + g_sky->Sky_z, 0.0f, 0.0f };
	g_sky->sky_obj[2] = { size / 2 + g_sky->Sky_x, 1000.0f + g_sky->Sky_y, size / 2 + g_sky->Sky_z, 1.0f, 1.0f };
	g_sky->sky_obj[3] = { size / 2 + g_sky->Sky_x, 1000.0f + g_sky->Sky_y, -size / 2 + g_sky->Sky_z, 1.0f, 0.0f };

	void *ptr2;
	g_sky->down_Buffer->Lock(0, sizeof(ptr2), (void**)&ptr2, 0);
	memcpy(ptr2, g_sky->sky_obj, sizeof(g_sky->sky_obj));
	g_sky->down_Buffer->Unlock();

	Device->SetTexture(0, g_sky->down_Texture);
	Device->SetStreamSource(0, g_sky->down_Buffer, 0, sizeof(SkyVertex));
	Device->SetFVF(D3DFVF_SKY);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//前
	g_sky->sky_obj[0] = { -size / 2 + g_sky->Sky_x, size + g_sky->Sky_y, 10000.0f + g_sky->Sky_z, 0.0f, 0.0f };
	g_sky->sky_obj[1] = { -size / 2 + g_sky->Sky_x, 0.0f + g_sky->Sky_y, 10000.0f + g_sky->Sky_z, 0.0f, 1.0f };
	g_sky->sky_obj[2] = { size / 2 + g_sky->Sky_x, size + g_sky->Sky_y, 10000.0f + g_sky->Sky_z, 1.0f, 0.0f };
	g_sky->sky_obj[3] = { size / 2 + g_sky->Sky_x, 0.0f + g_sky->Sky_y, 10000.0f + g_sky->Sky_z, 1.0f, 1.0f };

	void *ptr3;
	g_sky->front_Buffer->Lock(0, sizeof(ptr3), (void**)&ptr3, 0);
	memcpy(ptr3, g_sky->sky_obj, sizeof(g_sky->sky_obj));
	g_sky->front_Buffer->Unlock();

	Device->SetTexture(0, g_sky->front_Texture);
	Device->SetStreamSource(0, g_sky->front_Buffer, 0, sizeof(SkyVertex));
	Device->SetFVF(D3DFVF_SKY);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//后
	g_sky->sky_obj[0] = { -size / 2 + g_sky->Sky_x, size + g_sky->Sky_y, -10000.0f + g_sky->Sky_z, 1.0f, 0.0f };
	g_sky->sky_obj[1] = { -size / 2 + g_sky->Sky_x, 0.0f + g_sky->Sky_y, -10000.0f + g_sky->Sky_z, 1.0f, 1.0f };
	g_sky->sky_obj[2] = { size / 2 + g_sky->Sky_x, size + g_sky->Sky_y, -10000.0f + g_sky->Sky_z, 0.0f, 0.0f };
	g_sky->sky_obj[3] = { size / 2 + g_sky->Sky_x, 0.0f + g_sky->Sky_y, -10000.0f + g_sky->Sky_z, 0.0f, 1.0f };

	void *ptr4;
	g_sky->back_Buffer->Lock(0, sizeof(ptr4), (void**)&ptr4, 0);
	memcpy(ptr4, g_sky->sky_obj, sizeof(g_sky->sky_obj));
	g_sky->back_Buffer->Unlock();

	Device->SetTexture(0, g_sky->back_Texture);
	Device->SetStreamSource(0, g_sky->back_Buffer, 0, sizeof(SkyVertex));
	Device->SetFVF(D3DFVF_SKY);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//左
	g_sky->sky_obj[0] = { -10000.0f + g_sky->Sky_x, 0.0f + g_sky->Sky_y, size / 2 + g_sky->Sky_z, 1.0f, 1.0f };
	g_sky->sky_obj[1] = { -10000.0f + g_sky->Sky_x, 0.0f + g_sky->Sky_y, -size / 2 + g_sky->Sky_z, 0.0f, 1.0f };
	g_sky->sky_obj[2] = { -10000.0f + g_sky->Sky_x, size + g_sky->Sky_y, size / 2 + g_sky->Sky_z, 1.0f, 0.0f };
	g_sky->sky_obj[3] = { -10000.0f + g_sky->Sky_x, size + g_sky->Sky_y, -size / 2 + g_sky->Sky_z, 0.0f, 0.0f };

	void *ptr5;
	g_sky->left_Buffer->Lock(0, sizeof(ptr5), (void**)&ptr5, 0);
	memcpy(ptr5, g_sky->sky_obj, sizeof(g_sky->sky_obj));
	g_sky->left_Buffer->Unlock();

	Device->SetTexture(0, g_sky->left_Texture);
	Device->SetStreamSource(0, g_sky->left_Buffer, 0, sizeof(SkyVertex));
	Device->SetFVF(D3DFVF_SKY);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//右
	g_sky->sky_obj[0] = { 10000.0f + g_sky->Sky_x, 0.0f + g_sky->Sky_y, size / 2 + g_sky->Sky_z, 0.0f, 1.0f };
	g_sky->sky_obj[1] = { 10000.0f + g_sky->Sky_x, 0.0f + g_sky->Sky_y, -size / 2 + g_sky->Sky_z, 1.0f, 1.0f };
	g_sky->sky_obj[2] = { 10000.0f + g_sky->Sky_x, size + g_sky->Sky_y, size / 2 + g_sky->Sky_z, 0.0f, 0.0f };
	g_sky->sky_obj[3] = { 10000.0f + g_sky->Sky_x, size + g_sky->Sky_y, -size / 2 + g_sky->Sky_z, 1.0f, 0.0f };

	void *ptr6;
	g_sky->right_Buffer->Lock(0, sizeof(ptr6), (void**)&ptr6, 0);
	memcpy(ptr6, g_sky->sky_obj, sizeof(g_sky->sky_obj));
	g_sky->right_Buffer->Unlock();

	Device->SetTexture(0, g_sky->right_Texture);
	Device->SetStreamSource(0, g_sky->right_Buffer, 0, sizeof(SkyVertex));
	Device->SetFVF(D3DFVF_SKY);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void Sky::Shutdown() {
	m_Device->Release();

	up_Buffer->Release();
	down_Buffer->Release();
	front_Buffer->Release();
	back_Buffer->Release();
	left_Buffer->Release();
	right_Buffer->Release();

	up_Texture->Release();
	down_Texture->Release();
	front_Texture->Release();
	back_Texture->Release();
	left_Texture->Release();
	right_Texture->Release();
}
