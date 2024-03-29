///////////////////////////////////////////////////////////////////////////////
// Filename: textclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "textclass.h"


TextClass::TextClass()
{
	m_Font = 0;
	m_FontShader = 0;

	m_sentence1 = 0;
	m_sentence2 = 0;
	m_time = 0;
	m_hunger = 0;
	m_object = 0;
	m_screen = 0;
	m_polygon = 0;

	m_result = 0;
	chk = false;
}


TextClass::TextClass(const TextClass& other)
{
}


TextClass::~TextClass()
{
}


bool TextClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd, int screenWidth, int screenHeight, 
						   D3DXMATRIX baseViewMatrix)
{
	bool result;


	// Store the screen width and height.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the base view matrix.
	m_baseViewMatrix = baseViewMatrix;

	// Create the font object.
	m_Font = new FontClass;
	if(!m_Font)
	{
		return false;
	}

	// Initialize the font object.
	result = m_Font->Initialize(device, (CHAR*)"./models/fontdata.txt", (WCHAR*)L"./models/Textures/font.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font object.", L"Error", MB_OK);
		return false;
	}

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if(!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the first sentence.
	result = InitializeSentence(&m_sentence1, 16, device);
	if(!result)
	{
		return false;
	}

	// Now update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence1, (CHAR*)" ", 100, 100, 1.0f, 1.0f, 1.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	// Initialize the first sentence.
	result = InitializeSentence(&m_sentence2, 16, device);
	if(!result)
	{
		return false;
	}

	// Now update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence2, (CHAR*)" ", 100, 200, 1.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	// Initialize the first sentence.
	result = InitializeSentence(&m_time, 16, device);
	if (!result)
	{
		return false;
	}

	// Now update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_time, (CHAR*)" ", 100, 200, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	// Initialize the first sentence.
	result = InitializeSentence(&m_hunger, 16, device);
	if (!result)
	{
		return false;
	}

	// Now update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_hunger, (CHAR*)" ", 100, 200, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	// Initialize the first sentence.
	result = InitializeSentence(&m_object, 16, device);
	if (!result)
	{
		return false;
	}

	// Now update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_object, (CHAR*)" ", 100, 200, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	// Initialize the first sentence.
	result = InitializeSentence(&m_screen, 16, device);
	if (!result)
	{
		return false;
	}

	// Now update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_screen, (CHAR*)" ", 100, 200, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	// Initialize the first sentence.
	result = InitializeSentence(&m_polygon, 16, device);
	if (!result)
	{
		return false;
	}

	// Now update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_polygon, (CHAR*)" ", 100, 200, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	// Initialize the first sentence.
	result = InitializeSentence(&m_result, 16, device);
	if (!result)
	{
		return false;
	}

	// Now update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_result, (CHAR*)" ", 100, 200, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}


void TextClass::Shutdown()
{
	// Release the first sentence.
	ReleaseSentence(&m_sentence1);

	// Release the second sentence.
	ReleaseSentence(&m_sentence2);

	ReleaseSentence(&m_time);

	ReleaseSentence(&m_hunger);
	ReleaseSentence(&m_object);
	ReleaseSentence(&m_screen);
	ReleaseSentence(&m_polygon);

	ReleaseSentence(&m_result);

	// Release the font shader object.
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the font object.
	if(m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}

	return;
}


bool TextClass::Render(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{
	bool result;


	// Draw the first sentence.
	result = RenderSentence(deviceContext, m_sentence1, worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	// Draw the second sentence.
	result = RenderSentence(deviceContext, m_sentence2, worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(deviceContext, m_time, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	result = RenderSentence(deviceContext, m_hunger, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	result = RenderSentence(deviceContext, m_object, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	result = RenderSentence(deviceContext, m_screen, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	result = RenderSentence(deviceContext, m_polygon, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	
	result = RenderSentence(deviceContext, m_result, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	return true;
}


bool TextClass::InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


	// Create a new sentence object.
	*sentence = new SentenceType;
	if(!*sentence)
	{
		return false;
	}

	// Initialize the sentence buffers to null.
	(*sentence)->vertexBuffer = 0;
	(*sentence)->indexBuffer = 0;

	// Set the maximum length of the sentence.
	(*sentence)->maxLength = maxLength;

	// Set the number of vertices in the vertex array.
	(*sentence)->vertexCount = 6 * maxLength;

	// Set the number of indexes in the index array.
	(*sentence)->indexCount = (*sentence)->vertexCount;

	// Create the vertex array.
	vertices = new VertexType[(*sentence)->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[(*sentence)->indexCount];
	if(!indices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * (*sentence)->vertexCount));

	// Initialize the index array.
	for(i=0; i<(*sentence)->indexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	// Release the index array as it is no longer needed.
	delete [] indices;
	indices = 0;

	return true;
}


bool TextClass::UpdateSentence(SentenceType* sentence, char* text, int positionX, int positionY, float red, float green, float blue,
							   ID3D11DeviceContext* deviceContext)
{
	int numLetters;
	VertexType* vertices;
	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;


	// Store the color of the sentence.
	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(text);

	// Check for possible buffer overflow.
	if(numLetters > sentence->maxLength)
	{
		return false;
	}

	// Create the vertex array.
	vertices = new VertexType[sentence->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * sentence->vertexCount));

	// Calculate the X and Y pixel position on the screen to start drawing to.
	drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
	drawY = (float)((m_screenHeight / 2) - positionY);

	// Use the font class to build the vertex array from the sentence text and sentence draw location.
	m_Font->BuildVertexArray((void*)vertices, text, drawX, drawY);

	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(sentence->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * sentence->vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(sentence->vertexBuffer, 0);

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	return true;
}


void TextClass::ReleaseSentence(SentenceType** sentence)
{
	if(*sentence)
	{
		// Release the sentence vertex buffer.
		if((*sentence)->vertexBuffer)
		{
			(*sentence)->vertexBuffer->Release();
			(*sentence)->vertexBuffer = 0;
		}

		// Release the sentence index buffer.
		if((*sentence)->indexBuffer)
		{
			(*sentence)->indexBuffer->Release();
			(*sentence)->indexBuffer = 0;
		}

		// Release the sentence.
		delete *sentence;
		*sentence = 0;
	}

	return;
}


bool TextClass::RenderSentence(ID3D11DeviceContext* deviceContext, SentenceType* sentence, D3DXMATRIX worldMatrix, 
							   D3DXMATRIX orthoMatrix)
{
	unsigned int stride, offset;
	D3DXVECTOR4 pixelColor;
	bool result;


	// Set vertex buffer stride and offset.
    stride = sizeof(VertexType); 
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &sentence->vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(sentence->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create a pixel color vector with the input sentence color.
	pixelColor = D3DXVECTOR4(sentence->red, sentence->green, sentence->blue, 1.0f);

	// Render the text using the font shader.
	result = m_FontShader->Render(deviceContext, sentence->indexCount, worldMatrix, m_baseViewMatrix, orthoMatrix, m_Font->GetTexture(), 
								  pixelColor);
	if(!result)
	{
		false;
	}

	return true;
}

bool TextClass::SetMousePosition(int mouseX, int mouseY, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char mouseString[16];
	bool result;


	// Convert the mouseX integer to string format.
	_itoa_s(mouseX, tempString, 10);

	// Setup the mouseX string.
	strcpy_s(mouseString, "Mouse X: ");
	strcat_s(mouseString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence1, mouseString, 20, 20, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	// Convert the mouseY integer to string format.
	_itoa_s(mouseY, tempString, 10);

	// Setup the mouseY string.
	strcpy_s(mouseString, "Mouse Y: ");
	strcat_s(mouseString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence2, mouseString, 20, 40, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}
//fps:20
bool TextClass::SetFps(int fps, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char fpsString[16];
	float red, green, blue;
	bool result;


	// Truncate the fps to below 10,000.
	if (fps > 9999)
	{
		fps = 9999;
	}

	// Convert the fps integer to string format.
	_itoa_s(fps, tempString, 10);

	// Setup the fps string.
	strcpy_s(fpsString, "Fps: ");
	strcat_s(fpsString, tempString);

	// If fps is 60 or above set the fps color to green.
	if (fps >= 60)
	{
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 60 set the fps color to yellow.
	if (fps < 60)
	{
		red = 1.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 30 set the fps color to red.
	if (fps < 30)
	{
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence1, fpsString, 20, 20, red, green, blue, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}
//cpu:40
bool TextClass::SetCpu(int cpu, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char cpuString[16];
	bool result;


	// Convert the cpu integer to string format.
	_itoa_s(cpu, tempString, 10);

	// Setup the cpu string.
	strcpy_s(cpuString, "Cpu: ");
	strcat_s(cpuString, tempString);
	strcat_s(cpuString, "%");

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence2, cpuString, 20, 40, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}
//time:140
bool TextClass::SetTime(float time, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];	
	char tempString_min[16];//분 string
	char tempString_sec[16];//초 string
	char timeString[16];
	bool result;
	int calc = (int)time;
	int min;//분 int
	int sec;//초int
	float r, g, b;//글자 색 rgb
	if (calc <= 20)//20초 이하 초록색
	{
		r = 0.0f;
		g = 1.0f;
		b = 0.0f;
	}
	else if (calc <= 40)//40초 이하 노란색
	{
		r = 1.0f;
		g = 1.0f;
		b = 0.0f;
	}
	else//그 이상 빨간색
	{
		r = 1.0f;
		g = 0.0f;
		b = 0.0f;
	}

	
	if (calc >= 60)
	{
		sec = calc % 60;
		min = calc / 60;
		_itoa_s(sec, tempString_sec, 10);
		_itoa_s(min, tempString_min, 10);
		strcpy_s(tempString, tempString_min);
		strcat_s(tempString, ":");
		if(sec<10)
			strcat_s(tempString, "0");
		strcat_s(tempString, tempString_sec);
	}
	else
	{
		_itoa_s(calc, tempString, 10);
	}

	// Setup the cpu string.
	strcpy_s(timeString, "Time: ");
	strcat_s(timeString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_time, timeString, 20, 140, r, g, b, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}
//hunger:160
bool TextClass::SetHunger(float hunger, ID3D11DeviceContext* deviceContext)//배고픔 추가함**************************
{
	char tempString[16];
	char hungerString[16];
	bool result;
	int calc = (int)hunger;
	float r, g, b;//글자 색 rgb
	if (calc <= 20)//20 이하 빨간색
	{
		r = 1.0f;
		g = 0.0f;
		b = 0.0f;
	}
	else if (calc <= 40)//40 이하 노란색
	{
		r = 1.0f;
		g = 1.0f;
		b = 0.0f;
	}
	else//그 이상 초록색
	{
		r = 0.0f;
		g = 1.0f;
		b = 0.0f;
	}


	{
		_itoa_s(calc, tempString, 10);
	}

	// Setup the cpu string.
	strcpy_s(hungerString, "Fullness: ");
	strcat_s(hungerString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_hunger, hungerString, 20, 160, r, g, b, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}
//obj:60
bool TextClass::SetObject(int object, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char objString[16];
	bool result;


	// Convert the cpu integer to string format.
	_itoa_s(object, tempString, 10);

	// Setup the cpu string.
	strcpy_s(objString, "Object: ");
	strcat_s(objString, tempString);
	strcat_s(objString, "EA");

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_object, objString, 20, 60, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}
//screen:80
bool TextClass::SetScreen(ID3D11DeviceContext* deviceContext)
{
	char tempString_h[16];
	char tempString_w[16];
	char screenString[16];
	bool result;


	// Convert the cpu integer to string format.
	_itoa_s(m_screenHeight, tempString_h, 10);
	_itoa_s(m_screenWidth, tempString_w, 10);

	// Setup the cpu string.
	strcpy_s(screenString, "Screen: ");
	strcat_s(screenString, tempString_h);
	strcat_s(screenString, "X");
	strcat_s(screenString, tempString_w);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_screen, screenString, 20, 80, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}
//polygon:100
bool TextClass::SetPolygon(float polygon, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char polygonString[16];
	bool result;
	int calc = (int)polygon;
	

	{
		_itoa_s(calc, tempString, 10);
	}

	// Setup the cpu string.
	strcpy_s(polygonString, "Polygon: ");
	strcat_s(polygonString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_polygon, polygonString, 20, 100, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetResult(ID3D11DeviceContext* deviceContext,bool win, bool lose)
{
	char tempString[16];
	char resultString[16];
	bool result;
	
	// Setup the cpu string.
	strcpy_s(resultString, " ");
	if (win && !lose)
	{
		strcpy_s(resultString, "Clear!");
		result = UpdateSentence(m_result, resultString, m_screenWidth / 2, 100, 0.0f, 1.0f, 0.0f, deviceContext);
		if (!result)
		{
			return false;
		}
	}
	if (lose && !win)
	{
		strcpy_s(resultString, "Failure!");
		result = UpdateSentence(m_result, resultString, m_screenWidth / 2, 100, 1.0f, 0.0f, 0.0f, deviceContext);
		if (!result)
		{
			return false;
		}
	}
	
	
	// Update the sentence vertex buffer with the new string information.
	

	return true;
}