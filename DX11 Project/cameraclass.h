////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
private:
	struct ColliderType
	{
		float Mx, mx;
		float My, my;
		float Mz, mz;
	};
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void Render(float,float, float, float, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, float);
	void GetViewMatrix(D3DXMATRIX&);

	D3DXVECTOR3 camPosition;
	D3DXVECTOR3 camTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	D3DXVECTOR3 camUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 camForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 camRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	void setCollider();
	void setSize(float, float, float);
	bool checkCollider(float, float, float, float, float, float);
	void Shutdown();

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	D3DXMATRIX m_viewMatrix;

	ColliderType* m_collider;
	float sizX, sizY, sizZ;
};

#endif