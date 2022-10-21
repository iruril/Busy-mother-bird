////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Island = 0;
	m_Cloud = 0;
	m_Tree = 0;
	m_Rock = 0;
	m_Mushroom = 0;
	m_Nest = 0;
	m_Cross = 0;

	m_LightShader = 0;

	m_Light = 0;

	m_TextureShader = 0;
	m_Bitmap = 0;

	m_Text = 0;
	m_time = 0.0f;
	m_hunger = 100.0f;//난이도 조절 배고픔수치-------------------------------------------
	isFood = false;//먹이는 맨처음엔 안들고 있음
	m_indexCount = 0.0f;

	m_SkyBox = 0;

	m_Player = 0;

	m_result = 0;
	sound = false;

	win = false;
	lose = false;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	D3DXMATRIX baseViewMatrix;
	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	//카메라 사이즈 초기화 추가***********************************************************************
	//************************************************************************************************
	m_Camera->setSize(0.5f, 0.5f, 0.5f);//************************************************************

	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	/// <island>
	/// /////////////////////////////////////////
	m_Island = new ModelClass;
	if(!m_Island)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Island->Initialize(m_D3D->GetDevice(), (char*)"./models/island.obj", (WCHAR*)L"./models/Textures/island.dds");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	/// <cloud>
	/// /////////////////////////////////////////
	m_Cloud = new ModelClass;
	if (!m_Cloud)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Cloud->Initialize(m_D3D->GetDevice(), (char*)"./models/cloud.obj", (WCHAR*)L"./models/Textures/cloud.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	/// <tree>
	/// ////////////////////////////////////////
	m_Tree = new ModelClass;
	if (!m_Tree)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Tree->Initialize(m_D3D->GetDevice(), (char*)"./models/SmallTree.obj", (WCHAR*)L"./models/Textures/SmallTree.dds");
	
	/// <rock>
	/// ///////////////////////////////////////
	m_Rock = new ModelClass;
	if (!m_Rock)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Rock->Initialize(m_D3D->GetDevice(), (char*)"./models/Rocks.obj", (WCHAR*)L"./models/Textures/Rocks.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	/// <mushroom>
	/// ///////////////////////////////////////
	m_Mushroom = new ModelClass;
	if (!m_Mushroom)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Mushroom->Initialize(m_D3D->GetDevice(), (char*)"./models/Mushrooms1.obj", (WCHAR*)L"./models/Textures/Mushrooms1.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	/// <nest>
	/// ///////////////////////////////////////
	m_Nest = new ModelClass;
	if (!m_Nest)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Nest->Initialize(m_D3D->GetDevice(), (char*)"./models/nest.obj", (WCHAR*)L"./models/Textures/nest.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	/// <Cross>
	/// ///////////////////////////////////////
	m_Cross = new ModelClass;
	if (!m_Nest)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Cross->Initialize(m_D3D->GetDevice(), (char*)"./models/cross.obj", (WCHAR*)L"./models/Textures/cross.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	

	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////

	m_SkyBox = new ModelClass;
	if (!m_SkyBox)
	{
		return false;
	}

	// Initialize the model object.
	result = m_SkyBox->Initialize(m_D3D->GetDevice(), (char*)"./models/skybox.obj", (WCHAR*)L"./models/Textures/skybox3.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////


	// <Player>

	m_Player = new ModelClass;
	if (!m_Player)
	{
		return false;
	}

	result = m_Player->Initialize(m_D3D->GetDevice(), (char*)"./models/bird.obj", (WCHAR*)L"./models/Textures/bird.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////
	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-1.0f, -1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, (WCHAR*)L"./models/Textures/bitmap.dds", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	m_Camera->Render(playerYaw, playerPitch, moveLeftRight, moveBackForward, CamDefaultForward, CamDefaultRight, playerPosition, charCamDist);
	m_Camera->GetViewMatrix(baseViewMatrix);
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	m_result = new TextClass;
	if (!m_result)
	{
		return false;
	}

	// Initialize the text object.
	result = m_result->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if(m_Island)
	{
		m_Island->Shutdown();
		delete m_Island;
		m_Island = 0;
	}
	if (m_Cloud)
	{
		m_Cloud->Shutdown();
		delete m_Cloud;
		m_Cloud = 0;
		
	}
	if (m_Tree)
	{
		m_Tree->Shutdown();
		delete m_Tree;
	}
	if (m_Rock)
	{
		m_Rock->Shutdown();
		delete m_Rock;
		m_Rock = 0;
	}
	if (m_Mushroom)
	{
		m_Mushroom->Shutdown();
		delete m_Mushroom;
		m_Mushroom = 0;
	}

	if (m_SkyBox)
	{
		m_SkyBox->Shutdown();
		delete m_SkyBox;
		m_SkyBox = 0;
	}

	if (m_Player)
	{
		m_Player->Shutdown();
		delete m_Player;
		m_Player = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		m_Camera->Shutdown();//카메라 콜라이더 릴리즈용 셧다운 함수 추가
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}
	
	if (m_result)
	{
		m_result->Shutdown();
		delete m_result;
		m_result = 0;
	}
	return;
}


bool GraphicsClass::Frame()
{
	bool result;
	
	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}
float chk = 0;
bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;
	this->frameTime = frameTime;
	//m_time += 0.25f / frameTime;
	if (fps <= 0)
	{
		m_time = 0;
	}
	else
	{
		m_time += 1.0f / fps;
		m_hunger -= 2.0f / fps;//배고픔 초당 1씩 하락
	}
	
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetTime(m_time, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetHunger(m_hunger, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	
	result = m_Text->SetObject(num_total + 2, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetScreen(m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetPolygon(m_indexCount, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	if (m_hunger < 1 && !win)
	{
		lose = true;
	}
	else if (m_time >= 60 && !lose)//난이도 조절(승리조건)-------------------------------------------------------
	{
		win = true;
	}
	result = m_result->SetResult(m_D3D->GetDeviceContext(), win, lose);
	if (!result)
	{
		return false;
	}
	// Render the graphics scene.
	result = Render();
	//printf("fps : %d, cpu : %d, fps/fT : %.2f, fT : %.2f\n", fps, cpu, fps / frameTime, frameTime);
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render()
{
	m_indexCount = m_Island->getPolygon() * num_island
					+ m_Cloud->getPolygon() * num_cloud + m_Tree->getPolygon() * num_tree
					+ m_Rock->getPolygon() * num_rock + m_Mushroom->getPolygon() * num_mushroom
					+ m_Player->getPolygon() + m_Nest->getPolygon() + m_Cross->getPolygon();

	D3DXMATRIX worldMatrix_Player;

	D3DXMATRIX worldMatrix_Nest;
	D3DXMATRIX transMatrix_Nest;
	D3DXMATRIX scaleMatrix_Nest;
	D3DXMATRIX rotateMatrix_Nest;

	D3DXMATRIX worldMatrix_Cross;
	D3DXMATRIX transMatrix_Cross;
	D3DXMATRIX scaleMatrix_Cross;
	D3DXMATRIX rotateMatrix_Cross;

	D3DXMATRIX TextRotate;
	D3DXMATRIX TextScale;
	D3DXMatrixRotationY(&TextRotate, 3.141562f);
	D3DXMatrixScaling(&TextScale, 1.5f, 1.2f, 1.0f);

	D3DXMATRIX worldMatrix_Island[10], worldMatrix, worldMatrix2, viewMatrix, projectionMatrix, orthoMatrix;//worldMatrix 단품 또 추가
	D3DXMATRIX worldMatrix_Cloud[10];
	D3DXMATRIX worldMatrix_Tree[10];
	D3DXMATRIX worldMatrix_Rock[10];
	D3DXMATRIX worldMatrix_Mushroom[10];

	D3DXMATRIX rotateMatrix_island[10];
	D3DXMATRIX rotateMatrix_Cloud[10];
	D3DXMATRIX rotateMatrix_Tree[10];
	D3DXMATRIX rotateMatrix_Rock[10];
	D3DXMATRIX rotateMatrix_Mushroom[10];

	D3DXMATRIX transMatrix_island[10];
	D3DXMATRIX transMatrix_Cloud[10];
	D3DXMATRIX transMatrix_Tree[10];
	D3DXMATRIX transMatrix_Rock[10];
	D3DXMATRIX transMatrix_Mushroom[10];

	D3DXMATRIX scaleMatrix_island[10];
	D3DXMATRIX scaleMatrix_Cloud[10];
	D3DXMATRIX scaleMatrix_Tree[10];
	D3DXMATRIX scaleMatrix_Rock[10];
	D3DXMATRIX scaleMatrix_Mushroom[10];

	D3DXMATRIX worldMatrix_skybox;
	D3DXMATRIX transMatrix_skybox;
	D3DXMATRIX scaleMatrix_skybox;

	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.55f, 0.55f, 1.00f, 1.0f);


	// Generate the view matrix based on the camera's position.
	m_Camera->Render(camYaw, camPitch, moveLeftRight, moveBackForward, CamDefaultForward, CamDefaultRight, playerPosition, charCamDist);

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);//추가한 부분
	m_D3D->GetWorldMatrix(worldMatrix2);//또 추가한 부분
	m_D3D->GetWorldMatrix(worldMatrix_skybox); //skybox 월드
	m_D3D->GetWorldMatrix(worldMatrix_Player);
	m_D3D->GetWorldMatrix(worldMatrix_Nest);
	m_D3D->GetWorldMatrix(worldMatrix_Cross);

	for (int i = 0; i < num_island; i++) {
		m_D3D->GetWorldMatrix(worldMatrix_Island[i]);
	}
	for (int i = 0; i < num_cloud; i++) {
		m_D3D->GetWorldMatrix(worldMatrix_Cloud[i]);
	}
	for (int i = 0; i < num_tree; i++) {
		m_D3D->GetWorldMatrix(worldMatrix_Tree[i]);
	}
	for (int i = 0; i < num_rock; i++) {
		m_D3D->GetWorldMatrix(worldMatrix_Rock[i]);
	}
	for (int i = 0; i < num_mushroom; i++) {
		m_D3D->GetWorldMatrix(worldMatrix_Mushroom[i]);
	}
	m_D3D->GetProjectionMatrix(projectionMatrix);
	//추가한 부분 시작
	m_D3D->GetOrthoMatrix(orthoMatrix);

	m_D3D->TurnOffCulling();
	/// <skybox>
	D3DXVECTOR3 Camera_Pos = m_Camera->GetPosition();
	D3DXVECTOR3 Camera_Rotate = m_Camera->GetRotation();

	/// <플레이어 이동>
	/// ////////

	if (!isCPressed) {
		if (camRotateInfoYaw != 0.0f) {
			camYaw = 0.0f;
			camYaw = camRotateInfoYaw;
			camRotateInfoYaw = 0.0f;
		}
		if (camRotateInfoPitch != 0.0f) {
			camPitch = 0.0f;
			camPitch = camRotateInfoPitch;
			camRotateInfoPitch = 0.0f;
		}

		playerYaw = camYaw;
		playerPitch = camPitch;
	}

	if (isCPressed) {
		camRotateInfoYaw = playerYaw;
		camRotateInfoPitch = playerPitch;
	}


	D3DXMatrixScaling(&scaleMatrix_Player, 2.0f, 2.0f, 2.0f);
	rotateMatrix_Player = MoveChar(playerYaw, playerPitch, playerRoll, moveLeftRight, moveBackForward, DefaultForward, DefaultRight, worldMatrix_Player);
	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	m_Player->SetCollider(playerPosition.x, playerPosition.y, playerPosition.z);
	/// ////////


	D3DXMatrixScaling(&scaleMatrix_skybox, 1000.0f, 1000.0f+200.0f, 1000.0f);
	D3DXMatrixTranslation(&transMatrix_skybox, Camera_Pos.x, Camera_Pos.y, Camera_Pos.z);

	worldMatrix_skybox = scaleMatrix_skybox * transMatrix_skybox;

	m_SkyBox->Render(m_D3D->GetDeviceContext());

	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_SkyBox->GetIndexCount(), worldMatrix_skybox, viewMatrix, projectionMatrix, m_SkyBox->GetTexture());
	if (!result)
	{
		return false;
	}
	m_D3D->TurnOnCulling();

	/// ////////

	m_D3D->TurnZBufferOff();

	/*result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
	if (!result)
	{
		return false;
	}
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}*/

	m_D3D->TurnZBufferOn();
	//추가한 부분 끝

	/// <Island>
	/// ////////
	D3DXMatrixScaling(&scaleMatrix_island[0], 1.0f, 1.0f, 1.0f);
	D3DXMatrixRotationY(&rotateMatrix_island[0], 0);
	D3DXMatrixTranslation(&transMatrix_island[0], 0.0f, 0.0f, 0.0f);

	D3DXMatrixScaling(&scaleMatrix_island[1], 0.5f, 0.5f, 0.5f);
	D3DXMatrixRotationY(&rotateMatrix_island[1], -15);
	D3DXMatrixTranslation(&transMatrix_island[1], -20.0f, -20.0f, -60.0f);

	D3DXMatrixScaling(&scaleMatrix_island[2], 0.75f, 0.75f, 0.75f);
	D3DXMatrixRotationY(&rotateMatrix_island[2], 35);
	D3DXMatrixTranslation(&transMatrix_island[2], 150.0f, -15.0f, 160.0f);

	D3DXMatrixScaling(&scaleMatrix_island[3], 0.60f, 0.60f, 0.60f);
	D3DXMatrixRotationY(&rotateMatrix_island[3], 10);
	D3DXMatrixTranslation(&transMatrix_island[3], -160.0f, -25.0f, -80.0f);

	D3DXMatrixScaling(&scaleMatrix_island[4], 0.35f, 0.35f, 0.35f);
	D3DXMatrixRotationY(&rotateMatrix_island[4], -25);
	D3DXMatrixTranslation(&transMatrix_island[4], 180.0f, -25.0f, 100.0f);

	D3DXMatrixScaling(&scaleMatrix_island[5], 0.75f, 0.75f, 0.75f);
	D3DXMatrixRotationY(&rotateMatrix_island[5], 20);
	D3DXMatrixTranslation(&transMatrix_island[5], -20.0f, -30.0f, 200.0f);

	D3DXMatrixScaling(&scaleMatrix_island[6], 0.25f, 0.25f, 0.25f);
	D3DXMatrixRotationY(&rotateMatrix_island[6], 46);
	D3DXMatrixTranslation(&transMatrix_island[6], -120.0f, 10.0f, 200.0f);


	num_island = 7;

	/// <Cloud>
	/// ////////
	D3DXMatrixScaling(&scaleMatrix_Cloud[0], 1.0f, 1.0f, 1.0f);
	D3DXMatrixRotationY(&rotateMatrix_Cloud[0], 30);
	D3DXMatrixTranslation(&transMatrix_Cloud[0], 80.0f, -40.0f, -100.0f);

	D3DXMatrixScaling(&scaleMatrix_Cloud[1], 1.2f, 1.2f, 1.2f);
	D3DXMatrixRotationY(&rotateMatrix_Cloud[1], 90);
	D3DXMatrixTranslation(&transMatrix_Cloud[1], -150.0f, -40.0f, 100.0f);

	D3DXMatrixScaling(&scaleMatrix_Cloud[2], 0.7f, 0.7f, 0.7f);
	D3DXMatrixRotationY(&rotateMatrix_Cloud[2], 20);
	D3DXMatrixTranslation(&transMatrix_Cloud[2], -80.0f, -50.0f, -120.0f);

	D3DXMatrixScaling(&scaleMatrix_Cloud[3], 1.6f, 1.2f, 1.7f);
	D3DXMatrixRotationY(&rotateMatrix_Cloud[3], 46);
	D3DXMatrixTranslation(&transMatrix_Cloud[3], 250.0f, 40.0f, 250.0f);

	D3DXMatrixScaling(&scaleMatrix_Cloud[4], 1.8f, 1.3f, 1.8f);
	D3DXMatrixRotationY(&rotateMatrix_Cloud[4], 123);
	D3DXMatrixTranslation(&transMatrix_Cloud[4], -200.0f, 40.0f, -270.0f);

	D3DXMatrixScaling(&scaleMatrix_Cloud[5], 1.5f, 1.2f, 1.8f);
	D3DXMatrixRotationY(&rotateMatrix_Cloud[5], 56);
	D3DXMatrixTranslation(&transMatrix_Cloud[5], -290.0f, 20.0f, 230.0f);

	num_cloud = 6;

	/// <Tree>
	/// ///////
	D3DXMatrixScaling(&scaleMatrix_Tree[0], 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&rotateMatrix_Tree[0], -10);
	D3DXMatrixTranslation(&transMatrix_Tree[0], -15.0f, 8.0f, -25.0f);

	D3DXMatrixScaling(&scaleMatrix_Tree[1], 0.15f, 0.15f, 0.15f);
	D3DXMatrixRotationY(&rotateMatrix_Tree[1], 20);
	D3DXMatrixTranslation(&transMatrix_Tree[1], 50.0f, 5.0f, 10.0f);

	D3DXMatrixScaling(&scaleMatrix_Tree[2], 0.12f, 0.12f, 0.12f);
	D3DXMatrixRotationY(&rotateMatrix_Tree[2], -6);
	D3DXMatrixTranslation(&transMatrix_Tree[2], -50.0f, 6.2f, 40.0f);

	D3DXMatrixScaling(&scaleMatrix_Tree[3], 0.12f, 0.12f, 0.12f);
	D3DXMatrixRotationY(&rotateMatrix_Tree[3], -56);
	D3DXMatrixTranslation(&transMatrix_Tree[3], -20.0f, -26.4f, 200.0f);

	D3DXMatrixScaling(&scaleMatrix_Tree[4], 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&rotateMatrix_Tree[4], 46);
	D3DXMatrixTranslation(&transMatrix_Tree[4], -120.0f, 12.0f, 200.0f);

	num_tree = 5;

	/// <Rock>
	/// ///////
	D3DXMatrixScaling(&scaleMatrix_Rock[0], 0.2f, 0.2f, 0.2f);
	D3DXMatrixRotationY(&rotateMatrix_Rock[0], 5);
	D3DXMatrixTranslation(&transMatrix_Rock[0], -80.0f, 7.0f, 0.0f);

	D3DXMatrixScaling(&scaleMatrix_Rock[1], 0.15f, 0.15f, 0.15f);
	D3DXMatrixRotationY(&rotateMatrix_Rock[1], -10);
	D3DXMatrixTranslation(&transMatrix_Rock[1], 50.0f, 5.0f, -20.0f);

	D3DXMatrixScaling(&scaleMatrix_Rock[2], 0.2f, 0.2f, 0.2f);
	D3DXMatrixRotationY(&rotateMatrix_Rock[2], -15);
	D3DXMatrixTranslation(&transMatrix_Rock[2], 130.0f, -15.0f, 160.0f);

	D3DXMatrixScaling(&scaleMatrix_Rock[3], 0.35f, 0.35f, 0.35f);
	D3DXMatrixRotationY(&rotateMatrix_Rock[3], -25);
	D3DXMatrixTranslation(&transMatrix_Rock[3], -20.0f, 0.0f, 20.0f);

	D3DXMatrixScaling(&scaleMatrix_Rock[4], 0.15f, 0.15f, 0.15f);
	D3DXMatrixRotationY(&rotateMatrix_Rock[4], -17);
	D3DXMatrixTranslation(&transMatrix_Rock[4], -190.0f, -22.0f, -80.0f);

	D3DXMatrixScaling(&scaleMatrix_Rock[5], 0.15f, 0.15f, 0.15f);
	D3DXMatrixRotationY(&rotateMatrix_Rock[5], -123);
	D3DXMatrixTranslation(&transMatrix_Rock[5], -40.0f, -25.0f, 200.0f);

	D3DXMatrixScaling(&scaleMatrix_Rock[6], 0.20f, 0.20f, 0.20f);
	D3DXMatrixRotationY(&rotateMatrix_Rock[6], 23);
	D3DXMatrixTranslation(&transMatrix_Rock[6], 15.0f, -30.0f, 180.0f);

	D3DXMatrixScaling(&scaleMatrix_Rock[7], 0.1f, 0.07f, 0.1f);
	D3DXMatrixRotationY(&rotateMatrix_Rock[7], 65);
	D3DXMatrixTranslation(&transMatrix_Rock[7], -120.0f, 12.0f, 200.0f);

	num_rock = 8;

	/// <Mushroom>
	/// ///////
	D3DXMatrixScaling(&scaleMatrix_Mushroom[0], 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationY(&rotateMatrix_Mushroom[0], 0);
	D3DXMatrixTranslation(&transMatrix_Mushroom[0], 45.0f, 6.0f, 15.0f);
	
	D3DXMatrixScaling(&scaleMatrix_Mushroom[1], 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationY(&rotateMatrix_Mushroom[1], 5);
	D3DXMatrixTranslation(&transMatrix_Mushroom[1], -10.0f, -14.0f, -60.0f);

	D3DXMatrixScaling(&scaleMatrix_Mushroom[2], 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationY(&rotateMatrix_Mushroom[2], 13);
	D3DXMatrixTranslation(&transMatrix_Mushroom[2], -10.0f, -25.0f, 200.0f);

	D3DXMatrixScaling(&scaleMatrix_Mushroom[3], 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationY(&rotateMatrix_Mushroom[3], 45);
	D3DXMatrixTranslation(&transMatrix_Mushroom[3], -110.0f, 12.0f, 210.0f);

	D3DXMatrixScaling(&scaleMatrix_Mushroom[4], 0.025f, 0.025f, 0.025f); //들고있는 버섯
	D3DXMatrixRotationY(&rotateMatrix_Mushroom[4], 5);
	D3DXMatrixTranslation(&transMatrix_Mushroom[4], 0.0f, -2.0f, 0.0f);
	if (isFood)//먹이를 물고있다면*******************************************************************
	{
		worldMatrix_Mushroom[4] = scaleMatrix_Mushroom[4] * transMatrix_Mushroom[4] * rotateMatrix_Player * transMatrix_Player;
	}
	else//먹이가 없다면*****************************************************************************
	{
		worldMatrix_Mushroom[4] = scaleMatrix_Mushroom[4] * rotateMatrix_Mushroom[4] * transMatrix_Mushroom[4];
	}

	num_mushroom = 5;

	num_total = num_island + num_cloud + num_tree + num_rock + num_mushroom;
	/// <Cross>
	/// ///////
	D3DXMatrixScaling(&scaleMatrix_Cross, 4.0f, 4.0f, 4.0f);
	D3DXMatrixTranslation(&transMatrix_Cross, 0.0f, 8.0f, 0.0f);

	float nest_Dir = CrossLookAt(nestPosition, playerPosition);
	D3DXMatrixRotationY(&rotateMatrix_Cross, nest_Dir);

	worldMatrix_Cross = scaleMatrix_Cross * rotateMatrix_Cross * transMatrix_Player * transMatrix_Cross;

	/// <Nest>
	/// ///////
	D3DXMatrixScaling(&scaleMatrix_Nest, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationY(&rotateMatrix_Nest, 5);
	D3DXMatrixTranslation(&transMatrix_Nest, nestPosition.x, nestPosition.y, nestPosition.z);

	worldMatrix_Nest = scaleMatrix_Nest * rotateMatrix_Nest * transMatrix_Nest;
	m_Nest->SetCollider(scaleMatrix_Nest, transMatrix_Nest);//colliderSet

	isCollide = m_Player->checkCollider(m_Nest->GetMaxX(), m_Nest->GetMinX(), m_Nest->GetMaxY(),
		m_Nest->GetMinY(), m_Nest->GetMaxZ(), m_Nest->GetMinZ());
	if (isCollide)
	{
		if (isFood)//먹이를 물고있다면
		{
			m_hunger += 10.0f;//난이도 조절 배부름증가량---------------------------------------------
			isFood = false;//먹이는 내려두고
			grab = false;
		}
		else//먹이가 없다면
		{
			printf("먹이 없음\n");
		}
	}

	////////////////////////////////////////////////////////////////////////
	m_Camera->setCollider();//카메라 콜라이더 설정 함수 및 각 모델 콜라이더 설정 추가**********************************

	for (int i = 0; i < num_island; i++) {
		worldMatrix_Island[i] = scaleMatrix_island[i] * rotateMatrix_island[i] * transMatrix_island[i]; 
		m_Island->SetCollider(scaleMatrix_island[i], transMatrix_island[i]);//colliderSet
	}
	for (int i = 0; i < num_cloud; i++) {
		worldMatrix_Cloud[i] = scaleMatrix_Cloud[i] * rotateMatrix_Cloud[i] * transMatrix_Cloud[i];
		m_Cloud->SetCollider(scaleMatrix_Cloud[i], transMatrix_Cloud[i]);//colliderSet
	}
	for (int i = 0; i < num_tree; i++) {
		worldMatrix_Tree[i] = scaleMatrix_Tree[i] * rotateMatrix_Tree[i] * transMatrix_Tree[i];
		m_Tree->SetCollider(scaleMatrix_Tree[i], transMatrix_Tree[i]);//colliderSet
	}
	for (int i = 0; i < num_rock; i++) {
		worldMatrix_Rock[i] = scaleMatrix_Rock[i] * rotateMatrix_Rock[i] * transMatrix_Rock[i];
		m_Rock->SetCollider(scaleMatrix_Rock[i], transMatrix_Rock[i]);//colliderSet
	}
	for (int i = 0; i < num_mushroom - 1; i++) {
		worldMatrix_Mushroom[i] = scaleMatrix_Mushroom[i] * rotateMatrix_Mushroom[i] * transMatrix_Mushroom[i];
		m_Mushroom->SetCollider(scaleMatrix_Mushroom[i], transMatrix_Mushroom[i]);//colliderSet

		isCollide = m_Player->checkCollider(m_Mushroom->GetMaxX(), m_Mushroom->GetMinX(), m_Mushroom->GetMaxY(),
					m_Mushroom->GetMinY(), m_Mushroom->GetMaxZ(), m_Mushroom->GetMinZ());

		if (isCollide && grab)//버섯 콜라이더 충돌 체크 함수 추가
		{
			if (!isFood)//먹이를 물 입이 비었다면**************************************************************
			{
				isFood = true;//버섯에 닿았을때 먹이를 물었다고 볼수 있다**************************************
				sound = true;
				printf("먹이를 물었다\n");
			}
			else//먹이를 이미 물고있다면***********************************************************************
			{
				printf("버섯과 충돌함\n");
			}
		}

		worldMatrix = TextRotate;
		worldMatrix2 = TextScale * TextRotate;

	}

	/// nest
	/// ///////////////////////////////////////////////////////
	m_Nest->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Nest->GetIndexCount(), worldMatrix_Nest, viewMatrix, projectionMatrix,
		m_Nest->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_Nest);

	/// player
	/// ///////////////////////////////////////////////////////
	m_Player->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Player->GetIndexCount(), worldMatrix_Player, viewMatrix, projectionMatrix,
		m_Player->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_Player);

	/// Cross
	/// ///////////////////////////////////////////////////////
	m_Cross->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Cross->GetIndexCount(), worldMatrix_Cross, viewMatrix, projectionMatrix,
		m_Cross->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_Cross);

	/// island
	/// ///////////////////////////////////////////////////////
	for (int i = 0; i < num_island; i++) { 
		m_Island->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Island->GetIndexCount(), worldMatrix_Island[i], viewMatrix, projectionMatrix,
			m_Island->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_island[i]);
		if (!result)
		{
			return false;
		}
	}
	/// cloud
	////////////////////////////////////////////////////////////
	for (int i = 0; i < num_cloud; i++) {
		m_Cloud->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Cloud->GetIndexCount(), worldMatrix_Cloud[i], viewMatrix, projectionMatrix,
			m_Cloud->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_Cloud[i]);
		if (!result)
		{
			return false;
		}
	}
	/// tree
	/// ////////////////////////////////////////////////////////
	for (int i = 0; i < num_tree; i++) {
		m_Tree->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Tree->GetIndexCount(), worldMatrix_Tree[i], viewMatrix, projectionMatrix,
			m_Tree->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_Tree[i]);
		if (!result)
		{
			return false;
		}
	}
	/// rock
	/// ///////////////////////////////////////////////////////////
	for (int i = 0; i < num_rock; i++) {
		m_Rock->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Rock->GetIndexCount(), worldMatrix_Rock[i], viewMatrix, projectionMatrix,
			m_Rock->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_Rock[i]);
		if (!result)
		{
			return false;
		}
	}
	/// mushroom
	/// ///////////////////////////////////////////////////////////
	for (int i = 0; i < num_mushroom; i++) {
		m_Mushroom->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Mushroom->GetIndexCount(), worldMatrix_Mushroom[i], viewMatrix, projectionMatrix,
			m_Mushroom->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_Mushroom[i]);
		if (!result)
		{
			return false;
		}
	}
	
	m_D3D->TurnZBufferOff();
	m_D3D->TurnOnAlphaBlending();
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	result = m_result->Render(m_D3D->GetDeviceContext(), worldMatrix2, orthoMatrix);
	if (!result)
	{
		return false;
	}
	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnZBufferOn();
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

D3DXMATRIX GraphicsClass::MoveChar(float playerYaw, float playerPitch, float playerRoll, float moveLeftRight, float moveBackForward,
							 D3DXVECTOR3 DefaultForward, D3DXVECTOR3 DefalutRight, D3DXMATRIX& worldMatrix)
{
	D3DXMATRIX rotateMatrix_Player;
	D3DXQUATERNION Quat_Rot;

	D3DXMatrixRotationYawPitchRoll(&rotateMatrix_Player, playerYaw, playerPitch, playerRoll);
	D3DXQuaternionRotationMatrix(&Quat_Rot, &rotateMatrix_Player);

	this->Quat_Rot = this->Quat_Rot * Quat_Rot;

	D3DXMatrixRotationQuaternion(&rotateMatrix_Player, &Quat_Rot);

	D3DXVec3TransformNormal(&playerTarget, &DefaultForward, &rotateMatrix_Player);

	D3DXVec3TransformCoord(&playerRight, &DefalutRight, &rotateMatrix_Player);
	D3DXVec3TransformCoord(&playerForward, &DefaultForward, &rotateMatrix_Player);
	D3DXVec3Cross(&playerUp, &playerForward, &playerRight);

	playerPosition += moveLeftRight * playerRight;
	playerPosition += moveBackForward * playerForward;

	playerTarget = playerPosition + playerTarget;

	//D3DXMatrixLookAtLH(&worldMatrix, &playerPosition, &playerTarget, &playerUp);

	D3DXMatrixTranslation(&transMatrix_Player, playerPosition.x, playerPosition.y, playerPosition.z);
	worldMatrix = scaleMatrix_Player * rotateMatrix_Player * transMatrix_Player;

	m_Player->SetCollider(scaleMatrix_Player, transMatrix_Player); //플레이어 콜라이더

	return rotateMatrix_Player;
}

float GraphicsClass::CrossLookAt(D3DXVECTOR3 NestPos, D3DXVECTOR3 playerPos)
{
	D3DXVECTOR3 Cross_Dir;
	D3DXVECTOR3 Cross_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	Cross_Dir = NestPos - playerPos;
	D3DXVec3Normalize(&crossForward, &crossForward);
	D3DXVec3Normalize(&Cross_Dir, &Cross_Dir);

	float Dot;
	float Radian;

	Dot = D3DXVec3Dot(&crossForward, &Cross_Dir);
	Radian = (float)acos(Dot);

	D3DXVec3Cross(&crossForward, &crossRight, &Cross_Up); //마지막값은 up

	if (D3DXVec3Dot(&crossRight, &Cross_Dir) > 0)
	{
		return Radian;
	}

	else
	{
		return -Radian;
	}

}

void GraphicsClass::YawRotation(float playerYaw) {
	D3DXQUATERNION Quat_Rot;
	D3DXQuaternionRotationAxis(&Quat_Rot, &RotateYaw, playerYaw);
	this->Quat_Rot = this->Quat_Rot * Quat_Rot;

	D3DXMATRIX rotateMatrix_Player;
	D3DXMatrixRotationQuaternion(&rotateMatrix_Player, &Quat_Rot);
	D3DXVec3TransformNormal(&RotatePitch, &RotatePitch, &rotateMatrix_Player);
	D3DXVec3TransformNormal(&RotateRoll, &RotateRoll, &rotateMatrix_Player);
}

void GraphicsClass::RollRotation(float playerRoll) {
	D3DXQUATERNION Quat_Rot;
	D3DXQuaternionRotationAxis(&Quat_Rot, &RotateRoll, playerRoll);
	this->Quat_Rot = this->Quat_Rot * Quat_Rot;

	D3DXMATRIX rotateMatrix_Player;
	D3DXMatrixRotationQuaternion(&rotateMatrix_Player, &Quat_Rot);
	D3DXVec3TransformNormal(&RotatePitch, &RotatePitch, &rotateMatrix_Player);
	D3DXVec3TransformNormal(&RotateYaw, &RotateYaw, &rotateMatrix_Player);
}

void GraphicsClass::PitchRotation(float playerPitch) {
	D3DXQUATERNION Quat_Rot;
	D3DXQuaternionRotationAxis(&Quat_Rot, &RotatePitch, playerPitch);
	this->Quat_Rot = this->Quat_Rot * Quat_Rot;

	D3DXMATRIX rotateMatrix_Player;
	D3DXMatrixRotationQuaternion(&rotateMatrix_Player, &Quat_Rot);
	D3DXVec3TransformNormal(&RotateRoll, &RotateRoll, &rotateMatrix_Player);
	D3DXVec3TransformNormal(&RotateYaw, &RotateYaw, &rotateMatrix_Player);
}