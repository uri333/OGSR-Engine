#pragma once 
class CEntity;
class CEntityAlive;
//////////////////////////////////////////////////////////////////////////
// Member local goal notification
//////////////////////////////////////////////////////////////////////////
enum EMemberGoalType {
	MG_AttackEnemy,				// entity
	MG_PanicFromEnemy,			// entity
	MG_InterestingSound,		// position
	MG_DangerousSound,			// position
	MG_WalkGraph,				// node
	MG_Rest,					// node, position
	MG_None,
};

struct SMemberGoal {
	EMemberGoalType		type;
	CEntity				*entity;
	Fvector				position;
	u32					node;

	SMemberGoal			() {
		type			= MG_None;
		entity			= 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// Squad command 
//////////////////////////////////////////////////////////////////////////
enum ESquadCommandType { 
	SC_EXPLORE,
	SC_ATTACK,
	SC_THREATEN,
	SC_COVER,
	SC_FOLLOW,
	SC_FEEL_DANGER,
	SC_EXPLICIT_ACTION,
	SC_REST,
	SC_NONE,
};

struct SSquadCommand {
	ESquadCommandType	type;	// ��� �������

	CEntity		*entity;
	Fvector		position;
	u32			node;
	Fvector		direction;

};


/////////////////////////////////////////////////////////////////////////////////////////
// MonsterSquad Class
class CMonsterSquad {
	CEntity				*leader;

	DEFINE_MAP		(CEntity*, SMemberGoal,		MEMBER_GOAL_MAP,	MEMBER_GOAL_MAP_IT);
	DEFINE_MAP		(CEntity*, SSquadCommand,	MEMBER_COMMAND_MAP, MEMBER_COMMAND_MAP_IT);

	// ����� ����� ������ ������ (����������� �� ������� �������)
	MEMBER_GOAL_MAP		m_goals;

	// ����� ������� ������ ������ (����������� �� ������� squad manager)
	MEMBER_COMMAND_MAP	m_commands;

	DEFINE_VECTOR	(u32, NODES_VECTOR, NODES_VECTOR_IT);
	NODES_VECTOR	m_locked_covers;

	DEFINE_VECTOR	(const CEntityAlive*, CORPSES_VECTOR, CORPSES_VECTOR_IT);
	CORPSES_VECTOR	m_locked_corpses;

public:
	
				CMonsterSquad		();
				~CMonsterSquad		();

	// -----------------------------------------------------------------

	void		RegisterMember		(CEntity *pE);
	void		RemoveMember		(CEntity *pE);

	bool		SquadActive			();

	// -----------------------------------------------------------------

	void			SetLeader			(CEntity *pE) {leader = pE;}
	CEntity			*GetLeader			() {return leader;}

	// -----------------------------------------------------------------
	
	void			UpdateGoal			(CEntity *pE, const SMemberGoal	&goal);
	void			UpdateCommand		(CEntity *pE, const SSquadCommand &com);

	
	void			GetGoal				(CEntity *pE, SMemberGoal &goal);
	void			GetCommand			(CEntity *pE, SSquadCommand &com);
	SMemberGoal		&GetGoal			(CEntity *pE);
	SSquadCommand	&GetCommand			(CEntity *pE);

	// -----------------------------------------------------------------
	
	
	void		UpdateSquadCommands	();	

	void		remove_links			(CObject *O);
	
	// return count of monsters in radius for object
	u8			get_count				(const CEntity *object, float radius);


	///////////////////////////////////////////////////////////////////////////////////////
	//  ����� ������
	//////////////////////////////////////////////////////////////////////////////////////
	
	DEFINE_VECTOR	(CEntity*, ENTITY_VEC,	ENTITY_VEC_IT);	
	ENTITY_VEC		m_temp_entities;
	
	///////////////////////////////////////////////////////////////////////////////////////
	//  ����� ������� ��������
	//////////////////////////////////////////////////////////////////////////////////////
	
	DEFINE_MAP		(CEntity*, ENTITY_VEC,	ENEMY_MAP, ENEMY_MAP_IT);
	
	ENEMY_MAP		m_enemy_map;

	void			ProcessAttack					();
	
	
	// -- Temp -- 
	struct _elem {
		CEntity		*pE;
		Fvector		p_from;
		float		yaw;
	};
	xr_vector<_elem>	lines;
	// ------------

	void			Attack_AssignTargetDir			(ENTITY_VEC &members, CEntity *enemy);

	////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////
	//  ��������� idle
	//////////////////////////////////////////////////////////////////////////////////////
	ENTITY_VEC		front, back, left, right;
	
	void			ProcessIdle				();
	void			Idle_AssignAction		(ENTITY_VEC &members);

	////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////
	//  Covers
	//////////////////////////////////////////////////////////////////////////////////////
	bool			is_locked_cover			(u32 node);
	void			lock_cover				(u32 node);
	void			unlock_cover			(u32 node);
	////////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////
	//  Corpses
	//////////////////////////////////////////////////////////////////////////////////////
	bool			is_locked_corpse		(const CEntityAlive*);
	void			lock_corpse				(const CEntityAlive*);
	void			unlock_corpse			(const CEntityAlive*);
	////////////////////////////////////////////////////////////////////////////////////////

        bool home_in_danger() { return Device.dwTimeGlobal < m_home_danger_end_tick; }
        void set_home_in_danger() { m_home_danger_end_tick = Device.dwTimeGlobal + m_home_danger_mode_time; }

private:
        // danger mode is turns on when monsters hear dangerous sound or get a hit
        // danger mode turns off after m_danger_mode_time miliseconds
        u32 m_home_danger_mode_time;
        u32 m_home_danger_end_tick;
};
