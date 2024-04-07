/**
* @file ResouceManager.cpp
*/
#include "ResouceManager.h"
#include "Debug.h"
#include "Package/Glad.h"
#include <GLFW/glfw3.h>
#include "Texture.h"
#include "MeshBuffer.h"
#include "ShaderObject.h"
#include <fstream>
#include <filesystem>

#pragma warning(push)
#pragma warning(disable:4005)
#include <Windows.h>
#pragma warning(pop)


namespace FGEngine::ResouceSystem
{
	/**
	* ���\�[�X�}�l�[�W���[��������
	* 
	* @retval 0		����������
	* @retval 0�ȊO	���������s
	*/
	int ResouceManager::Initialize(const Rendering::MeshBufferPtr meshBuffer)
	{
		// ���b�V���o�b�t�@����������
		this->meshBuffer = meshBuffer;


		return 0;
	}
	/**
	* tga�t�@�C����ǂݍ���
	*
	* @param name		�e�N�X�`���̖��O
	* @param filename	Tga�t�@�C����
	*/
	void ResouceManager::LoadTga(const std::string& name, const std::string& filename)
	{
		// ���łɓo�^����Ă��邽�ߓo�^�ł��Ȃ�
		auto itr = textureCache.find(name);
		if (itr != textureCache.end())
		{
			LOG_ERROR("(Texture)%s�͂��łɓo�^����Ă��邽�ߓo�^�ł��܂���", name.c_str());

			return;
		}

		// �t�@�C�����J��
		std::ifstream file(filename, std::ios::binary);
		if (!file)
		{
			char s[256];
			snprintf(s, 256, "[ERROR] %s: %s���J���܂���\n", __func__, filename.c_str());
			OutputDebugStringA(s);
			return;
		}

		// �t�@�C����ǂݍ���
		const size_t filesize = std::filesystem::file_size(filename);
		std::vector<uint8_t> buffer(filesize);
		file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
		file.close();

		// �w�b�_��������擾
		const size_t tgaHeaderSize = 18;	// �w�b�_���̃o�C�g��
		const int imageOffset = tgaHeaderSize + buffer[0];	// �摜�f�[�^�̈ʒu
		const uint8_t imageType = buffer[2];				// �摜�`��
		const int pixelBytes = (buffer[16] + 7) / 8;		// 1�s�N�Z���̃o�C�g��
		int width = buffer[12] + buffer[13] * 256;
		int height = buffer[14] + buffer[15] * 256;

		// ���k�`���̏ꍇ�͓W�J����
		//  0(0b0000): �摜����
		//  1(0b0001): �C���f�b�N�X(�����k)
		//  2(0b0010): �g�D���[�J���[(�����k)
		//  3(0b0011): ����(�����k)
		//  9(0b1001): �C���f�b�N�X(RLE)
		// 10(0b1010): �g�D���[�J���[(RLE)
		// 11(0b1011): ����(RLE)
		if (imageType & 0b1000)
		{
			// �W�J�p�̃o�b�t�@��p��
			const int imageBytes = width * height * pixelBytes;	// �W�J��̃o�C�g��
			std::vector<uint8_t> tmp(imageOffset + imageBytes);

			// swap�ɔ����āA�摜�f�[�^���O�̕����R�s�[
			std::copy_n(buffer.begin(), imageOffset, tmp.begin());

			// �摜�f�[�^��W�J
			const uint8_t* src = buffer.data() + imageOffset;	// ���k�f�[�^�̃A�h���X
			uint8_t* dest = tmp.data() + imageOffset;			// �f�[�^�W�J��A�h���X
			const uint8_t* const destEnd = dest + imageBytes;	// �W�J�I���A�h���X

			while (dest != destEnd) {
				// �o�P�b�g�w�b�_����ID�ƃf�[�^�����擾
				const int isRLE = *src & 0x80;
				const int count = (*src & 0x7f) + 1;
				++src;	// �A�h���X���o�P�b�g�f�[�^�̈ʒu�ɐi�߂�

				if (isRLE) {
					// ���k�f�[�^�̏ꍇ�A�p�P�b�g�f�[�^���w��񐔃R�s�[
					for (int a = 0; a < count; ++a) {
						memcpy(dest, src, pixelBytes);
						dest += pixelBytes;
					}
					src += pixelBytes;
				}
				else {
					// �����k�f�[�^�̏ꍇ�A�p�P�b�g�f�[�^�S�̂��R�s�[
					const int dataBytes = pixelBytes * count;
					memcpy(dest, src, dataBytes);
					dest += dataBytes;
					src += dataBytes;
				}
			}

			// buffer��tmp�̓��e����
			buffer.swap(tmp);
		}
		// �i�[�������u�ォ�牺�v�̏ꍇ�A�f�[�^���㉺���]
		bool topToBottom = buffer[17] & 0b0010'0000;
		//if (usage == Usage::forGltf)
		//{
		//	topToBottom = !topToBottom;
		//}
		if (topToBottom)
		{
			const int pixelDepth = buffer[16];						// �P�s�N�Z���̃r�b�g��
			const int lineByteSize = width * pixelDepth / 8;		// 1�s�̃o�C�g��
			uint8_t* top = buffer.data() + tgaHeaderSize;			// ��̍s�̈ʒu
			uint8_t* bottom = top + lineByteSize * (height - 1);	// ���̍s�̈ʒu
			std::vector<uint8_t> tmp(lineByteSize);					// �㉺�̓���ւ��p�o�b�t�@

			// �s�P�ʂŏ㉺���]
			// �㉺�̍s�̈ʒu���t�]����܂ŌJ��Ԃ�
			while (top < bottom)
			{
				std::copy_n(top, lineByteSize, tmp.data());			// �u��̍s�̃R�s�[�v�����
				std::copy_n(bottom, lineByteSize, top);				// ���̍s���A��̍s�ɏ㏑��
				std::copy_n(tmp.data(), lineByteSize, bottom);		// �u��̍s�̃R�s�[�v�����̍s�ɏ㏑��
				top += lineByteSize;		// ��̍s�̈ʒu���P�s���Ɉړ�
				bottom -= lineByteSize;		// ���̍s�̈ʒu���P�s��Ɉړ�
			}
		}

		// 1�s�N�Z���̃r�b�g���ɑΉ�����`���̃Z�b�g������
		struct Format
		{
			int pixelDepth;		// TGA��1�s�N�Z���̃r�b�g��
			GLenum imageFormat;	// TGA�̃f�[�^�`��
			GLenum imageType;	// TGA�̃f�[�^�^
			GLenum gpuFormat;	// GPU���̃f�[�^�`��
		};
		constexpr Format formatList[] = {
			{ 32, GL_BGRA,	GL_UNSIGNED_BYTE,				GL_RGBA8 },
			{ 24, GL_BGR,	GL_UNSIGNED_BYTE,				GL_RGB8 },
			{ 16, GL_BGRA,	GL_UNSIGNED_SHORT_1_5_5_5_REV,	GL_RGB5_A1 },
			{ 15, GL_BGR,	GL_UNSIGNED_SHORT_1_5_5_5_REV,	GL_RGB5 },
			{  8, GL_RED,	GL_UNSIGNED_BYTE,				GL_R8 },
		};

		const Format* format = std::find_if(formatList, std::end(formatList) - 1,
			[pixelDepth = buffer[16]](const Format& e) { return e.pixelDepth == pixelDepth; });

		// ���݂̃A���C�����g���L�^
		GLint alignment;
		//glGetintegerv(�擾����p�����[�^��, �l���i�[����ϐ��̃A�h���X)
		glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);

