/**
* @file ImageNum.cpp
*/
#include "ImageNum.h"
using namespace FGEngine::ResouceSystem;

/**
* �������Ɏ��s
*/
void ImageNum::Awake()
{
	auto resManager = ResouceManager::GetInstance();
	// �z���\��
	texNums.reserve(10);

	// �e�N�X�`���ɐ���������
	for (int i = 0; i < 10; i++)
	{
		std::string num = "Num" + std::to_string(i);
		auto img = resManager->GetTexture(num);
		texNums.push_back(img);
	}
	
}

/**
* �ŏ��Ɏ��s
*/
void ImageNum::Start()
{
	for(int i = 0; i < 3; ++i)
	{
		std::string name = "Num" + std::to_string(i);
		auto num = Instantate(name, GetTransform()->position + Vector3(space * i, 0, 0));
		auto image = num->AddComponent<Image>();
		image->texture = texNums[0];
		image->size = image->texture->GetSize() * scale;
		imgNums.push_back(image);
	}

}

void ImageNum::Update()
{
}
