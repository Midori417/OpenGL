/**
* @file unlit.vert
*/
# version 450

// �V�F�[�_�̓���
layout(location=0) in vec3 inPosition;	// ���_���W
layout(location=1) in vec2 inTexcoord;	// �e�N�X�`�����W

// �V�F�[�_�̏o��
layout(location=0) out vec3 outPosition;	// ���[���h���W
layout(location=1) out vec2 outTexcoord;	// �e�N�X�`�����W

// �v���O��������̓���
layout(location=0) uniform mat4 transformMatrix;
layout(location=3) uniform vec2 aspectRatioAndScaleFov;	// �A�X�y�N�g��
layout(location=4) uniform vec3 cameraPosition;	// �J�����̈ʒu
//layout(location=5) uniform vec3 cameraSin;
//layout(location=6) uniform vec3 cameraCos;
layout(location=7) uniform mat3 cameraRotationMatrix;


void main()
{
	outTexcoord = inTexcoord;

	// ���[�J�����W�n���烏�[���h���W�ɕϊ�
	// ���[�J�����W�n���烏�[���h���W�ɕϊ�
	gl_Position = transformMatrix * vec4(inPosition, 1);

	outPosition = gl_Position.xyz;

	// ���[���h���W�n����r���[���W�n�ɕϊ�
	vec3 pos = (gl_Position.xyz - cameraPosition) * cameraRotationMatrix;
	gl_Position.xyz = pos;

	// �r���[���W�n����N���b�v���W�n�ɕϊ�
	gl_Position.xy *= aspectRatioAndScaleFov;

	// �[�x�l�̌v�Z���ʂ�-1�`+1�ɂȂ�悤�ȃp�����[�^A�AB���v�Z
	const float near = 0.35f;
	const float far = 1000;
	const float A = -2 * far * near / (far - near);
	const float B = (far + near) / (far - near);

	// ���ߖ@��L���ɂ���
	gl_Position.w = -gl_Position.z;
	gl_Position.z = -gl_Position.z * B + A; // �[�x�l��␳
}