/**
* @file Object,h
*/
#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include <memory>
#include <string>

// 先行宣言
class Object;
using ObjectPtr = std::shared_ptr<Object>;
class Transform;
using TransformPtr = std::shared_ptr<Transform>;
struct Vector3;
struct Quaternion;

/**
* Editor用(インスペクターでオブジェクトの破壊や表示を制御するビットマスク)
*/
enum class HideFlags
{
	None = 0x0,
	Destroy = 0x1,
};

/**
* 全てのオブジェクトの基底クラス
*/
class Object
{
public:

	// === コンストラクタ・デストラクタ === //
	Object() = default;
	virtual ~Object() = default;

private:

	// オブジェクトのインスタンスId
	int m_InstanceId = -1;

	// オブジェクト名
	std::string name = "Object";

	// オブジェクトの状態
	HideFlags hideFlags = HideFlags::None;

public:

	/**
	* インスタンス番号を取得
	*/
	int GetInstanceId() const
	{
		return m_InstanceId;
	}

	/**
	* オブジェクトの名前を設定と取得
	*/
	std::string ToString() const
	{
		return name;
	}
	void SetName(const std::string& value)
	{
		this->name = value;
	}

	/**
	* オブジェクト状態ビットマスクの設定と取得
	*/
	HideFlags GetHideFlags() const
	{
		return hideFlags;
	}
	void SetHideFlags(HideFlags flag)
	{
		this->hideFlags = flag;
	}

};

#endif // !OBJECT_H_INCLUDED
