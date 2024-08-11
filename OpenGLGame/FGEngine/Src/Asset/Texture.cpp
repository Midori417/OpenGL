/**
* @file Texture.cpp
*/
#include "FGEngine/Asset/Texture.h"
#include <vector>
#include <fstream>
#include <filesystem>

#pragma warning(push)
#pragma warning(disable:4005)
#include <Windows.h>
#pragma warning(pop)

namespace FGEngine
{

	/**
	* コンストラクタ
	*
	* @parma name		テクスチャの名前
	* @param filename	テクスチャファイル名
	* @parma usage		テクスチャの形式
	*/
	Texture::Texture(const std::string& name, const std::string& filename, TextureType type, GLenum filterMode)
		: name(name)
	{
		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			char s[256];
			snprintf(s, 256, "[ERROR] %s: %sを開けません\n", __func__, filename.c_str());
			OutputDebugStringA(s);
			return;
		}

		// ファイルを読み込む
		const size_t filesize = std::filesystem::file_size(filename);
		std::vector<uint8_t> buffer(filesize);
		file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
		file.close();

		// ヘッダから情報を取得
		const size_t tgaHeaderSize = 18;	// ヘッダ情報のバイト数
		const int imageOffset = tgaHeaderSize + buffer[0];	// 画像データの位置
		const uint8_t imageType = buffer[2];				// 画像形式
		const int pixelBytes = (buffer[16] + 7) / 8;		// 1ピクセルのバイト数
		width = buffer[12] + buffer[13] * 256;
		height = buffer[14] + buffer[15] * 256;

		// 圧縮形式の場合は展開する
		//  0(0b0000): 画像無し
		//  1(0b0001): インデックス(無圧縮)
		//  2(0b0010): トゥルーカラー(無圧縮)
		//  3(0b0011): 白黒(無圧縮)
		//  9(0b1001): インデックス(RLE)
		// 10(0b1010): トゥルーカラー(RLE)
		// 11(0b1011): 白黒(RLE)
		if (imageType & 0b1000)
		{
			// 展開用のバッファを用意
			const int imageBytes = width * height * pixelBytes;	// 展開後のバイト数
			std::vector<uint8_t> tmp(imageOffset + imageBytes);

			// swapに備えて、画像データより前の部分コピー
			std::copy_n(buffer.begin(), imageOffset, tmp.begin());

			// 画像データを展開
			const uint8_t* src = buffer.data() + imageOffset;	// 圧縮データのアドレス
			uint8_t* dest = tmp.data() + imageOffset;			// データ展開先アドレス
			const uint8_t* const destEnd = dest + imageBytes;	// 展開終了アドレス

			while (dest != destEnd) {
				// バケットヘッダからIDとデータ数を取得
				const int isRLE = *src & 0x80;
				const int count = (*src & 0x7f) + 1;
				++src;	// アドレスをバケットデータの位置に進める

				if (isRLE) {
					// 圧縮データの場合、パケットデータを指定回数コピー
					for (int a = 0; a < count; ++a) {
						memcpy(dest, src, pixelBytes);
						dest += pixelBytes;
					}
					src += pixelBytes;
				}
				else {
					// 無圧縮データの場合、パケットデータ全体をコピー
					const int dataBytes = pixelBytes * count;
					memcpy(dest, src, dataBytes);
					dest += dataBytes;
					src += dataBytes;
				}
			}

			// bufferとtmpの内容交換
			buffer.swap(tmp);
		}
		// 格納方向が「上から下」の場合、データを上下反転
		bool topToBottom = buffer[17] & 0b0010'0000;
		if (type == TextureType::Gltf)
		{
			topToBottom = !topToBottom;
		}
		if (topToBottom)
		{
			const int pixelDepth = buffer[16];						// １ピクセルのビット数
			const int lineByteSize = width * pixelDepth / 8;		// 1行のバイト数
			uint8_t* top = buffer.data() + tgaHeaderSize;			// 上の行の位置
			uint8_t* bottom = top + lineByteSize * (height - 1);	// 下の行の位置
			std::vector<uint8_t> tmp(lineByteSize);					// 上下の入れ替え用バッファ

			// 行単位で上下反転
			// 上下の行の位置が逆転するまで繰り返す
			while (top < bottom) {
				std::copy_n(top, lineByteSize, tmp.data());			// 「上の行のコピー」を作る
				std::copy_n(bottom, lineByteSize, top);				// 下の行を、上の行に上書き
				std::copy_n(tmp.data(), lineByteSize, bottom);		// 「上の行のコピー」を下の行に上書き
				top += lineByteSize;		// 上の行の位置を１行下に移動
				bottom -= lineByteSize;		// 下の行の位置を１行上に移動
			}
		}

