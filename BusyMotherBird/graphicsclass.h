////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"

#include "textureshaderclass.h"
#include "bitmapclass.h"

#include "textclass.h"

#include <cmath>
/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 2000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	bool Frame(int, int, float);

	float moveLeftRight = 0.0f;
	float moveBackForward = 0.0f;

	float camRotateInfoYaw = 0.0f;
	float camRotateInfoPitch = 0.0f;

	float playerYaw = 0.0f;
	float playerPitch = 0.0f;
	float playerRoll = 0.0f;

	bool isCPressed = false;

	float camYaw = 0.0f;
	float camPitch = 0.0f;

	D3DXVECTOR3 desiredCharDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 playerPosition = D3DXVECTOR3(0.0f, 50.0f, 300.0f);

	D3DXVECTOR3 nestPosition = D3DXVECTOR3(55.0f, 53.0f, 10.0f);

	D3DXVECTOR3 crossForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 crossRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	bool grab = false;
	bool isCollide;
	bool isFood;//먹이 들고있는지 확인하는거*******************************************************
	bool sound;
	bool win;
	bool lose;

	void YawRotation(float);
	void RollRotation(float);
	void PitchRotation(float);

private:
	bool Render();
	D3DXMATRIX MoveChar(float, float, float, float, float, D3DXVECTOR3, D3DXVECTOR3, D3DXMATRIX&);
	float CrossLookAt(D3DXVECTOR3, D3DXVECTOR3);

private:
	D3DClass* m_D3D;
	ModelClass* m_Island;
	ModelClass* m_Cloud;
	ModelClass* m_Tree;
	ModelClass* m_Rock;
	ModelClass* m_Mushroom;
	ModelClass* m_Nest;
	ModelClass* m_Cross;

	ModelClass* m_Player;

	ModelClass* m_SkyBox;

	int num_island = 0;
	int num_cloud = 0;
	int num_tree = 0;
	int num_rock = 0;
	int num_mushroom = 0;
	int num_total = 0;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	CameraClass* m_Camera;

	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;

	TextClass* m_Text;
	float m_time;
	float frameTime = 0.0f;
	float m_hunger;//배고픔 수치 여기에 추가함*****************************************************
	
	float m_indexCount;

	TextClass* m_result;

	D3DXVECTOR3 DefaultForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 DefaultRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXVECTOR3 CamDefaultForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 CamDefaultRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXVECTOR3 playerTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	D3DXVECTOR3 playerUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 playerForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 playerRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXVECTOR3 RotateYaw = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 RotatePitch = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 RotateRoll = D3DXVECTOR3(0.0f, 0.0f, 1.0f);


	/*D3DXVECTOR3 currCharDirection = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 oldCharDirection = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 charPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);*/

	float charCamDist = 50.0f;


	D3DXMATRIX transMatrix_Player;
	D3DXMATRIX rotateMatrix_Player;

	D3DXMATRIX scaleMatrix_Player;

	D3DXQUATERNION Quat_Rot;
};

#endif