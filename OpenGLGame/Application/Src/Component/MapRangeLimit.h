/**
* @file MapRangeLimit.h
*/
#ifndef MAPRANGELIMIT_H_INCLUDED
#define MAPRANGELIMIT_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/UsingNames/UsingAsset.h"
using namespace FGEngine;

/**
* �}�b�v�͈͐���
*/
class MapRangeLimit : public GameEvent
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	MapRangeLimit() = default;

private:

	/**
	* Update���n�܂�O�Ɉ�x���s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* �R���|�[�l���g�̃N���[�����쐬����
	* 
	* @return �쐬�����N���[��
	*/
	virtual ComponentPtr Clone() const override;

private:

	/**
	* �ǂ��쐬
	*/
	void CreateMapWall(const Vector2& pos, const Vector2& size);

public:

	StaticMeshPtr mesh;
	ShaderPtr shader;
	MaterialPtr material;

	// �͈͐����̑傫��
	Vector2 mapSize = Vector2::one;
};


#endif // !MAPRANGELIMIT_H_INCLUDED