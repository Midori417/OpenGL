/**
* @file MapBufferObject.cpp
*/
#include "FGEngine/Buffer/MapBufferObjecth.h"
#include "FGEngine/Debug.h"

namespace FGEngine
{
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
	MappedBufferObject::MappedBufferObject(GLsizeiptr size, GLenum type, GLenum access)
		:type(type)
	{
		// ダブルバッファのため、サイズを256バイト境界に繰り上げる
		bufferSize = ((size + 255) / 256) * 256;

		// アクセスの種類によってフラグを選択
		GLbitfield flags = GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
		switch (access)
		{
		default:
			LOG_ERROR("引数が間違っています(access=%d)", access);

			// フォースルーする
			// breakを省略可能でbreakに会うまで後続のcaseブロックを実行する
			[[fallthrough]];
		case GL_READ_WRITE:
			flags |= GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
			break;
		case GL_READ_ONLY:
			flags |= GL_MAP_READ_BIT;
			break;
		case GL_WRITE_ONLY:
			flags |= GL_MAP_WRITE_BIT;
			break;
		}

		// バッファオブジェクトを作成
		glCreateBuffers(2, id);
		glNamedBufferStorage(id[0], bufferSize, nullptr, flags);
		glNamedBufferStorage(id[1], bufferSize, nullptr, flags);

		// GPUメモリをCPUメモリアドレスにマップする
		p[0] = static_cast<uint8_t*>(glMapNamedBuffer(id[0], access));
		p[1] = static_cast<uint8_t*>(glMapNamedBuffer(id[1], access));
	}

	/**
	* デストラクタ
	*/
	MappedBufferObject::~MappedBufferObject()
	{
		glDeleteBuffers(2, id);
	}

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
	MappedBufferObjectPtr MappedBufferObject::Create(GLsizeiptr size, GLenum type, GLenum acceess)
	{
		return std::make_shared<MappedBufferObject>(size, type, acceess);
	}

	/**
	* バッファオブジェクトの管理番号を取得
	*/
	MappedBufferObject::operator GLuint() const
	{
		return id[bufferIndex];
	}

	/**
	* バッファサイズを取得
	*/
	GLsizeiptr MappedBufferObject::GetSize() const
	{
		return bufferSize;
	}

	/**
	* GPUがバッファを使い終わるのを待つ
	*/
	void MappedBufferObject::WaitSync()
	{
		for (GLsync& sync = syncList[bufferIndex]; sync;)
		{
			const GLuint64 timeout = 16'700'000;	// 16.7ミリ秒(約1/60秒)
			const GLenum status = glClientWaitSync(sync, 0, timeout);
			if (status != GL_TIMEOUT_EXPIRED)
			{
				// 使い終わった同期オブジェクトは削除しなくてはならない
				glDeleteSync(sync);
				sync = 0;
				break;
			}
		}
	}

	/**
	* データのコピー先アドレスを取得する
	*
	* @return コピー先アドレス
	*/
	uint8_t* MappedBufferObject::GetMappedAddress() const
	{
		return p[bufferIndex];
	}

	/**
	* 指定した範囲をOpenGLコンテキストに割り当てる
	*
	* @parma index	割り当てるバインディングポイント番号
	* @param offset	割り当て範囲の先頭位置
	* @parma size	割り当て範囲のバイトサイズ
	*/
	void MappedBufferObject::Bind(GLuint index, size_t offset, size_t size)
	{
		glBindBufferRange(type, index, id[bufferIndex], offset, size);
	}

	/**
	* コピー先バッファを切り替える
	*/
	void MappedBufferObject::SwapBuffers()
	{
		syncList[bufferIndex] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
		bufferIndex = (bufferIndex + 1) % 2;
	}
}