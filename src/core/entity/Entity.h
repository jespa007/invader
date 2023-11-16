/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

class EntityManager;
class Entity{
public:

	static bool testCollision(
			 Entity *	_e1
			 ,  Entity *	_e2
	);

	int 			x, y;
	int 			dx, dy;
	int				life_time;
	bool			is_active;
	bool			is_visible;


	Entity();//EntityManager *_entity_manager, int _entity_id);
	void setEntityManagerInfo(EntityManager *_entity_manager, size_t _entity_type_id, size_t _entity_id);
	void setFrameAnimation(size_t _frame_animation_idx);
	void setFrame(size_t _frame_idx);
	inline int getWidth()  {return width;}
	inline  int getHeight()  {return height;}
	inline int getX()  {return x;}
	inline int getY()  {return y;}
	inline int getEntityId()  {return entity_id;}
	void setMoveTime(Uint32 _move_time){move_time=_move_time;}
	Uint32 getMoveTime(){return move_time;}
	bool	finishedFrameAnimation(){return current_frame_idx==Frame::npos;}

	void deInit();

	//void setSkipFrame(float _skip_frame);

	Frame 			* 	getCurrentFrameData();
	size_t			 	getCurrentFrameIdx();
	size_t 				getCurrentAnimationIdx();
	Collider 		*	getCollider();
	void				die();
	EntityManager 	* 	getEntityManager();

	void update();

	~Entity();

private:

	float		scale;
	size_t		entity_id;
	size_t		entity_type_id;
	EntityManager	*entity_manager;
	//float 		skip_frame;
	int 		width, height;
	bool		fix_frame;
	Uint32		next_move_time;
	Uint32		move_time;


	size_t		current_frame_animation_idx;
	size_t		current_frame_idx;
	int 		next_time_change_frame;
	//EntityFrameAnimation	*current_animation;
	//size_t		current_animation_idx;
	//int idx_fixed_frame;

	std::vector<EntityFrameAnimation> *	frame_animations;

};
