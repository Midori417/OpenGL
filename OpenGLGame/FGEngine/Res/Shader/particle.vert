/**
* @file particle.vert
*/
#version 450

// �V�F�[�_�[�ւ̓���
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexcoord;

// �V�F�[�_����̏o��
layout(location=0) out vec4 outColor;
layout(location=1) out vec2 outTexcoord;

// �v���O��������̓���
layout(location=3) uniform vec4 aspectRatioAndScaleFov;	// �A�X�y�N�g��
layout(location=4) uniform vec3 cameraPosition;	// �J�����̈ʒu
layout(location=5) uniform mat3 cameraRotationMatrix;

// �e�N�X�`��
layout(binding=0) uniform sampler2D texColor;

// �e�N�X�`�����W�\����
struct Texcoord
{
	vec2 uv;
	vec2 size;
};

// �p�[�e�B�N���f�[�^�\����
struct ParticleData
{
	mat4 transformMatrix;
	vec4 color;		// �F�ƕs�����x
	Texcoord texcoord;	// �e�N�X�`�����W
};

// �p�[�e�B�N���pSSBO
layout(std430, binding=0)buffer praticleDataBuffer
{
	ParticleData particlList[];
};

void main()
{
	ParticleData particle = particlList[gl_InstanceID];

	// �v���~�e�B�u�̐F��ݒ�
	outColor = particle.color;
	outColor.a = clamp(outColor.a, 0, 1);

	// �v���~�e�B�u�̃e�N�X�`�����W���v�Z
	outTexcoord = particle.texcoord.uv + (inTexcoord * particle.texcoord.size);

	// ���[�J�����W�n���烏�[���h���W�ɕϊ�
	gl_Position = particle.transformMatrix * vec4(inPosition, 1);

	// ���[���h���W�n����r���[���W�n�ɕϊ�
	vec3 pos = (gl_Position.xyz - cameraPosition) * cameraRotationMatrix;
	gl_Position.xyz = pos;

	// �r���[���W�n����N���b�v���W�n�ɕϊ�
	gl_Position.xy *= aspectRatioAndScaleFov;

	// �[�x�l�̌v�Z���ʂ�-1�`+1�ɂȂ�悤�ȃp�����[�^A�AB���v�Z
	const float near = aspectRatioAndScaleFov.z;
	const float far = aspectRatioAndScaleFov.w;
	const float A = -2 * far * near / (far - near);
	const float B = (far + near) / (far - near);

	// ���ߖ@��L���ɂ���
	gl_Position.w = -gl_Position.z;
	gl_Position.z = -gl_Position.z * B + A; // �[�x�l��␳
}

//// �G���g���[�|�C���g
//void main()
//{
//	ParticleData particle = particlList[gl_InstanceID];
//
//	// �v���~�e�B�u�̐F��ݒ�
//	outColor = particle.color;
//	outColor.a = clamp(outColor.a, 0, 1);
//
//	// �v���~�e�B�u�̃e�N�X�`�����W���v�Z
//	outTexcoord = particle.texcoord.uv + (inTexcoord * particle.texcoord.size);
//
//	// �v���~�e�B�u�̑傫�����摜�̑傫���Ɠ���������
//	vec2 v = inPosition * abs(particle.texcoord.size) * textureSize(texColor, 0);
//
//	// �v���~�e�B�u�̊g��k��
//	v *= particle.scale;
//
//	// �v���~�e�B�u����]
//	gl_Position.x = v.x * particle.cosZ - v.y * particle.sinZ;
//	gl_Position.y = v.x + particle.sinZ + v.y * particle.cosZ;
//
//	// �v���~�e�B�u���J�����̕����Ɍ�����(�r���{�[�h������)
//	gl_Position.z = 0;
//	gl_Position.xyz = matBillboard * gl_Position.xyz;
//
//	// �v���~�e�B�u�����[���h���W�ɕ��s�ړ�
//	gl_Position.xyz += particle.position.xyz;
//
//	//�v���~�e�B�u�����[���h���W�n����N���b�v���W�n�֕ϊ�
//	gl_Position.w = 1;
//	gl_Position = matViewPorj * gl_Position;
//}