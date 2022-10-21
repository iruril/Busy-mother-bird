////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_collider = new ColliderType;//콜라이더 타입 변수 추가
	sizX = sizY = sizZ = 0.0f;//카메라 사이즈 변수 추가
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	camPosition.x = x;
	camPosition.y = y;
	camPosition.z = z;
	return;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	camTarget.x = x;
	camTarget.y = y;
	camTarget.z = z;
	return;
}


D3DXVECTOR3 CameraClass::GetPosition()
{
	return D3DXVECTOR3(camPosition.x, camPosition.y, camPosition.z);
}


D3DXVECTOR3 CameraClass::GetRotation()
{
	return D3DXVECTOR3(camTarget.x, camTarget.y, camTarget.z);
}

void CameraClass::Render(float camYaw, float camPitch, float moveLeftRight, float moveBackForward,
						 D3DXVECTOR3 DefaultForward, D3DXVECTOR3 DefalutRight, D3DXVECTOR3 charPosition, float charCamDist)
{
	D3DXMATRIX camRotationMatrix;

	/*D3DXMatrixRotationYawPitchRoll(&camRotationMatrix, camYaw, camPitch, 0);
	D3DXVec3TransformNormal(&camTarget, &DefalutForward, &camRotationMatrix);

	D3DXVec3TransformCoord(&camRight, &DefalutRight, &camRotationMatrix);
	D3DXVec3TransformCoord(&camForward, &DefalutForward, &camRotationMatrix);
	D3DXVec3Cross(&camUp, &camForward, &camRight);

	camPosition += moveLeftRight * camRight;
	camPosition += moveBackForward * camForward;

	camTarget = camPosition + camTarget;

	D3DXMatrixLookAtLH(&m_viewMatrix, &camPosition, &camTarget, &camUp);*/

	camTarget = charPosition;

	camTarget.y = camTarget.y + 10.0f;

	D3DXMatrixRotationYawPitchRoll(&camRotationMatrix, camYaw, camPitch, 0);
	D3DXVec3TransformNormal(&camPosition, &DefaultForward, &camRotationMatrix);
	D3DXVec3Normalize(&camPosition, &camPosition);

	camPosition.x = (camPosition.x * charCamDist) + camTarget.x;
	camPosition.y = (camPosition.y * charCamDist) + camTarget.y;
	camPosition.z = (camPosition.z * charCamDist) + camTarget.z;

	D3DXVECTOR3 Tar_Pos = camTarget - camPosition;
	D3DXVec3Normalize(&camForward, &Tar_Pos);   
	//camForward.y = 0.0f;   

	D3DXVec3Normalize(&camForward, &camForward);
	camRight = D3DXVECTOR3(-camForward.z, 0.0f, camForward.x);

	D3DXVECTOR3 Pos_Tar = camPosition - camTarget;
	D3DXVec3Normalize(&Pos_Tar, &Pos_Tar);

	D3DXVec3Normalize(&camUp, D3DXVec3Cross(&Pos_Tar, &Pos_Tar, &camRight));

	D3DXMatrixLookAtLH(&m_viewMatrix, &camPosition, &camTarget, &camUp);
	return;
}


void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}

void CameraClass::setCollider()//콜라이더 설정 추가
{
	m_collider->Mx = camPosition.x + sizX / 2;
	m_collider->mx = camPosition.x - sizX / 2;
	m_collider->My = camPosition.y + sizY / 2;
	m_collider->my = camPosition.y - sizY / 2;
	m_collider->Mz = camPosition.z + sizZ / 2;
	m_collider->mz = camPosition.z - sizZ / 2;
}

void CameraClass::setSize(float x, float y, float z)//카메라 사이즈 설정 추가
{
	sizX = x; sizY = y; sizZ = z;
}

bool CameraClass::checkCollider(float max, float mix, float may, float miy, float maz, float miz)//충돌 체크 함수 추가, 충돌 시 트루, 그 외 펄스
{
	if ((mix <= m_collider->Mx && m_collider->Mx <= max) || (mix <= m_collider->mx && m_collider->mx <= max))
	{
		if ((miy <= m_collider->My && m_collider->My <= may) || (miy <= m_collider->my && m_collider->my <= may))
		{
			if ((miz <= m_collider->Mz && m_collider->Mz <= maz) || (miz <= m_collider->mz && m_collider->mz <= maz))
			{
				return true;
			}
		}
	}

	return false;
}

void CameraClass::Shutdown()//릴리즈용 셧다운 함수 추가
{
	if (m_collider)
	{
		delete m_collider;
		m_collider = 0;
	}
}