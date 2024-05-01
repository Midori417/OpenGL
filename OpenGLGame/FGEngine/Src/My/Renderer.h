/**
* @file Renderer.h
*/
#ifndef COMPONENT_RENDERER_H_INCLUDED
#define COMPONENT_RENDERER_H_INCLUDED
#include "Component.h"
#include "VecMath.h"

// ��s�錾
class ProgramObject;

/**
* ���f���`��
*/
enum class ModelFormat
{
	obj,			// OBJ�t�@�C��
	gltfStatic,		// glTF(�A�j���[�V��������)
	gltfAnimated	// glTF(�A�j���[�V��������)
};

/**
* �����_���[�R���|�[�l���g�̊��N���X
*/
class Renderer : public Component
{
public:
	enum class Type
	{
		Standard,
		Shadow
	};


	// �R���X�g���N�^�E�f�X�g���N�^
	Renderer() = default;
	virtual ~Renderer() = default;

	// ���f���`�����擾
	virtual ModelFormat GetModelFormat() const = 0;

	virtual void PreDraw(){}
	virtual void Draw(const ProgramObject& program, Type type = Type::Standard) const {}

public:

	//int renderQueue = RenderQueue_geometry;	// �`�揇

};
using RendererPtr = std::shared_ptr<Renderer>;

#endif // !COMPONENT_RENDERER_H_INCLUDED
