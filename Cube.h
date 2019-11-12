#pragma once
#include <Windows.h>
#include "common.h"
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>

#include "main.h"

class Cube {
public:
	Cube(HWND hwnd);
	~Cube();

	void Draw();

	void SetPosition(D3DXVECTOR3 _position);
	void SetLocalPosition(D3DXVECTOR3 _lposition);
	void SetRotation(D3DXVECTOR3 _rotation);
	void SetScale(D3DXVECTOR3 _scale);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetLocalPosition();
	D3DXVECTOR3 GetRotation();
	D3DXVECTOR3 GetScale();

private:
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;

	D3DXVECTOR3 localPosition;

	LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff;

	float size;
};

