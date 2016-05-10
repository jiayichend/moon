#ifndef __ACTOR_EQUIP_H__
#define __ACTOR_EQUIP_H__

class CPlayer;

/*******************************************
* 玩家装备模块
******************************************/
class CPlayerEquip :
	public CDoerUnit
{
public:
	typedef CDoerUnit super;
	//角色装备位置定义
	enum EquipPosition
	{
		epHat = 0,//头盔（左侧第一格）
		epDress = 1,//衣服（左侧第二格）
		epPants = 2,//裤子（右侧第一格）
		epBoot = 3,//靴子（右侧第二格）

		EquipCount,//装备数量
	};

public:
	CPlayerEquip();
	~CPlayerEquip();

	virtual bool init();
	virtual bool loadData(CDataPacketReader &data);
	virtual void saveData(CDataPacket &data);
	virtual void dispatchRecvPacket(int btCmd, CDataPacketReader &inPacket);

	//获取装备穿戴位置
	int getEquipPos(int btItemType);
	//通过物品系列号获取装备位置索引
	int findEquipItem(common::ItemSeries series);
	//向客户端发送装备列表
	void sendEquipItems();

private:
	void HandleTakeOnItem(CDataPacketReader &inPacket);
	void HandleTakeOffItem(CDataPacketReader &inPacket);
	void TakeOffItem(int nEquipPos);

public:
	UserItem*	m_ItemList[EquipCount];//装备物品列表，wItemId为0表示没有装备
};

#endif
