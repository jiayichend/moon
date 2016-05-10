#ifndef __ENTITY_H__
#define __ENTITY_H__

using namespace lib::container;
using namespace lib::graph;
using namespace common;
class CMapGrid;
class Scene;
class CPlayer;

enum EntityType
{
	eUnknown,

	/** 注意：下面定义的实体类型的实现类必须是CDoer以及CDoer的子类 **/
	eActor = 100,
	eNormalMonster = 100,
	eNPC = 180,
	ePlayer = 255,
};

enum EntityStateMask
{
	esDescDirty = 0x00000001,//角色描述表变更
};

class CEntity :public CBaseObject
{
public:
	struct ViewStruct
	{
		unsigned short mask;
		CEntity* pEntity;
	};

public:
	CEntity();
	virtual ~CEntity();
	
	//初始化
	virtual void init(int x, int y);
	//例行逻辑处理
	virtual void run(TickTime dwCurrTick);
	virtual void disappear();
	virtual int getPlayerIndex(){return -1;}//CPlayer需要继承重载 返回playerIndex

	int findEntity(CBaseObject* pEntity);
	int getRandomKey(int min,int max);
	void setScene(Scene* scene,int x,int y);
	void setXY(int x,int y);
	EntityDesc& getEntityDescription(EntityDesc &desc, CPlayer *player);

protected:
	virtual void sceneChanged(Scene *oldScene, int ox, int oy);
	virtual void positionChanged(int ox, int oy);
	virtual void updateEntityDescription();

public:
	STDGUID			m_EntityId;//对象ID
	int				m_nX;//当前X坐标（像素坐标）
	int				m_nY;//当前Y坐标（像素坐标）
	unsigned int	m_dwStateMasks;//状态标志表
	unsigned char	m_btType;//实体类型，为EntityType枚举值
	char			m_btDirection;//角色朝向，0左1右
	bool			m_boDisappeared;//对象是否已消失并从地图移除
	bool			m_boDead;//角色是否已死亡
	bool			m_boGodMode;//超级无敌模式
	char			_______reserve[1];
	unsigned short	m_wEntityBody;//身体外形编号
	GRect			m_ImpactRect;//身体大小矩形
	Scene*			m_pScene;
	TickTime		m_dwDieTick;//对象死亡时间
	TickTime		m_dwDisappearTick;//对象消失的时间
protected:
	EntityDesc		m_EntityDesc;
			  
};


#endif