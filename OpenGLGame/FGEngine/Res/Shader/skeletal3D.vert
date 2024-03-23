/**
* @file standard.vert
*/
# version 450

// �V�F�[�_�̓���
layout(location=0) in vec3 inPosition;	// ���_���W
layout(location=1) in vec2 inTexcoord;	// �e�N�X�`�����W
layout(location=2) in vec3 inNormal;	// �@���x�N�g��
layout(location=4) in vec4 inJoints;
layout(location=5) in vec4 inWeights;

// �V�F�[�_�̏o��
layout(location=0) out vec3 outPosition;	// ���[���h���W
layout(location=1) out vec2 outTexcoord;	// �e�N�X�`�����W
layout(location=2) out vec3 outNormal;		// �@���x�N�g��
layout(location=3) out vec3 outShadowTexcoord;	// �V���h�E�e�N�X�`�����W

// �v���O��������̓���
layout(location=0) uniform mat4 transformMatrix;
layout(location=1) uniform mat3 normalMatrix;
layout(location=2) uniform mat4 viewProjectionMatrix;	// �r���[�v���W�F�N�g�s��
layout(location=3) uniform vec2 aspectRatioAndScaleFov;	// �A�X�y�N�g��
layout(location=4) uniform vec3 cameraPosition;	// �J�����̈ʒu
layout(location=7) uniform mat3 cameraRotationMatrix;
layout(location=10) uniform mat4 shadowTextureMatrix;	// �V���h�E�e�N�X�`���s��
layout(location=11) uniform float shadowNormalOffset;	// ���W��@�������ɂ��炷��

// �X�P���^���A�j���[�V�����pSSBO
layout(std430, binding=0) buffer AnimationDataBlock
{
	mat4 matBones[];	// �p���s��̔z��
};

void main()
{
	outTexcoord = inTexcoord;

	// �p���s��ɃE�F�C�g�������ĉ��Z�������A���f���s����쐬
	mat4 matModel = 
		matBones[int(inJoints.x)] * inWeights.x + 
		matBones[int(inJoints.y)] * inWeights.y + 
		matBones[int(inJoints.z)] * inWeights.z + 
		matBones[int(inJoints.w)] * inWeights.w;

	// �E�F�C�g�����K������Ă��Ȃ��ꍇ�̑΍�([3][3]��1.0�ɂȂ�Ƃ͌���Ȃ�)
	matModel[3][3] = dot(inWeights, vec4(1));

	// �֐ߍs��ƃQ�[���I�u�W�F�N�g���W�ϊ��s�������
	mat4 modelMatrix = matModel;

	// ���[�J�����W�n���烏�[���h���W�ɕϊ�
	gl_Position = modelMatrix * vec4(inPosition, 1);

	outPosition = gl_Position.xyz;
	
	// ���[���h�@�����v�Z
	mat3 jointNormalMatrix = transpose(inverse(mat3(matModel)));
	outNormal = normalize(jointNormalMatrix *inNormal);

	// �V���h�E�e�N�X�`�����W���v�Z
	outShadowTexcoord = outPosition + outNormal * shadowNormalOffset;
	outShadowTexcoord = vec3(shadowTextureMatrix* vec4(outShadowTexcoord, 1));

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