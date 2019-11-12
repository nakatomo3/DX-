#include "Cube.h"



Cube::Cube(HWND hwnd) {
	position = D3DXVECTOR3(0, 0, 0);
	localPosition = D3DXVECTOR3(0, 0, 0);
	rotation = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1, 1, 1);

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 36,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pD3DVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	size = 0.1f;

	g_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].vtx = D3DXVECTOR3(-size, size, -size)+ localPosition;
	pVtx[1].vtx = D3DXVECTOR3(size, size, -size)+ localPosition;
	pVtx[2].vtx = D3DXVECTOR3(-size, -size, -size)+ localPosition;
	pVtx[3].vtx = D3DXVECTOR3(size, size, -size)+ localPosition;
	pVtx[4].vtx = D3DXVECTOR3(size, -size, -size)+ localPosition;
	pVtx[5].vtx = D3DXVECTOR3(-size, -size, -size)+ localPosition;

	pVtx[6].vtx = D3DXVECTOR3(size, size, size)+ localPosition;
	pVtx[7].vtx = D3DXVECTOR3(size, -size, size)+ localPosition;
	pVtx[8].vtx = D3DXVECTOR3(size, size, -size)+ localPosition;
	pVtx[9].vtx = D3DXVECTOR3(size, -size, size)+ localPosition;
	pVtx[10].vtx = D3DXVECTOR3(size, -size, -size)+ localPosition;
	pVtx[11].vtx = D3DXVECTOR3(size, size, -size)+ localPosition;

	pVtx[12].vtx = D3DXVECTOR3(-size, -size, size)+ localPosition;
	pVtx[13].vtx = D3DXVECTOR3(-size, size, -size)+ localPosition;
	pVtx[14].vtx = D3DXVECTOR3(-size, -size, -size)+ localPosition;
	pVtx[16].vtx = D3DXVECTOR3(-size, size, -size)+ localPosition;
	pVtx[15].vtx = D3DXVECTOR3(-size, size, size)+ localPosition;
	pVtx[17].vtx = D3DXVECTOR3(-size, -size, size)+ localPosition;

	pVtx[18].vtx = D3DXVECTOR3(-size, size, size)+ localPosition;
	pVtx[19].vtx = D3DXVECTOR3(-size, -size, size)+ localPosition;
	pVtx[20].vtx = D3DXVECTOR3(size, size, size)+ localPosition;
	pVtx[21].vtx = D3DXVECTOR3(size, size, size)+ localPosition;
	pVtx[22].vtx = D3DXVECTOR3(-size, -size, size)+ localPosition;
	pVtx[23].vtx = D3DXVECTOR3(size, -size, size)+ localPosition;

	pVtx[24].vtx = D3DXVECTOR3(-size, size, size)+ localPosition;
	pVtx[25].vtx = D3DXVECTOR3(size, size, size)+ localPosition;
	pVtx[26].vtx = D3DXVECTOR3(size, size, -size)+ localPosition;
	pVtx[27].vtx = D3DXVECTOR3(-size, size, size)+ localPosition;
	pVtx[28].vtx = D3DXVECTOR3(size, size, -size)+ localPosition;
	pVtx[29].vtx = D3DXVECTOR3(-size, size, -size)+ localPosition;

	pVtx[30].vtx = D3DXVECTOR3(-size, -size, size)+ localPosition;
	pVtx[31].vtx = D3DXVECTOR3(size, -size, -size)+ localPosition;
	pVtx[32].vtx = D3DXVECTOR3(size, -size, size)+ localPosition;
	pVtx[33].vtx = D3DXVECTOR3(-size, -size, size)+ localPosition;
	pVtx[34].vtx = D3DXVECTOR3(-size, -size, -size)+ localPosition;
	pVtx[35].vtx = D3DXVECTOR3(size, -size, -size)+ localPosition;

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[9].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[10].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[11].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[12].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[13].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[14].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[15].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[16].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[17].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[18].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[19].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[20].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[21].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[22].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[23].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[24].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[25].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[26].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[27].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[28].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[29].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[30].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[31].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[32].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[33].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[34].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[35].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//反射光の設定
	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[4].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[6].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[7].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[8].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[9].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[10].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[11].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	pVtx[12].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	pVtx[13].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	pVtx[14].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	pVtx[15].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	pVtx[16].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	pVtx[17].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	pVtx[18].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	pVtx[19].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	pVtx[20].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	pVtx[21].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	pVtx[22].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	pVtx[23].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	pVtx[24].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f); //水色
	pVtx[25].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[26].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[27].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[28].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[29].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

	pVtx[30].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f); //ピンク
	pVtx[31].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	pVtx[32].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	pVtx[33].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	pVtx[34].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	pVtx[35].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[6].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[16].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[17].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[18].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[19].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[20].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[21].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[22].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[23].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[24].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[25].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[26].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[27].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[28].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[29].tex = D3DXVECTOR2(0.0f, 1.0f);

	pVtx[30].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[31].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[32].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[34].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[35].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pD3DVtxBuff->Unlock();
}


