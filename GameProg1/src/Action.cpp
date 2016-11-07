#include "stdafx.h"
#include "Action.h"

Action::Action()
{

}
void Action::Attack(Player target, Weapon weapon)
{
	target.recieveDamage(weapon.getDamageValue);
}

void Action::Attack(Enemy target, Weapon weapon)
{

}