		// 1ピクセルのビット数に対応する形式のセットを検索
		struct Format
		{
			int pixelDepth;		// TGAの1ピクセルのビット数
			GLenum imageFormat;	// TGAのデータ形式
			GLenum imageType;	// TGAのデータ型
			GLenum gpuFormat;	// GPU側のデータ形式
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

		// 現在のアライメントを記録
		GLint alignment;
		//glGetintegerv(取得するパラメータ名, 値を格納する変数のアドレス)
		glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);

		// 画像のアライメントを設定
		// 1行のバイト数が4で割り切れるときは4,2で割り切れるときは2,それ以外は1に設定
		constexpr int alignmentList[] = { 4,1,2,1 };
		const int lineByteSize = width * pixelBytes;	// 一行のバイト数
		const int imageAlignment = alignmentList[lineByteSize % 4];

		// アライメントを変更
		if (alignment != imageAlignment)
		{
			// glPixelStorei(設定するパラメータ名, 設定する値)
			glPixelStorei(GL_UNPACK_ALIGNMENT, imageAlignment);
		}

		// テクスチャを作成
		GLuint object = 0; // テクスチャの管理番号
		// テクスチャを作成
		// (テクスチャの種類、作成する個数、番号を格納する配列アドレス)
		glCreateTextures(GL_TEXTURE_2D, 1, &object);
		//　画像データのコピー先であるＧＰＵメモリ領域を確保します
		// (テクスチャの管理番号,作成するレベル数,ピクセル形式,幅、高さ)
		glTextureStorage2D(object, 1, format->gpuFormat, width, height);
		// 画像データをGPUにコピー
		// (テクスチャの管理番号、コピー先のレイヤー番号、コピー先のＸ座標、コピー先のＹ座標、
		// コピーする画像の幅、コピーする画像の高さ、ピクセルに含まれる要素と順序、要素の方、画像データのアドレス)
		glTextureSubImage2D(object, 0, 0, 0, width, height,
			format->imageFormat, format->imageType, buffer.data() + tgaHeaderSize);

		// アライメント元に戻す
		if (alignment != imageAlignment) {
			glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
		}

		// グレースケールテクスチャの場合、赤成分をミドリと青にコピーするようにし設定する
		if (format->imageFormat == GL_RED) {
			// glTextureParameteri(テクスチャの管理番号、設定するパラメータ名、設定する値)
			glTextureParameteri(object, GL_TEXTURE_SWIZZLE_R, GL_RED);
			glTextureParameteri(object, GL_TEXTURE_SWIZZLE_G, GL_RED);
			glTextureParameteri(object, GL_TEXTURE_SWIZZLE_B, GL_RED);
		}
		glTextureParameteri(object, GL_TEXTURE_MAG_FILTER, filterMode);
		glTextureParameteri(object, GL_TEXTURE_MIN_FILTER, filterMode);

		// 管理ID
		id = object;
	}

	/**
	* 空のテクスチャを作成するコンストラクタ
	*
	* @param name		テクスチャ識別用の名前
	* @param widht		テクスチャの幅(ピクセル数)
	* @param height		テクスチャの高さ(ピクセル数)
	* @param gpuFormat	データ形式
	* @param wrapMode	ラップモード
	*/
	Texture::Texture(const std::string& name, int width, int height, GLenum gpuFormat, GLenum wrapMode)
		: name(name), width(width), height(height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, gpuFormat, width, height);
		glTextureParameteri(id, GL_TEXTURE_WRAP_S, wrapMode);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, wrapMode);

		// 深度テクスチャの場合、シャドウマッピングのために比較モードを設定する
		switch (gpuFormat)
		{
		case GL_DEPTH_COMPONENT16:
		case GL_DEPTH_COMPONENT24:
		case GL_DEPTH_COMPONENT32:
		case GL_DEPTH_COMPONENT32F:
			glTextureParameteri(id, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
			break;
		default:
			break;
		}
	}

	/**
	* デストラクタ
	*/
	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	/**
	* テクスチャを読み込んで作成
	*
	* @param name		テクスチャの名前
	* @apram filename	テクスチャのファイル
	*
	* @return 作成したテクスチャポインター
	*/
	std::shared_ptr<Texture> Texture::Create(const std::string& name, const std::string& filename, 
		TextureType type, GLenum filterMode)
	{
		return std::make_shared<Texture>(name, filename, type, filterMode);
	}

	/**
	* 空のテクスチャを作成する
	*
	* @param name		テクスチャ識別用の名前
	* @param widht		テクスチャの幅(ピクセル数)
	* @param height		テクスチャの高さ(ピクセル数)
	* @param gpuFormat	データ形式
	* @param wrapMode	ラップモード
	*
	* @return 作成したテクスチャポインター
	*/
	std::shared_ptr<Texture> Texture::Create(const std::string& name, int width, int height, GLenum gpuFormat, GLenum wrapMode)
	{
		return std::make_shared<Texture>(name, width, height, gpuFormat, wrapMode);
	}
}