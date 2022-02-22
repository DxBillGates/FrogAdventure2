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
	/// �v���C���[���i�񂾋���������UI�̃T�C�Y���w�肷��
	/// </summary>
	/// <param name="value">�w�肷��T�C�Y (0 ~ 1080)</param>
	void SetMovingUIMaxLength(float value);

	/// <summary>
	/// �v���C���[���i�񂾋���������UI�̕\���ʒu�̃I�t�Z�b�g���w�肷��
	/// </summary>
	/// <param name="offset">�w�肷��2D���W</param>
	void SetOffset(const GE::Math::Vector3& offset);
};