Cube::~Cube() {
}

void Cube::Draw() {
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
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);
}

void Cube::SetPosition(D3DXVECTOR3 _position) {
	position = _position;
}

void Cube::SetLocalPosition(D3DXVECTOR3 _lposition) {
	localPosition = _lposition;

	VERTEX_3D *pVtx;
	g_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-size, size, -size) + localPosition;
	pVtx[1].vtx = D3DXVECTOR3(size, size, -size) + localPosition;
	pVtx[2].vtx = D3DXVECTOR3(-size, -size, -size) + localPosition;
	pVtx[3].vtx = D3DXVECTOR3(size, size, -size) + localPosition;
	pVtx[4].vtx = D3DXVECTOR3(size, -size, -size) + localPosition;
	pVtx[5].vtx = D3DXVECTOR3(-size, -size, -size) + localPosition;

	pVtx[6].vtx = D3DXVECTOR3(size, size, size) + localPosition;
	pVtx[7].vtx = D3DXVECTOR3(size, -size, size) + localPosition;
	pVtx[8].vtx = D3DXVECTOR3(size, size, -size) + localPosition;
	pVtx[9].vtx = D3DXVECTOR3(size, -size, size) + localPosition;
	pVtx[10].vtx = D3DXVECTOR3(size, -size, -size) + localPosition;
	pVtx[11].vtx = D3DXVECTOR3(size, size, -size) + localPosition;

	pVtx[12].vtx = D3DXVECTOR3(-size, -size, size) + localPosition;
	pVtx[13].vtx = D3DXVECTOR3(-size, size, -size) + localPosition;
	pVtx[14].vtx = D3DXVECTOR3(-size, -size, -size) + localPosition;
	pVtx[16].vtx = D3DXVECTOR3(-size, size, -size) + localPosition;
	pVtx[15].vtx = D3DXVECTOR3(-size, size, size) + localPosition;
	pVtx[17].vtx = D3DXVECTOR3(-size, -size, size) + localPosition;

	pVtx[18].vtx = D3DXVECTOR3(-size, size, size) + localPosition;
	pVtx[19].vtx = D3DXVECTOR3(-size, -size, size) + localPosition;
	pVtx[20].vtx = D3DXVECTOR3(size, size, size) + localPosition;
	pVtx[21].vtx = D3DXVECTOR3(size, size, size) + localPosition;
	pVtx[22].vtx = D3DXVECTOR3(-size, -size, size) + localPosition;
	pVtx[23].vtx = D3DXVECTOR3(size, -size, size) + localPosition;

	pVtx[24].vtx = D3DXVECTOR3(-size, size, size) + localPosition;
	pVtx[25].vtx = D3DXVECTOR3(size, size, size) + localPosition;
	pVtx[26].vtx = D3DXVECTOR3(size, size, -size) + localPosition;
	pVtx[27].vtx = D3DXVECTOR3(-size, size, size) + localPosition;
	pVtx[28].vtx = D3DXVECTOR3(size, size, -size) + localPosition;
	pVtx[29].vtx = D3DXVECTOR3(-size, size, -size) + localPosition;

	pVtx[30].vtx = D3DXVECTOR3(-size, -size, size) + localPosition;
	pVtx[31].vtx = D3DXVECTOR3(size, -size, -size) + localPosition;
	pVtx[32].vtx = D3DXVECTOR3(size, -size, size) + localPosition;
	pVtx[33].vtx = D3DXVECTOR3(-size, -size, size) + localPosition;
	pVtx[34].vtx = D3DXVECTOR3(-size, -size, -size) + localPosition;
	pVtx[35].vtx = D3DXVECTOR3(size, -size, -size) + localPosition;

	g_pD3DVtxBuff->Unlock();
}

void Cube::SetRotation(D3DXVECTOR3 _rotation) {
	rotation = _rotation;
}

void Cube::SetScale(D3DXVECTOR3 _scale) {
	scale = _scale;
}

D3DXVECTOR3 Cube::GetPosition() {
	return position;
}

D3DXVECTOR3 Cube::GetLocalPosition() {
	return localPosition;
}

D3DXVECTOR3 Cube::GetRotation() {
	return rotation;
}

D3DXVECTOR3 Cube::GetScale() {
	return scale;
}
