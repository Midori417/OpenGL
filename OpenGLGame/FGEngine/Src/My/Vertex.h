/**
* @file Vertex.h
*/
#ifndef FGENGINE_VERTEX_H_INCLUDED
#define FGENGINE_VERTEX_H_INCLUDED
#include "VectorPoint.h"

namespace FGEngine::RenderingSystem
{
	/**
	* ���_�f�[�^�`��
	*/
	struct Vertex
	{
		Vector3 position = Vector3::zero;	// ���_���W
		Vector2 texcoord = Vector2::zero;	// �e�N�X�`�����W
		Vector3 normal = Vector3(0,0,-1);	// �@���x�N�g��
	};
}

#endif // !FGENGINE_VERTEX_H_INCLUDED
