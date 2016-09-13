//
// Created by cvalenza on 8/30/16.
//

#include "Player.h"
#include "Game.h"
#include "res.h"
#include "Joystick.h"
#include "math.h"

void Player::_init()
{
	atk_anim_timer = std::chrono::milliseconds(0);

	view->setPosition(game->getSize() / 2);
	character = new Sprite;
	character->setResAnim(res::ui.getResAnim("player"));
	character->attachTo(view);
	character->setAnchor(0.5f, 0.5f);

	weapon = new Sprite;
	weapon->setResAnim(res::ui.getResAnim("sword"));
	weapon->attachTo(character);
	weapon->setVisible(false);
}

void Player::move(timeMS dt)
{
	Vector2 dir;
	Vector2 pos = view->getPosition();

	if (game->move->getDirection(dir)) {
		Vector2 l_dir;

		if (game->look->getDirection(l_dir)) {
			pos = pos + dir * (dt / 1000.0f) * 3.5f;
		} else {
			pos = pos + dir * (dt / 1000.0f) * 5;
		}

		float angle = atan2f(dir.y, dir.x);

		if (angle >= -3 && angle <= 1.5) {
			angle += M_PI / 2;
		} else {
			angle -= 1.5f * M_PI;
		}

		view->setRotation(angle);
	}

	if (pos.x < 0.25f * game->getWidth()) {
		pos.x = 0.25f * game->getWidth();
	} else if (pos.x > 0.75f * game->getWidth()) {
		pos.x = 0.75f * game->getWidth();
	}

	if (pos.y < 0.25f * game->getHeight()) {
		pos.y = 0.25f * game->getHeight();
	} else if (pos.y > 0.75f *  game->getHeight()) {
		pos.y = 0.75f * game->getHeight();
	}

	view->setPosition(pos);
}

void Player::changeAnim(std::string action, int ms)
{
	if (action == "stand") {
		character->addTween(TweenAnim(res::ui.getResAnim("player"), 0, 0), ms);
	} else if (action, "swing") {
		character->addTween(TweenAnim(res::ui.getResAnim("player"), 1, 4), ms);
	}
}

void Player::swingAnimation(int ms)
{
	using namespace std::chrono;
	milliseconds cur_time = duration_cast< milliseconds >
		(system_clock::now().time_since_epoch());

	if (cur_time - atk_anim_timer > milliseconds(ms)) {
		character->setResAnim(res::ui.getResAnim("swing"));
		changeAnim("swing", ms);
		//character->addTween(TweenAnim(res::ui.getResAnim("player"), 1, 4), ms);
		atk_anim_timer = cur_time;
	}
}

void Player::attack()
{
	Vector2 dir;

	if (game->look->getDirection(dir)) {
		float angle = atan2f(dir.y, dir.x);

		if (angle >= -3 && angle <= 1.5) {
			angle += M_PI / 2;
		} else {
			angle -= 1.5f * M_PI;
		}

		view->setRotation(angle);

		swingAnimation(300);
	} else {
		changeAnim("stand", 1);
		//character->addTween(TweenAnim(res::ui.getResAnim("player"), 0, 0), 1);
	}
}

void Player::_update(const UpdateState& us)
{
	weapon->setVisible(false);

	move(us.dt);
	attack();
}