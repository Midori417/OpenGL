/**
* @file VertexArrayObject.h
*/
#ifndef FGENGINE_VECTEXARRAYOBJECT_H_INCLUDED
#define FGENGINE_VECTEXARRAYOBJECT_H_INCLUDED
#include "FGEngine/Package/Glad.h"
#include <memory>

namespace FGEngine::RenderingSystem
{
	// 先行宣言
	class VertexArrayObject;
	using VertexArrayObjectPtr = std::shared_ptr<VertexArrayObject>;

	/**
	* 頂点配列オブジェクト(VAO)
	*
	* 頂点バッファに格納されている頂点データについて
	* 各要素がどのように配置されているかを記述するオブジェクト
	*/
	class VertexArrayObject
	{
	public:
		
		// コンストラクタ・デストラクタ
		VertexArrayObject();
		~VertexArrayObject();

		// コピーと代入を禁止
		VertexArrayObject(const VertexArrayObject&) = delete;
		VertexArrayObject& operator=(const VertexArrayObject&) = delete;

		/**
		* 頂点配列オブジェクトを作成する
		*
		* @return 作成した頂点配列オブジェクトのポインター
		*/
		static VertexArrayObjectPtr Create();

		/**
		* 頂点配列オブジェクトの管理番号を取得
		*/
		operator GLuint() const
		{
			return id;
		}

		/**
		* 頂点アトリビュートを設定
		*
		* @param index	設定する頂点アトリビュートの番号(0～15)
		* @param size	要素のデータ数
		* @param stride	次の頂点データにある同一要素までの感覚(バイト数)
		* @param offset 頂点データ内における要素の位置(バイト数)
		*/
		void SetAttribute(GLuint index, GLint size, size_t stride, size_t offset);

	private:

		// VertexArrayObjectの管理番号
		GLuint id = 0; 
	};
}
#endif // !VECTEXARRAYOBJECT_H_INCLUDED
