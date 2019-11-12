#pragma once
//3Dポリゴンフォーマット
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

typedef struct {
	D3DXVECTOR3 vtx;  //頂点座標
	D3DXVECTOR3 nor;  //法線ベクトル
	D3DCOLOR diffuse;  //反射光
	D3DXVECTOR2 tex;  //テクスチャ座座標
}VERTEX_3D;