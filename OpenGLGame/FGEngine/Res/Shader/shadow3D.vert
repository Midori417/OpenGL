/**
* @file shadow.vert
*/
# version 450

// �V�F�[�_�ւ̓���
layout(location=0) in vec3 inPosition; // ���_���W
layout(location=1) in vec2 inTexcoord; // �e�N�X�`�����W
layout(location=4) in vec4 inJoints;
layout(location=5) in vec4 inWeights;

// �V�F�[�_����̏o��
layout(location=1) out vec2 outTexcoord;	// �e�N�X�`�����W

// �v���O��������̓���
layout(location=0) uniform mat4 transformMatrix;	// ���W�ϊ��s��
layout(location=2) uniform mat4 viewProjectionMatrix;	// �r���[�v���W�F�N�g�s��

void main()
{
	// �e�N�X�`�����W
	outTexcoord = inTexcoord;

	// ���[�J�����W�n���烏�[���h���W�n�ɕϊ�
	gl_Position = transformMatrix * vec4(inPosition, 1);
	gl_Position = viewProjectionMatrix * gl_Position;
}