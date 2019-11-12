#include "Line.h"



Line::Line(D3DXVECTOR3 startPos, D3DXVECTOR3 endPos) {
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pD3DVtxBuff,
		NULL);

	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//頂点バッファの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = startPos;
	pVtx[1].vtx = endPos;

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	

	g_pD3DVtxBuff->Unlock();

	position = D3DXVECTOR3((startPos.x + endPos.x)/2, (startPos.y + endPos.y) / 2, (startPos.z + endPos.z) / 2);
	scale = D3DXVECTOR3(1, 1, 1);
	rotation = D3DXVECTOR3(0, 0, 0);
}


Line::~Line() {
}

void Line::Draw() {
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX mtxScl;
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrs;

	D3DXMATRIX g_mtxWorld;

	D3DXVECTOR3 finalPos = position/* + localPosition*/;



	//ワールド行列を単位行列へ初期化
	D3DXMatrixIdentity(&g_mtxWorld);

	//スケール行列を作成＆ワールド行列へ合成
	D3DXMatrixScaling(&mtxScl, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

	//回転行列を作成＆ワールド行列へ合成
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotation.y, rotation.x, rotation.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

	//平行行列
	D3DXMatrixTranslation(&mtxTrs, finalPos.x, finalPos.y, finalPos.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTrs);

	//ワールドマトリクスを設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

	//描画したいポリゴン頂点バッファをデータストリームにセット
	pDevice->SetStreamSource(0, g_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	//ポリゴンの描画
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_KIZUNA));
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 2);
}
