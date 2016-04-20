#pragma once
#include "C3DShape.h"

struct st3DParticle{
	//λ��
	Vec3 m_Position;
	//�ٶ�
	Vec3 m_Velocity;
	//���ٶ�
	Vec3 m_Acceleration;
	//��С
	Vec3 m_Size;
	//��С�仯�ٶ�
	Vec3 m_Size_Velocity;
	//ɫ��
	Vec3 m_Color;
	//ɫ�ʱ仯�ٶ�
	Vec3 m_Color_Velocity;
	float m_Life;
	//�����仯�ٶ�
	float m_Life_Velocity;
};

struct st3DParticleData{
	Vec3 m_Position_Min;
	Vec3 m_Position_Max;
	Vec3 m_Velocity_Min;
	Vec3 m_Velocity_Max;
	Vec3 m_Acceleration_Min;
	Vec3 m_Acceleration_Max;
	Vec3 m_Size_Min;
	Vec3 m_Size_Max;
	Vec3 m_Size_Velocity;
	Vec3 m_Color_Min;
	Vec3 m_Color_Max;
	Vec3 m_Color_Velocity;
	float m_Life_Min;
	float m_Life_Max;
	float m_Life_Velocity;
};

enum eParticleType
{
	PT_FIRE,
	PT_FIREWORK,
	PT_FOUNTAIN,
	PT_MAX,
};

class C3DParticleSystem : public C3DShape
{
public:
	C3DParticleSystem(void);
	~C3DParticleSystem(void);
public:
	void reset(int v_TotalSize, eParticleType _type, BlendFunc func);
	void InitPS_Fire(int v_TotalSize);
	void InitPS_FireWork(int v_TotalSize);
	void InitPS_Fountain(int v_TotalSize);
	void SetParticleData_FireWork(st3DParticleData& vParticle);
	void SetParticleData_Fire(st3DParticleData& vParticle);
	void SetParticleData_Fountain(st3DParticleData& vParticle);
	void addPS(float dt);
	virtual void Update();
	virtual void Render();

	void resetParticleInitPos(Vec3 pos);
	void resetParticleAccelerationMin(Vec3 acc);
	void resetParticleAccelerationMax(Vec3 acc);
	void resetParticleSizeMin(Vec3 size);
	void resetParticleSizeMax(Vec3 size);
	void resetParticleSizeVelocity(Vec3 size);
	void resetParticleVelocityMin(Vec3 vel);
	void resetParticleVelocityMax(Vec3 vel);
	void resetParticleColorMin(Vec3 color);
	void resetParticleColorMax(Vec3 color);
	void resetParticleColorVelocity(Vec3 col_vel);
	void resetParticleLifeMin(float life);
	void resetParticleLifeMax(float life);
	void resetParticleLife_Velocity(float life_v);
	void setParticleType(eParticleType _type);

	Vec3 getParticleAccelerationMin(){ return m_sParticleData.m_Acceleration_Min; };
	Vec3 getParticleAccelerationMax(){ return m_sParticleData.m_Acceleration_Max; };
	Vec3 getParticleSizeMin(){ return m_sParticleData.m_Size_Min; };
	Vec3 getParticleSizeMax(){ return m_sParticleData.m_Size_Max; };
	Vec3 getParticleSizeVelocity(){ return m_sParticleData.m_Size_Velocity; };
	Vec3 getParticleVelocityMin(){ return m_sParticleData.m_Velocity_Min; };
	Vec3 getParticleVelocityMax(){ return m_sParticleData.m_Velocity_Max; };
	Vec3 getParticleColorMin(){ return m_sParticleData.m_Color_Min; };
	Vec3 getParticleColorMax(){ return m_sParticleData.m_Color_Max; };
	Vec3 getParticleColorVelocity(){ return m_sParticleData.m_Color_Velocity; };
	float getParticleLifeMin(){ return m_sParticleData.m_Life_Min; };
	float getParticleLifeMax(){ return m_sParticleData.m_Life_Max; };
	float getParticleLife_Velocity(){ return m_sParticleData.m_Life_Velocity; };
	int getParticleCount(){ return m_createSize; };
	st3DParticleData getParticleData(){ return m_sParticleData; };
	eParticleType getParticleType(){ return m_eParticleType; };
private:
	void InitParticle(st3DParticle& vParticle);
	void BuildVBIB();
protected:
	//��������
	st3DParticleData m_sParticleData;
	std::vector<st3DParticle> m_3DParticleVec;
	//��ʼʱ��
	timeval m_StartTime;
	timeval m_PreTime;
	double sumTime;
	//��һ�γ���
	bool m_bFirstRender;
	eParticleType m_eParticleType;
	float updateTime;
	int m_createSize;
	double randomVelocity;
};

