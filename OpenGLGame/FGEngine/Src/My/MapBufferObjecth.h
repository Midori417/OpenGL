/**
* @file MapBufferObject.h
*/
#ifndef FGENGINE_MAPBUFFEROBJECT_H_INCLUDED
#define FGENGINE_MAPBUFFEROBJECT_H_INCLUDED
#include "Package/Glad.h"
#include <memory>

namespace FGEngine::RenderingSystem
{
	// 先行宣言
	class MappedBufferObject;
	using MappedBufferObjectPtr = std::shared_ptr<MappedBufferObject>;

	/**
	* バッファオブジェクト(マップあり)
	*/
	class MappedBufferObject
	{
	public:

		/**
		* バッファオブジェクトを作成する
		*
		* @parma size		バッファオブジェクトのバイトサイズ
		* @param type		バッファオブジェクトの種類
		* @param access		以下のいずれかを指定する
		*					GL_READ_WRITE 読み取り書き込みの両対応でマップする
		*					GL_READ_ONLY　読みとり専用としてマップする
		*					GL_WRITE_ONLY 書き込み専用としてマップする
		*/
		MappedBufferObject(GLsizeiptr size, GLenum type, GLenum access);

		/**
		* デストラクタ
		*/
		~MappedBufferObject();

		// コピーと代入を禁止
		MappedBufferObject(const MappedBufferObject&) = delete;
		MappedBufferObject& operator=(const MappedBufferObject&) = delete;

		/**
		* バッファオブジェクトを作成する
		*
		* @parma size		バッファオブジェクトのバイトサイズ
		* @param type		バッファオブジェクトの種類
		* @param access		以下のいずれかを指定する
		*					GL_READ_WRITE 読み取り書き込みの両対応でマップする
		*					GL_READ_ONLY　読みとり専用としてマップする
		*					GL_WRITE_ONLY 書き込み専用としてマップする
		*
		* @return 作成したバッファオブジェクトへのポインタ
		*/
		static MappedBufferObjectPtr Create(GLsizeiptr size, GLenum type, GLenum access);

		/**
		* 管理番号を取得
		*/
		operator GLuint() const;

		/**
		* バッファサイズを取得
		*/
		GLsizeiptr GetSize() const;

		/**
		* GPUがバッファを使い終わるのを待つ
		*/
		void WaitSync();

		/**
		* データのコピー先アドレスを取得する
		*/
		uint8_t* GetMappedAddress()const;

		/**
		* 指定した範囲をOpenGLコンテキストに割り当てる
		*
		* @parma index	割り当てるバインディングポイント番号
		* @param offset	割り当て範囲の先頭位置
		* @parma size	割り当て範囲のバイトサイズ
		*/
		void Bind(GLuint index, size_t offset, size_t size);

		/**
		* コピー先バッファを切り替える
		*/
		void SwapBuffers();

	private:

		// 管理Id
		GLuint id = 0;

		// バッファサイズ
		GLsizeiptr bufferSize = 0;

		// データコピー先アドレス
		uint8_t* p = nullptr;

		// コピー先バッファのインデックス
		size_t bufferIndex = 0;		

		// 同期オブジェクト
		GLsync syncList[2] = { 0, 0};

		// バッファの種類
		GLenum type = GL_ARRAY_BUFFER;	

	};
}
#endif // !MAPBUFFEROBJECT_H_INCLUDED
