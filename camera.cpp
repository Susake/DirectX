#include "camera.h"

Camera::Camera(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DXMATRIX *g_viewMatrix) {
	m_Device = g_pd3dDevice;

	camera_x = D3DXVECTOR3(1.0f, 0.0f, 0.0f);  
	camera_y = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  
	camera_z = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_viewMatrix = *g_viewMatrix;
}

void Camera::SetCamera(D3DXVECTOR3 *eye, D3DXVECTOR3 *tar, int width, int height) {
	camera_poition = *eye;

	target_position = *tar;

	camera_z = target_position - camera_poition;
	D3DXVec3Normalize(&camera_z, &camera_z);

	D3DXVec3Cross(&camera_y, &camera_z, &camera_x);
	D3DXVec3Normalize(&camera_y, &camera_y);
	D3DXVec3Cross(&camera_x, &camera_y, &camera_z);
	D3DXVec3Normalize(&camera_x, &camera_x);

	CalculateViewMatrix(&m_viewMatrix);
	m_Device->SetTransform(D3DTS_VIEW, &m_viewMatrix);

	camera_x = D3DXVECTOR3(m_viewMatrix._11, m_viewMatrix._12, m_viewMatrix._13);
	camera_y = D3DXVECTOR3(m_viewMatrix._21, m_viewMatrix._22, m_viewMatrix._23);
	camera_z = D3DXVECTOR3(m_viewMatrix._31, m_viewMatrix._32, m_viewMatrix._33);
}

void Camera::xMove(float x_dis) {
	camera_poition += camera_x * x_dis;
	target_position += camera_x * x_dis;

	CalculateViewMatrix(&m_viewMatrix);
	m_Device->SetTransform(D3DTS_VIEW, &m_viewMatrix);
}

void Camera::yMove(float y_dis) {
	camera_poition += camera_y * y_dis;
	target_position += camera_y * y_dis;

	CalculateViewMatrix(&m_viewMatrix);
	m_Device->SetTransform(D3DTS_VIEW, &m_viewMatrix);
}

void Camera::zMove(float z_dis) {
	camera_poition += camera_z * z_dis;
	target_position += camera_z * z_dis;

	CalculateViewMatrix(&m_viewMatrix);
	m_Device->SetTransform(D3DTS_VIEW, &m_viewMatrix);
}

void Camera::xRoation(float x_angle){
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &camera_x, x_angle);
	D3DXVec3TransformCoord(&camera_y, &camera_y, &R);
	D3DXVec3TransformCoord(&camera_z, &camera_z, &R);

	target_position = camera_z * D3DXVec3Length(&camera_poition);

	CalculateViewMatrix(&m_viewMatrix);
	m_Device->SetTransform(D3DTS_VIEW, &m_viewMatrix);
}

void Camera::yRoation(float y_angle){
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &camera_y, y_angle);
	D3DXVec3TransformCoord(&camera_x, &camera_x, &R);
	D3DXVec3TransformCoord(&camera_z, &camera_z, &R);

	target_position = camera_z * D3DXVec3Length(&camera_poition);

	CalculateViewMatrix(&m_viewMatrix);
	m_Device->SetTransform(D3DTS_VIEW, &m_viewMatrix);
}

void Camera::zRoation(float z_angle){
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &camera_z, z_angle);
	D3DXVec3TransformCoord(&camera_x, &camera_x, &R);
	D3DXVec3TransformCoord(&camera_y, &camera_y, &R);

	target_position = camera_z * D3DXVec3Length(&camera_poition);

	CalculateViewMatrix(&m_viewMatrix);
	m_Device->SetTransform(D3DTS_VIEW, &m_viewMatrix);
}

void Camera::CalculateViewMatrix(D3DXMATRIX *pMatrix) {

	D3DXVec3Normalize(&camera_z, &camera_z); 
	D3DXVec3Cross(&camera_y, &camera_z, &camera_x);  
	D3DXVec3Normalize(&camera_y, &camera_y);            
	D3DXVec3Cross(&camera_x, &camera_y, &camera_z);   
	D3DXVec3Normalize(&camera_x, &camera_x);        

	pMatrix->_11 = camera_x.x;        
	pMatrix->_12 = camera_y.x;         
	pMatrix->_13 = camera_z.x;         
	pMatrix->_14 = 0.0f;

	pMatrix->_21 = camera_x.y;         
	pMatrix->_22 = camera_y.y;         
	pMatrix->_23 = camera_z.y;         
	pMatrix->_24 = 0.0f;

	pMatrix->_31 = camera_x.z;       
	pMatrix->_32 = camera_y.z;         
	pMatrix->_33 = camera_z.z;          
	pMatrix->_34 = 0.0f;

	pMatrix->_41 = -D3DXVec3Dot(&camera_x, &camera_poition);
	pMatrix->_42 = -D3DXVec3Dot(&camera_y, &camera_poition); 
	pMatrix->_43 = -D3DXVec3Dot(&camera_z, &camera_poition);  
	pMatrix->_44 = 1.0f;
}

void Camera::Shutdown() {
	m_Device->Release();
}
