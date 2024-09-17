/**
* @file ImageNum.cpp
*/
#include "ImageNum.h"

/**
* 生成時に実行
*/
void ImageNum::Awake()
{
	auto resManager = AssetManager::GetInstance();
	// 配列を予約
	texNums.reserve(10);

	// テクスチャに数字をついか
	for (int i = 0; i < 10; i++)
	{
		std::string num = "Num" + std::to_string(i);
		auto img = resManager->GetTexture(num);
		texNums.push_back(img);
	}
	
}

/**
* 最初に実行
*/
void ImageNum::Start()
{
	for(int i = 0; i < 3; ++i)
	{
		std::string name = OwnerObject()->name + "Num" + std::to_string(i);
		auto num = Instantate(CreateObjectType::Empty);
		num->name = name;
		num->GetTransform()->position = GetTransform()->position + Vector3(space * i, 0, 0);
		auto image = num->AddComponent<Image>();
		image->texture = texNums[0];
		image->size = image->texture->GetSize() * scale;
		imgNums.push_back(image);
	}

}

void ImageNum::Update()
{
	int number = num;
	std::vector<int> digits;

	while (number > 0)
	{
		int digit = number % 10;
		digits.push_back(digit);
		number /= 10;
	}

	// 空だった場合描画しない
	if (digits.empty())
	{
		for (int i = 1; i < imgNums.size(); ++i)
		{
			imgNums[i]->isActive =(false);
		}
		imgNums[0]->texture = texNums[0];
		return;
	}

	if (space > 0)
	{
		// 配列を逆にする
		std::reverse(digits.begin(), digits.end());
	}
	for (int i = 0; i < imgNums.size(); ++i)
	{
		if (i < digits.size())
		{
			imgNums[i]->isActive = (true);
			imgNums[i]->texture = texNums[digits[i]];
		}
		else
		{
			imgNums[i]->isActive =(false);
		}
	}
}

void ImageNum::Stop()
{
	for (auto x : imgNums)
	{
		x->isActive = (false);
	}

	isActive = (false);
}
