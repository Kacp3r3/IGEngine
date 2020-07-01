#include "Player.h"

Player::Player(Model* m)
	:
	Entity(m)
{}

void Player::processKeyboard(Movement m, float dt)
{
	float currVel=0.f;
	float roation = m_vecRotation.y;
	switch (m)
	{
		case Movement::FORWARD:
			currVel = m_fVelocity;
			break;
		case Movement::BACKWARD:
			currVel = -m_fVelocity;
			break;
		case Movement::LEFT:
			//currVel = -m_fVelocity;
			//roation += -90.f;
			m_vecRotation.y += 120 * dt;
			break;
		case Movement::RIGHT:
			//currVel = -m_fVelocity;
			//roation += 90.f;
			m_vecRotation.y -= 120 * dt;
			break;
	}
	float distance = currVel * dt;
	float dx = distance * glm::sin(glm::radians(roation));
	float dz = distance * glm::cos(glm::radians(roation));
	updatePos({ dx,0,dz });
}
