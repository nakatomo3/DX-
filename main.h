#pragma once
//3D�|���S���t�H�[�}�b�g
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

typedef struct {
	D3DXVECTOR3 vtx;  //���_���W
	D3DXVECTOR3 nor;  //�@���x�N�g��
	D3DCOLOR diffuse;  //���ˌ�
	D3DXVECTOR2 tex;  //�e�N�X�`�������W
}VERTEX_3D;