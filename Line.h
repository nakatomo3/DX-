#pragma once

#include <Windows.h>
#include "common.h"
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>

#include "main.h"

class Line {
public:
	Line(D3DXVECTOR3 startPos, D3DXVECTOR3 endPos);
	~Line();

	void Draw();

private:
	D3DXVECTOR3 startPosition;
	D3DXVECTOR3 endPosition;
	D3DXVECTOR3 position;

	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;

	LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff;
};

