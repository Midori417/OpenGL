/**
* @file standard.frag
*/
# version 450

// �V�F�[�_�̓���
layout(location=0) in vec3 inPosition;	// ���[���h���W
layout(location=1) in vec2 inTexcoord;	// �e�N�X�`�����W
layout(location=2) in vec3 inNormal;	// �@���x�N�g��
layout(location=3) in vec3 inShadowTexcoord;	// �V���h�E�e�N�X�`�����W

// �o�͂���F�f�[�^
out vec4 outColor;

// �e�N�X�`���T���v��
layout(binding=0) uniform sampler2D texColor;
layout(binding=1) uniform sampler2D texEmission;
layout(binding=2) uniform sampler2DShadow texShadow;	// �e���[�x�e�N�X�`��

// �v���O��������̓���
layout(location=100) uniform vec4 color;	// ���̂̐F
layout(location=101) uniform vec4 emissionColor; // ���̂̔����F
layout(location=102) uniform float alphaCutoff;	// �t���O�����g��j�����鋫�E��

// ����
layout(location=107) uniform vec3 ambientLight;

// ���s����
struct DirectionalLight
{
	vec3 color;		// �F�Ɩ��邳
	vec3 direction;	// ���̌���
};
layout(location=108) uniform DirectionalLight directionLight;

// ���C�g�p�����[�^
struct Light
{
	vec4 colorAndFalloffAngle[16];		// �F�Ɩ��邳�A�����J�n�p�x
	vec4 positionAndRadius[16];			// ���W�Ɣ��a
	vec4 directionAndConeAngle[16];		// �����A�ő�Ǝˊp�x
};
layout(location=110) uniform int lightCount;
layout(location=111) uniform Light light;

void main()
{
	vec4 c = texture(texColor, inTexcoord);

	// �J�b�g�I�t�l���w�肳��Ă���ꍇ�A�A���t�@�����̒l�����̏ꍇ�͕`����L�����Z��
	if(alphaCutoff > 0){
		if(c.a < alphaCutoff){
			discard;	// �t���O�����g��j��
		}
		c.a = 1;	// �j������Ȃ�������s�����ɂ���
	}

	// �e�N�X�`���̃K���}�␳������
	const float crtGamma = 2.2;	// CRT���j�^�[�̃K���}�l
	c.rgb = pow(c.rgb, vec3(2.2));

	outColor = c * color;

	// ���`��Ԃɂ���Ē�������ł͂Ȃ��Ȃ��Ă���̂Ő��K�����Ē�������ɕ�������
	vec3 normal = normalize(inNormal);


	vec3 diffuse = vec3(0);		// �g�U���̖��邳�̍��v
	for(int i = 0; i < lightCount; ++i)
	{
		// �����̕���
		vec3 direction = light.positionAndRadius[i].xyz - inPosition;

		// �����܂ł̋���
		float sqrDistance = dot(direction, direction);
		float distance = sqrt(sqrDistance);

		// �����𐳋K�����Ē������P�ɂ���
		direction = normalize(direction);


		// �����x���g�̗]�������g���Ė��邳���v�Z
		float theta = max(dot(direction, normal), 0);

		// �����p�[�g���˂ɂ�锽�ˌ��̃G�l���M�[�ʂ���ˌ��Ɠ��������邽�߂Ƀ΂Ŋ���
		float illuminance = theta / 3.14159265;

		// �Ǝˊp�x��0���傫����΃X�|�b�g���C�g�Ƃ݂Ȃ�
		const float coneAngle = light.directionAndConeAngle[i].w;
		if(coneAngle > 0){
			// �u���C�g����t���O�ʂ֌������x�N�g���v�Ɓu�X�|�b�g���C�g�̃x�N�g���v�̂Ȃ��p���v�Z
			// �p�x��coneAngle�ȏ�Ȃ�͈͊O
			float angle = acos(dot(-direction, light.directionAndConeAngle[i].xyz));
			if(angle >= coneAngle){
				continue; // �Ǝ˔͈͊O
			}

			// �ő�Ǝˊp�x�̎�0�A�����J�n�p�x�̂Ƃ�1�ɂȂ�悤�ɕ��
			const float falloffAngle = light.colorAndFalloffAngle[i].w;
			const float a = min((coneAngle - angle) / (coneAngle - falloffAngle), 1);
			illuminance *= a;
		}

		// ���C�g�̍ő勗���̐���
		const float radius = light.positionAndRadius[i].w;
		const float smoothFactor = clamp(1 - pow(distance / radius, 4), 0, 1);
		illuminance *= smoothFactor * smoothFactor;

		// �t���̖@���ɂ���Ė��邳������������
		// 0���Z���N���Ȃ��悤�ɂP�𑫂��Ă���
		illuminance /= sqrDistance + 1;

		// �g�U���̖��邳���v�Z
		diffuse += light.colorAndFalloffAngle[i].xyz * illuminance;
	}

	// �e���v�Z
	float shadow = texture(texShadow, inShadowTexcoord).r;

	// ���s�����̖��邳���v�Z
	float theta = max(dot(-directionLight.direction, normal),0);
	float illuminance = theta / 3.14159265;
	diffuse += directionLight.color * illuminance * shadow;

	// �A���r�G���g���C�g�̖��邳���v�Z
	diffuse += ambientLight;

	// �g�U���̉e���𔽉f
	outColor.rgb *= diffuse;

	// �����F�𔽉f
	if(emissionColor.w > 0)
	{
		outColor.rgb += texture(texEmission, inTexcoord).rgb * emissionColor.rgb;
	}
	else 
	{
	 outColor.rgb += emissionColor.rgb;
	}

	// �K���}�␳���s��
	outColor.rgb = pow(outColor.rgb, vec3(1 / 2.2));
}