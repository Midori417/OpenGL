/**
* @file Object,h
*/
#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include <memory>
#include <string>

// ��s�錾
class Object;
using ObjectPtr = std::shared_ptr<Object>;
class Transform;
using TransformPtr = std::shared_ptr<Transform>;
struct Vector3;
struct Quaternion;

/**
* Editor�p(�C���X�y�N�^�[�ŃI�u�W�F�N�g�̔j���\���𐧌䂷��r�b�g�}�X�N)
*/
enum class HideFlags
{
	None = 0x0,
	Destroy = 0x1,
};

/**
* �S�ẴI�u�W�F�N�g�̊��N���X
*/
class Object
{
public:

	// === �R���X�g���N�^�E�f�X�g���N�^ === //
	Object() = default;
	virtual ~Object() = default;

private:

	// �I�u�W�F�N�g�̃C���X�^���XId
	int m_InstanceId = -1;

	// �I�u�W�F�N�g��
	std::string name = "Object";

	// �I�u�W�F�N�g�̏��
	HideFlags hideFlags = HideFlags::None;

public:

	/**
	* �C���X�^���X�ԍ����擾
	*/
	int GetInstanceId() const
	{
		return m_InstanceId;
	}

	/**
	* �I�u�W�F�N�g�̖��O��ݒ�Ǝ擾
	*/
	std::string ToString() const
	{
		return name;
	}
	void SetName(const std::string& value)
	{
		this->name = value;
	}

	/**
	* �I�u�W�F�N�g��ԃr�b�g�}�X�N�̐ݒ�Ǝ擾
	*/
	HideFlags GetHideFlags() const
	{
		return hideFlags;
	}
	void SetHideFlags(HideFlags flag)
	{
		this->hideFlags = flag;
	}

};

#endif // !OBJECT_H_INCLUDED