		// �摜�̃A���C�����g��ݒ�
		// 1�s�̃o�C�g����4�Ŋ���؂��Ƃ���4,2�Ŋ���؂��Ƃ���2,����ȊO��1�ɐݒ�
		constexpr int alignmentList[] = { 4,1,2,1 };
		const int lineByteSize = width * pixelBytes;	// ��s�̃o�C�g��
		const int imageAlignment = alignmentList[lineByteSize % 4];

		// �A���C�����g��ύX
		if (alignment != imageAlignment)
		{
			// glPixelStorei(�ݒ肷��p�����[�^��, �ݒ肷��l)
			glPixelStorei(GL_UNPACK_ALIGNMENT, imageAlignment);
		}

		// �e�N�X�`�����쐬
		GLuint object = 0; // �e�N�X�`���̊Ǘ��ԍ�

		// �e�N�X�`�����쐬
		// (�e�N�X�`���̎�ށA�쐬������A�ԍ����i�[����z��A�h���X)
		glCreateTextures(GL_TEXTURE_2D, 1, &object);

		//�@�摜�f�[�^�̃R�s�[��ł���f�o�t�������̈���m�ۂ��܂�
		// (�e�N�X�`���̊Ǘ��ԍ�,�쐬���郌�x����,�s�N�Z���`��,���A����)
		glTextureStorage2D(object, 1, format->gpuFormat, width, height);

