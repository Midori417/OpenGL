/**
* @file GltfAnimatedMeshRenderer.cpp
*/
#include "GltfAnimatednMeshRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Time.h"
#include "Mathf.h"
#include <algorithm>

/**
* �A�j���[�V������Ԃ��X�V����
*/
void GltfAnimatedMeshRenderer::Update()
{
	if (file->animations.empty() || !animation)
	{
		return;
	}

	// �A�j���[�V������Ԃ��X�V
	switch (state)
	{
	case GltfAnimatedMeshRenderer::State::stop:
		break;
	case GltfAnimatedMeshRenderer::State::play:
		// �Đ��������X�V
		time += animationSpeed * Time::deltaTime();
		if (isLoop)
		{
 			time -= animation->totalTime * std::floor(time / animation->totalTime);
		}
		else
		{
			time = Mathf::Clamp(time, 0.0f, animation->totalTime);
			if (time >= animation->totalTime)
			{
				state = State::stop;
			}
		}
		break;
	case GltfAnimatedMeshRenderer::State::pause:
		break;
	}
}

/**
* �`��̑O���������s
*
* @param gameObject �`��Ώۂ̃Q�[���I�u�W�F�N�g
*/
void GltfAnimatedMeshRenderer::PreDraw()
{
	if (!fileBuffer || !file)
	{
		return;
	}

	// �V�[���Ɋ܂܂�郁�b�V���̃A�j���[�V�����s����X�V
	const auto scene = &file->scenes[0];
	const Matrix4x4 matModel = transform->GetModelMatrix();
	ssboRanges.clear();
	for (const auto e : scene->meshNodes)
	{
		// �A�j���[�V�����s����v�Z
		auto matBones = CalcAnimationMatrices(file, e, animation.get(), time);
		for (auto& m : matBones)
		{
			m = matModel * m; // �A�j���[�V�����s��Ƀ��f���s�������
		}
		// �A�j���[�V�����s����o�b�t�@�ɒǉ����A�ǉ���̃I�t�Z�b�g�ƃT�C�Y���L�^
		ssboRanges.push_back(fileBuffer->AddAnimationMatrices(matBones));
	}
}

/**
* ���b�V����`�悷��
*
* @param progaram �`��Ɏg���v���O�����p�C�v���C���I�u�W�F�N�g
* @param matGameObject �Q�[���I�u�W�F�N�g�̃��f���s��
*/
void GltfAnimatedMeshRenderer::Draw(const ProgramObject& program, Type type) const
{
	if (!fileBuffer || !file || ssboRanges.empty())
	{
		return;
	}

	// �V�[���Ɋ܂܂�郁�b�V����`��
	const auto scene = &file->scenes[0];
	for (size_t i = 0; i < scene->meshNodes.size(); ++i)
	{
		const int meshNo = scene->meshNodes[i]->mesh;
		const GltfMesh& mesh = file->meshes[meshNo];

		// SSBO���o�C���f�B���O�|�C���g0�ԂɊ��蓖�Ă�
		fileBuffer->BindAnimationBuffer(0, ssboRanges[i]);

		// �}�e���A�����w�肳��Ă��Ȃ��ꍇ�A���L�}�e���A�����g���ĕ`�悷��
		const auto* pMaterials = &materials;
		if (materials.empty())
		{
			pMaterials = &file->materials;
		}

		// ���b�V���Ɋ܂܂�邷�ׂẴv���~�e�B�u��`��
		::Draw(mesh, *pMaterials, program);
	}
}

/**
* �A�j���[�V�����̍Đ����J�n�E�ĊJ����
*/
void GltfAnimatedMeshRenderer::Play()
{
	switch (state)
	{
	case GltfAnimatedMeshRenderer::State::stop:
		time = 0;	// �擪����Đ�
		state = State::play;
		break;
	case GltfAnimatedMeshRenderer::State::play:
		break;
	case GltfAnimatedMeshRenderer::State::pause:
		state = State::play;
		break;
	}
}

/**
* �A�j���[�V�����̍Đ����~����
*/
void GltfAnimatedMeshRenderer::Stop()
{
	switch (state)
	{
	case GltfAnimatedMeshRenderer::State::stop:
		break;
	case GltfAnimatedMeshRenderer::State::play:
		state = State::stop;
		break;
	case GltfAnimatedMeshRenderer::State::pause:
		state = State::stop;
		break;
	}
}

/**
* �A�j���[�V�����̍Đ����ꎞ��~����
*/
void GltfAnimatedMeshRenderer::Pause()
{
	switch (state)
	{
	case GltfAnimatedMeshRenderer::State::stop:
		break;
	case GltfAnimatedMeshRenderer::State::play:
		state = State::pause;
		break;
	case GltfAnimatedMeshRenderer::State::pause:
		break;
	}
}

/**
* �A�j���[�V������ݒ肷��
* 
* @param animation	�Đ�����A�j���[�V����
* @param isLoop		���[�v�Đ��̎w��(true=���[�v����Afalse=���[�v���Ȃ�)
* 
* @retval true	�ݒ萬��
* @retval false	�ݒ莸�s
*/
bool GltfAnimatedMeshRenderer::SetAnimation(const GltfAnimationPtr& animation, bool isLoop)
{
	// �����A�j���[�V�������w�肳�ꂽ�ꍇ�͉������Ȃ�
	if (this->animation == animation)
	{
		return true;	// �ݒ萬���Ƃ��Ĉ���
	}
	this->animation = animation;	// �A�j���[�V������ݒ�

	// ��Ԃ��u��~���v�ɐݒ�
	time = 0;
	state = State::stop;
	this->isLoop = isLoop;

	return true;
}

/**
* �A�j���[�V������ݒ肷��
*
* @param name		�Đ�����A�j���[�V�����̖��O
* @param isLoop		���[�v�Đ��̎w��(true=���[�v����Afalse=���[�v���Ȃ�)
*
* @retval true	�ݒ萬��
* @retval false	�ݒ莸�s
*/
bool GltfAnimatedMeshRenderer::SetAnimation(const std::string& name, bool isLoop)
{
	if (!file)
	{
		return false;
	}
	for (const auto& e : file->animations)
	{
		if (e->name == name)
		{
			return SetAnimation(e, isLoop);
		}
	}

	return false;
}

/**
* �A�j���[�V������ݒ肷��
*
* @param index		�Đ�����A�j���[�V�����ԍ�
* @param isLoop		���[�v�Đ��̎w��(true=���[�v����Afalse=���[�v���Ȃ�)
*
* @retval true	�ݒ萬��
* @retval false	�ݒ莸�s
*/
bool GltfAnimatedMeshRenderer::SetAnimation(size_t index, bool isLoop)
{
	if (!file || index >= file->animations.size())
	{
		return false;
	}
	return SetAnimation(file->animations[index], isLoop);
}
