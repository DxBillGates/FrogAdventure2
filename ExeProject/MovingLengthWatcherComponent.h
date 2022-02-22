#pragma once
#include "Header/GameFramework/Component/Component.h"

class MovingLengthWatcherComponent : public GE::Component
{
private:
	float movingLength;
	float movingMaxLength;
	float movingUIMaxLength;
	GE::Math::Vector3 offset;
public:
	MovingLengthWatcherComponent();
	~MovingLengthWatcherComponent();
	void Start() override;
	void Update(float deltaTime) override;
	void Draw() override;

	void SetMovingLength(float value);

	/// <summary>
	/// プレイヤーが進んだ距離を示すUIのサイズを指定する
	/// </summary>
	/// <param name="value">指定するサイズ (0 ~ 1080)</param>
	void SetMovingUIMaxLength(float value);

	/// <summary>
	/// プレイヤーが進んだ距離を示すUIの表示位置のオフセットを指定する
	/// </summary>
	/// <param name="offset">指定する2D座標</param>
	void SetOffset(const GE::Math::Vector3& offset);
};