		// �摜�f�[�^��GPU�ɃR�s�[
		// (�e�N�X�`���̊Ǘ��ԍ��A�R�s�[��̃��C���[�ԍ��A�R�s�[��̂w���W�A�R�s�[��̂x���W�A
		// �R�s�[����摜�̕��A�R�s�[����摜�̍����A�s�N�Z���Ɋ܂܂��v�f�Ə����A�v�f�̕��A�摜�f�[�^�̃A�h���X)
		glTextureSubImage2D(object, 0, 0, 0, width, height,
			format->imageFormat, format->imageType, buffer.data() + tgaHeaderSize);

		// �A���C�����g���ɖ߂�
		if (alignment != imageAlignment)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
		}

		// �O���[�X�P�[���e�N�X�`���̏ꍇ�A�Ԑ������~�h���ƐɃR�s�[����悤�ɂ��ݒ肷��
		if (format->imageFormat == GL_RED)
		{
			// glTextureParameteri(�e�N�X�`���̊Ǘ��ԍ��A�ݒ肷��p�����[�^���A�ݒ肷��l)
			glTextureParameteri(object, GL_TEXTURE_SWIZZLE_R, GL_RED);
			glTextureParameteri(object, GL_TEXTURE_SWIZZLE_G, GL_RED);
			glTextureParameteri(object, GL_TEXTURE_SWIZZLE_B, GL_RED);
		}

		// �ǂݍ��񂾃p�����[�^�Ńe�N�X�`�����쐬
		TexturePtr texture = std::make_shared<Texture>(name, object, width, height);
		if (!texture)
		{
			LOG_ERROR("(Texture)%s�̍쐬�Ɏ��s", name.c_str());
			return;
		}

		// �쐬�����e�N�X�`����z��ɓo�^
		LOG("(Texture)%s��o�^", name.c_str());
		textureCache.emplace(name, texture);
	}

	/**
	* OBJ�t�@�C����ǂݍ���
	*
	* @param name		���b�V���̖��O
	* @param filename	Obj�t�@�C����
	*/
	void ResouceManager::LoadObj(const std::string& name, const std::string& filename)
	{
		meshBuffer.lock()->LoadObj(name, filename);
	}

	/**
	* �V�F�[�_�t�@�C����ǂݍ���
	*
	* @param name		�V�F�[�_�̖��O
	* @param filenameVS �o�[�e�b�N�X�V�F�[�_�t�@�C��
	* @param filenameFS �t���O�����g�V�F�[�_�t�@�C��
	*/
	void ResouceManager::LoadShader(const std::string& name, const std::string& filenameVS, const std::string& filenameFS)
	{
		// ���łɓo�^����Ă��邽�ߓo�^�ł��Ȃ�
		auto itr = shaderCache.find(name);
		if (itr != shaderCache.end())
		{
			LOG_ERROR("(Shader)%s�͂��łɓo�^����Ă��邽�ߓo�^�ł��܂���", name.c_str());
			return;
		}

		// �V�F�[�_���쐬
		auto shader = ShaderObject::Create(name, filenameVS, filenameFS);
		if (!shader)
		{
			LOG_ERROR("(Shader)%s�̍쐬�Ɏ��s", name.c_str());
			return;
		}

		// �쐬�����V�F�[�_��z��ɓo�^����
		LOG("(Shader)%s��o�^", name.c_str());
		shaderCache.emplace(name, shader);
	}

	/**
	* �e�N�X�`�����擾
	*
	* @param name �e�N�X�`���̖��O
	*
	* @return name�ɂ������e�N�X�`��
	*/
	TexturePtr ResouceManager::GetTexture(const std::string& name)
	{
		// �L���b�V��������΁A�L���b�V�����ꂽ�e�N�X�`����Ԃ�
		auto itr = textureCache.find(name);
		if (itr != textureCache.end())
		{
			return itr->second;
		}

		LOG_ERROR("(Texture)%s�͓o�^����Ă��܂���", name.c_str());
		return nullptr;
	}

	/**
	* �X�^�e�B�b�N���b�V�����擾
	*
	* @param name �X�^�e�B�b�N���b�V���̖��O
	*
	* @return name�ɂ������X�^�e�B�b�N���b�V��
	*/
	StaticMeshPtr ResouceManager::GetStaticMesh(const std::string& name)
	{
		return meshBuffer.lock()->GetStaticMesh(name);
	}

	/**
	* �X�P���^�����b�V�����擾
	*
	* @param name �X�P���^�����b�V���̖��O
	*
	* @return name�ɂ������X�P���^�����b�V��
	*/
	SkeletalMeshPtr ResouceManager::GetSkeltalMesh(const std::string& name)
	{
		return meshBuffer.lock()->GetSkeletalMesh(name);
	}
}