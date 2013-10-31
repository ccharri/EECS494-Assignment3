#ifndef __game__Arrow_h__
#define __game__Arrow_h__

#include <zenilib.h>
#include <memory>

#include "Enemy.h"
#include "Model_Wrapper.h"

class Arrow : public Enemy
{
public:
	Arrow(Zeni::Point3f location_, Zeni::Vector3f size_ = Zeni::Vector3f(), Zeni::Quaternion facing_ = Zeni::Quaternion(), float speed_ = 50) 
		: Enemy(location_, size_, facing_, speed_, 0)
	{
		setLeakAmount(0);
		lastDrop = signTimer.seconds();
		dropInterval = 0.5;
		signTimer.start();
	}

	~Arrow() {};

	virtual bool isTargetable() const override {return false;};
	virtual bool isAttackable() const override {return false;};

	void on_logic(float time_step) override;

	virtual std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();};

private:
	static Model_Wrapper model;
	Zeni::Chronometer<Zeni::Time> signTimer;
	float lastDrop;
	float dropInterval;
};

#endif