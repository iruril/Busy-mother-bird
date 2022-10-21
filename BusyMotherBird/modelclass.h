////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct ColliderType//�ݶ��̴��� �߰�
	{
		float Mx, mx;
		float My, my;
		float Mz, mz;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	
	float GetMaxX();//������ ��ȯ �Լ� �߰�
	float GetMinX();
	float GetMaxY();
	float GetMinY();
	float GetMaxZ();
	float GetMinZ();//-------------------

	void SetCollider(D3DXMATRIX, D3DXMATRIX);//�ݶ��̴� ���� �Լ� �߰�
	void SetCollider(float, float, float);
	bool checkCollider(float, float, float, float, float, float);
	int getPolygon();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	ModelType* m_model;
	const char* txt = ".txt";

	ColliderType* m_collider;//�ݶ��̴� ���� �߰�
	float Max, Mix, May, Miy, Maz, Miz;//�� ������ ���� �߰�
};

#endif