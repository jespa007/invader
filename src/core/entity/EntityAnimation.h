/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

#include "EntityAnimationOptions.h"

class EntityAnimation{
public:
	static const size_t npos=-1;

	Sprite sprite;

	EntityAnimation();
	EntityAnimation(const EntityAnimationOptions & _entity_state_options);


private:




};
