/**
* @file VertexArrayObject.cpp
*/
#include "VertexArrayObject.h"

namespace FGEngine::Rendering
{
	/**
	* コンストラクタ
	*/
	VertexArrayObject::VertexArrayObject()
	{
		glCreateVertexArrays(1, &id);
	}

	/**
	* デストラクタ
	*/
	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteVertexArrays(1, &id);
	}

	/**
	* VertexArrayObjectを作成
	* 
	* @return 作成したVertexArrayObjectポインター
	*/
	VertexArrayObjectPtr VertexArrayObject::Create()
	{
		return std::make_shared<VertexArrayObject>();
	}

	/**
	* 頂点アトリビュートを設定
	*
	* @param index	設定する頂点アトリビュートの番号(0～15)
	* @param size	要素のデータ数
	* @param stride	次の頂点データにある同一要素までの感覚(バイト数)
	* @param offset 頂点データ内における要素の位置(バイト数)
	*/
	void VertexArrayObject::SetAttribute(GLuint index, GLint size, size_t stride, size_t offset)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), reinterpret_cast<void*>(offset));
	}


}