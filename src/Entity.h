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
	EntityManager	*entity_manager;


	Entity();//EntityManager *_entity_manager, int _entity_id);
	void setEntityManagerInfo(EntityManager *_entity_manager, int _entity_id);
	void setAnimation(const std::string & _id_animation);
	void setFrame(int _idx_frame);
	inline int getWidth()  {return width;}
	inline  int getHeight()  {return height;}
	inline int getX()  {return x;}
	inline int getY()  {return y;}
	inline int getEntityId()  {return entity_id;}
	void setMoveTime(Uint32 _move_time){move_time=_move_time;}
	Uint32 getMoveTime(){return move_time;}

	void deInit();

	//void setSkipFrame(float _skip_frame);

	Frame 			* 	getFrame();
	std::string 		getAnimation();
	Collider 		*	getCollider();
	void				die();
	EntityManager 	* 	getEntityManager();

	void update();

	~Entity();

private:

	float		scale;
	int			 entity_id;
	//float 		skip_frame;
	unsigned 	idx_current_frame;
	int 		width, height;
	bool		fix_frame;
	Uint32		next_move_time;
	Uint32		move_time;


	std::string	id_current_animation;
	int 		next_time_change_frame;
	EntityAnimation	*current_animation;
	//int idx_fixed_frame;

	std::unordered_map<std::string, EntityAnimation *> *	animations;

};
