/**
* @file standard.vert
*/
# version 450

// �V�F�[�_�̓���
layout(location=0) in vec3 inPosition;	// ���_���W
layout(location=1) in vec2 inTexcoord;	// �e�N�X�`�����W
layout(location=2) in vec3 inNormal;	// �@���x�N�g��

// �V�F�[�_�̏o��
layout(location=0) out vec3 outPosition;	// ���[���h���W
layout(location=1) out vec2 outTexcoord;	// �e�N�X�`�����W
layout(location=2) out vec3 outNormal;		// �@���x�N�g��
layout(location=3) out vec3 outShadowTexcoord;	// �V���h�E�e�N�X�`�����W

// �v���O��������̓���
layout(location=0) uniform mat4 transformMatrix;
layout(location=1) uniform mat3 normalMatrix;
layout(location=2) uniform mat4 viewProjectionMatrix;	// �r���[�v���W�F�N�g�s��
layout(location=3) uniform vec4 aspectRatioAndScaleFov;	// �A�X�y�N�g��
layout(location=4) uniform vec3 cameraPosition;	// �J�����̈ʒu
layout(location=5) uniform mat3 cameraRotationMatrix;
layout(location=10) uniform mat4 shadowTextureMatrix;	// �V���h�E�e�N�X�`���s��
layout(location=11) uniform float shadowNormalOffset;	// ���W��@�������ɂ��炷��

void main()
{
	outTexcoord = inTexcoord;

	// ���[�J�����W�n���烏�[���h���W�ɕϊ�
	gl_Position = transformMatrix * vec4(inPosition, 1);

	outPosition = gl_Position.xyz;
	
	// ���[���h�@�����v�Z
	outNormal = normalMatrix *inNormal;

	// �V���h�E�e�N�X�`�����W���v�Z
	outShadowTexcoord = outPosition + outNormal * shadowNormalOffset;
	outShadowTexcoord = vec3(shadowTextureMatrix* vec4(outShadowTexcoord, 1));

	// ���[���h���W�n����r���[���W�n�ɕϊ�
	vec3 pos = (gl_Position.xyz - cameraPosition) * cameraRotationMatrix;
	gl_Position.xyz = pos;

	// �r���[���W�n����N���b�v���W�n�ɕϊ�
	gl_Position.xy *= aspectRatioAndScaleFov.xy;

	// �[�x�l�̌v�Z���ʂ�-1�`+1�ɂȂ�悤�ȃp�����[�^A�AB���v�Z
	const float near = aspectRatioAndScaleFov.z;
	const float far = aspectRatioAndScaleFov.w;
	const float A = -2 * far * near / (far - near);
	const float B = (far + near) / (far - near);

	// ���ߖ@��L���ɂ���
	gl_Position.w = -gl_Position.z;
	gl_Position.z = -gl_Position.z * B + A; // �[�x�l��␳
}