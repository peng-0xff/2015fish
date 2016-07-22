/**
*  @Name:          ��ˮ�л����˿�����ɫ��ƽ̨
*  @Description:   ��Ȩ���У���Ȩʹ��
*  @Version:       1.2.0.0
*  @Copyright:     ����ˮ�л���������
*  @Author:        ZhangX,XiongML
*  @Date:          14-04-04 16:55
*/

#ifndef STRATEGY_ALL
#define STRATEGY_ALL

#pragma once

#include <string>
#include "../Header/struct.h"
#include "../Header/ExternRobot.h"
#include "../Header/Fishinfo.h"
#include "../Header/Ballinfo.h"
#include "cv.h"

#define _PKU_NEW_STRATEGY_VERSION_ 

#ifdef MURSTRATEGY_EXPORTS
#define STRATEGY_API extern "C" __declspec(dllexport)                    /**��ֹ�޸�*/
#else
#define STRATEGY_API __declspec(dllimport)
#endif

STRATEGY_API BOOL MURStrategy(IplImage* imgOrig, IplImage* imgRecog, CFishAction action[], int n_action, CFishInfo fishInfo[], int n_fishInfo,
	CBallInfo ballinfo[], int n_ballinfo, OBSTAINFO obst[], int n_obst, CHANNEL channel[], int n_channel);
/************************************************************************/
/**
*  ��������Կ����㷨��
*/
/************************************************************************/
class CStrategy
{
public:
	CStrategy(void);
	~CStrategy(void);

public:

public:
	BOOL StrategyPtr(BOOL(*ptFunc)(IplImage*, IplImage*, CFishAction*, int, CFishInfo*, int,
		CBallInfo*, int, OBSTAINFO*, int, CHANNEL*, int));                                                 /**����ָ��:ָ�������ͬ������һ�ز��Կ��ƺ���*/
	BOOL Strategy(IplImage* imgOrig = NULL, IplImage* imgRecog = NULL, CFishAction action[] = NULL, int n_action = 0, CFishInfo fishinfo[] = NULL, int n_fishinfo = 0,
		CBallInfo ballinfo[] = NULL, int n_ballinfo = 0, OBSTAINFO obst[] = NULL, int n_obst = 0, CHANNEL channel[] = NULL, int n_channel = 0);      /**���Կ����㷨*/

	BOOL Strategy0(CFishAction m_action[], CFishInfo m_FishInfo[], CBallInfo  &m_goalinfo, OBSTAINFO m_obst[], CHANNEL m_Channel[]);
	BOOL Strategy7(CFishAction m_action[], CFishInfo m_FishInfo[], CBallInfo  &m_goalinfo, OBSTAINFO m_obst[], CHANNEL m_Channel[]);
	BOOL Strategy16(CFishAction m_action[], CFishInfo m_FishInfo[], CBallInfo  &m_goalinfo, OBSTAINFO m_obst[], CHANNEL m_Channel[]);
	BOOL Strategy1(CFishAction m_action[], CFishInfo m_FishInfo[], CBallInfo  &m_goalinfo, OBSTAINFO m_obst[], CHANNEL m_Channel[]);

	int m_TurnYuan;
	int m_StatePeriod;

	void BasicActionStop(CFishInfo fish[], CFishAction action[], int id);//fish[]���������Ϣ��action[]������Ķ�����Ϣ��idҪ���Ƶ�������
	void BasicActionGo(CFishInfo fish[], CFishAction action[], int id, int speed, int direction, int mode);//fish[]���������Ϣ��action[]������Ķ�����Ϣ��idҪ���Ƶ������ţ�speed�ٶȵ���direction���򵵣�modeģ̬��0ͨ��ת��1ԭʼת��

protected:
	double Angle(CPoint pt, CPoint aimpt);
	double Distance(CPoint pt, CPoint aimpt);
	double Checkangle(double angle);
	void Roundp2p(CPoint aimpt, CFishAction &action, int fishID, CFishInfo m_FishInfo);
	void Point2point(CPoint aimpt, CFishAction &action, int fishID, CFishInfo m_FishInfo);
	void CStrategy::con2tempt(CPoint aimpt, CFishAction m_action[], CFishInfo m_FishInfo[]);
	void CStrategy::xiqiu(CPoint aimpt, CFishAction &action, int fishID, CFishInfo m_FishInfo);//�ж��Ƿ�������
	//BOOL CStrategy::pizza(CPoint fishpt, CPoint aimpt);
	BOOL CStrategy::ttong(CPoint fishpt, CPoint aimpt);
	void Roundp2p7(CPoint aimpt, CFishAction &action, int fishID, CFishInfo m_FishInfo)   //
	{
		CPoint FishPt;// �����ĵ�λ��
		double FishDir;// ��ͷ�ķ���
		CPoint FishHeadPt;//��ͷ��λ��
		CPoint LastFishPt;
		CPoint FishRotatePt;//���ת��λ��
		CPoint FishTailPt;//��β�͵�λ��		
		CPoint GoalPt1, GoalPt2;//��ʱĿ��㣬GoalPt2û���õ�
		CPoint Pt1, Pt2, Pt3, Pt4;
		CPoint f_headpt;//point of fish's head

		double dir1 = 0;
		double dir0;
		double dist0;
		double dist1 = 0;
		double dir2 = 0;
		double dist2 = 0;//��ʱ�õ��ķ���;���
		CPoint centerpt1, centerpt2;//��Ϊ��Ҫ�Ƶ���������	
		CPoint centerpt3, centerpt4, centerpt5, centerpt6;
		CPoint centerpt0, centerpt00;
		double dis1, dis2;
		dis1 = 0;
		dis2 = 0;
		double radius;///��Ҫ�ζ��İ뾶,�������������.
		FishPt = m_FishInfo.GetCenterPoint();
		f_headpt = m_FishInfo.GetHeaderPoint();
		FishDir = m_FishInfo.GetDirection();
		dist1 = Distance(FishPt, aimpt);      //����
		dir1 = Angle(f_headpt, aimpt);          //�Ƕ�   Ŀ������ͷ�ĽǶ�
		dir1 -= FishDir;
		dir1 = Checkangle(dir1) * 180 / PI;
		action.speed = 13;
		m_FishInfo.SetAction(action);
		if (dist1>100)
		{
			if (dir1>-5 && dir1<5)
			{
				action.mode = 0;
				action.direction = 7;
			}
			else if (dir1<-5 && dir1>-10)
			{
				action.mode = 0;
				action.direction = 6;
			}
			else if (dir1<-10 && dir1>-30)
			{
				action.mode = 0;
				action.direction = 5;
			}
			else if (dir1<-30 && dir1>-50)
			{
				action.mode = 0;
				action.direction = 4;
			}
			else if (dir1<-50 && dir1>-70)
			{
				action.mode = 0;
				action.direction = 2;
			}
			else if (dir1<-70 && dir1>-90)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-90)
			{
				action.mode = 1;
				action.direction = 0;
			}
			else if (dir1>5 && dir1<10)
			{
				action.mode = 0;
				action.direction = 8;
			}
			else if (dir1>10 && dir1<30)
			{
				action.mode = 0;
				action.direction = 9;
			}
			else if (dir1>30 && dir1<50)
			{
				action.mode = 0;
				action.direction = 10;
			}
			else if (dir1>50 && dir1<70)
			{
				action.mode = 0;
				action.direction = 11;
			}
			else if (dir1>70 && dir1<90)
			{
				action.mode = 0;
				action.direction = 14;
			}
			//			else if(dir1>80&&dir1<90)
			//			{
			//				action.mode=0;
			//				action.direction=14;
			//			}
			else
			{
				action.mode = 1;
				action.direction = 14;
			}
		}

		else
		{
			if (dir1>-5 && dir1<5)
			{
				action.mode = 0;
				action.direction = 7;
			}
			else if (dir1<-5 && dir1>-20)
			{
				action.mode = 0;
				action.direction = 4;
			}
			else if (dir1<-20 && dir1>-40)
			{
				action.mode = 0;
				action.direction = 1;
			}
			else if (dir1<-40 && dir1>-60)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-60 && dir1>-70)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-70 && dir1>-90)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-90 && dir1>-120)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-120)
			{
				action.mode = 1;
				action.direction = 0;
			}
			else if (dir1>5 && dir1<20)
			{
				action.mode = 0;
				action.direction = 10;
			}
			else if (dir1>20 && dir1<40)
			{
				action.mode = 0;
				action.direction = 13;
			}
			else if (dir1>40 && dir1<60)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1>60 && dir1<70)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1>70 && dir1<90)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1<120)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else
			{
				action.mode = 1;
				action.direction = 14;
			}
		}
		m_FishInfo.SetAction(action);
	}

	void CStrategy::other(CFishAction &action, int fishID, CFishInfo m_FishInfo)
	{
		CPoint FishPt;// �����ĵ�λ��
		double f_dir;// ��ͷ�ķ���
		CPoint FishHeadPt;//��ͷ��λ��
		CPoint LastFishPt;
		CPoint FishRotatePt;//���ת��λ��
		CPoint FishTailPt;//��β�͵�λ��		
		CPoint GoalPt1, GoalPt2;//��ʱĿ��㣬GoalPt2û���õ�
		CPoint Pt1, Pt2, Pt3, Pt4;
		//CPoint f_headpt;//point of fish's head
		//f_headpt=m_FishInfo[0].GetHeadPoint();

		double dir1 = 0;
		double dir0;
		double dist0;
		double dist1 = 0;
		double dir2 = 0;
		double dist2 = 0;//��ʱ�õ��ķ���;���
		CPoint centerpt1, centerpt2;//��Ϊ��Ҫ�Ƶ���������	
		CPoint centerpt3, centerpt4, centerpt5, centerpt6;
		CPoint centerpt0, centerpt00;
		double dis1, dis2;
		dis1 = 0;
		dis2 = 0;
		double radius;///��Ҫ�ζ��İ뾶,�������������.
		FishPt = m_FishInfo.GetCenterPoint();
		f_dir = m_FishInfo.GetDirection();
		//dist1 = Distance(FishPt, aimpt);
		//dir1 = Angle(FishPt, aimpt);
		dir1 -= f_dir;
		dir1 = Checkangle(dir1) * 180 / PI;
		action.speed = 15;
		m_FishInfo.SetAction(action);

	//	{
			//m_action[0].speed = 15;
			//if (f_dir > 2 / 3 * PI || f_dir < -2 / 3 * PI)
			//{
			//	m_action[0].mode = 1;
			//	m_action[0].direction = f_dir>0 ? 0 : 14;//0-6��ת��7�м�ֵ��8-14��ת
			//}
			//else
			//{
			//	m_action[0].mode = 0;                                                                                                                                                                                                                             
			//	m_action[0].direction = 7;
			//}
			//m_FishInfo[0].SetAction(m_action[0]);
			
			if (f_dir > 3 / 4 * PI || f_dir < -3 / 4 * PI)
			{
				action.mode = 1;
				action.direction = f_dir>0 ? 0 : 14;//0-6��ת��7�м�ֵ��8-14��ת
			}
			else if ((f_dir >-3 / 4 * PI && f_dir <  -1 / 4 * PI) || (f_dir >1 / 4 * PI && f_dir <  3 / 4 * PI))
			{
				if (FishPt.y < 50)
				{
					if ((f_dir >-3 / 4 * PI && f_dir < -1 / 4 * PI))
					{
						action.mode = 1;
						action.direction = 14;
					}
					else if ((f_dir >1 / 4 * PI && f_dir < 3 / 4 * PI))  //�ĸ�ֱ��
					{
						action.mode = 0;
						action.direction = 7;
					}
				}
				else if (FishPt.y>430)
				{
					if ((f_dir >-3 / 4 * PI && f_dir < -1 / 4 * PI))
					{
						action.mode = 0;
						action.direction = 7;
					}
					else if ((f_dir >1 / 4 * PI && f_dir < 3 / 4 * PI))
					{
						action.mode = 1;
						action.direction = 14;
					}
				}
				else
				{
					action.mode = 0;
					action.direction = 7;
				}
			}
			else
			{
				action.mode = 1;
				action.direction = f_dir<0 ? 0 : 14;
			}
			m_FishInfo.SetAction(action);
		//}
	}
	void Roundp2p2(bool ready, CPoint aimpt, CFishAction &action, int fishID, CFishInfo m_FishInfo, CBallInfo  &m_goalinfo, CHANNEL m_Channel[])//���������Ŀ��
	{





		CPoint FishPt;// �����ĵ�λ��
		double FishDir;// ��ͷ�ķ���
		CPoint FishHeadPt;//��ͷ��λ��
		CPoint LastFishPt;
		CPoint FishRotatePt;//���ת��λ��
		CPoint FishTailPt;//��β�͵�λ��		
		CPoint GoalPt1, GoalPt2;//��ʱĿ��㣬GoalPt2û���õ�
		CPoint Pt1, Pt2, Pt3, Pt4;
		CPoint f_headpt;//point of fish's head
		///////////////////////////xgm//////////////////////////////////
		double dir_fish2ball;//
		double dir_ball2goal;
		double reledir_fish2ball;
		double reledir_ball2goal;
		CPoint b_pt;//������ĵ�����
		b_pt = m_goalinfo.GetBallPoint();
		CPoint g_pt;//�������ĵ�����//distance
		g_pt = m_Channel[0].center;
		///////////////////////////////////////////////
		double dir1 = 0;
		double dir0;
		double dist0;
		double dist1 = 0;
		double dir2 = 0;
		double dist2 = 0;//��ʱ�õ��ķ���;���
		CPoint centerpt1, centerpt2;//��Ϊ��Ҫ�Ƶ���������	
		CPoint centerpt3, centerpt4, centerpt5, centerpt6;
		CPoint centerpt0, centerpt00;
		double dis1, dis2;
		dis1 = 0;
		dis2 = 0;
		double radius;///��Ҫ�ζ��İ뾶,�������������.



		FishPt = m_FishInfo.GetCenterPoint();
		f_headpt = m_FishInfo.GetHeaderPoint();
		FishDir = m_FishInfo.GetDirection();
		dist1 = Distance(FishPt, aimpt);
		dir1 = Angle(f_headpt, aimpt);
		dir1 -= FishDir;
		dir1 = Checkangle(dir1) * 180 / PI;
		action.speed = 15;
		m_FishInfo.SetAction(action);
		///////////////////xgm/////////////////////////
		dir_fish2ball = Angle(FishPt, b_pt);
		dir_ball2goal = Angle(b_pt, g_pt);

		reledir_fish2ball = dir_fish2ball - FishDir;
		reledir_fish2ball = Checkangle(reledir_fish2ball) * 180 / PI;

		reledir_ball2goal = dir_ball2goal - FishDir;
		reledir_ball2goal = Checkangle(reledir_ball2goal) * 180 / PI;
		////////////////////////////////////////////////
		if (dist1>100)
		{
			if (dir1>-5 && dir1<5)
			{
				action.mode = 0;
				action.direction = 7;
			}
			else if (dir1<-5 && dir1>-10)
			{
				action.mode = 0;
				action.direction = 5;
			}
			else if (dir1<-10 && dir1>-30)
			{
				action.mode = 0;
				action.direction = 4;
			}
			else if (dir1<-30 && dir1>-50)
			{
				action.mode = 0;
				action.direction = 2;
			}
			else if (dir1<-50 && dir1>-70)
			{
				action.mode = 0;
				action.direction = 1;
			}
			else if (dir1<-70 && dir1>-90)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-90)
			{
				action.mode = 1;
				action.direction = 0;
			}
			else if (dir1>5 && dir1<10)
			{
				action.mode = 0;
				action.direction = 9;
			}
			else if (dir1>10 && dir1<30)
			{
				action.mode = 0;
				action.direction = 10;
			}
			else if (dir1>30 && dir1<50)
			{
				action.mode = 0;
				action.direction = 12;
			}
			else if (dir1>50 && dir1<70)
			{
				action.mode = 0;
				action.direction = 13;
			}
			else if (dir1>70 && dir1<90)
			{
				action.mode = 0;
				action.direction = 14;
			}
			//			else if(dir1>80&&dir1<90)
			//			{
			//				action.mode=0;
			//				action.direction=14;
			//			}
			else
			{
				action.mode = 1;
				action.direction = 14;
			}
		}

		else if (dist1>39)

		{
			if (dir1>-5 && dir1<5)
			{
				action.mode = 0;
				action.direction = 7;
			}
			else if (dir1<-5 && dir1>-20)
			{
				action.mode = 0;
				action.direction = 4;
			}
			else if (dir1<-20 && dir1>-40)
			{
				action.mode = 0;
				action.direction = 1;
			}
			else if (dir1<-40 && dir1>-60)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-60 && dir1>-70)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-70 && dir1>-90)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-90 && dir1>-120)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-120)
			{
				action.mode = 1;
				action.direction = 0;
			}
			else if (dir1>5 && dir1<20)
			{
				action.mode = 0;
				action.direction = 10;
			}
			else if (dir1>20 && dir1<40)
			{
				action.mode = 0;
				action.direction = 13;
			}
			else if (dir1>40 && dir1<60)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1>60 && dir1<70)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1>70 && dir1<90)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1<120)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else
			{
				action.mode = 1;
				action.direction = 14;
			}
		}







		else if (ready == true)
		{
			if (reledir_fish2ball > 0 && reledir_fish2ball <= 90)

			{

				if (reledir_ball2goal > 0 && reledir_ball2goal <= 90)//ԭʼת�� 14��
				{
					action.mode = 1;
					action.direction = 14;
				}
				else if (reledir_ball2goal > -90 && reledir_ball2goal <= 0)//ԭʼת�� 0��
				{
					action.mode = 1;
					action.direction = 0;
				}
				else if (reledir_ball2goal > -180 && reledir_ball2goal <= -90)//ͨ��ת��  12��
				{
					action.mode = 0;
					action.direction = 12;
				}
				else if (reledir_ball2goal > 90 && reledir_ball2goal <= 180)//ֱ��
				{
					action.mode = 0;
					action.direction = 7;
				}
				else
				{

				}



			}



			else if (reledir_fish2ball>-90 && reledir_fish2ball <= 0)
			{




				if (reledir_ball2goal > 0 && reledir_ball2goal <= 90)//ԭʼת�� 14��
				{
					action.mode = 1;
					action.direction = 14;
				}
				else if (reledir_ball2goal > -90 && reledir_ball2goal <= 0)//ԭʼת�� 0��
				{
					action.mode = 1;
					action.direction = 0;
				}
				else if (reledir_ball2goal > -180 && reledir_ball2goal <= -90)//ͨ��ת��  12��
				{
					action.mode = 0;
					action.direction = 7;
				}
				else if (reledir_ball2goal > 90 && reledir_ball2goal <= 180)//ֱ��
				{
					action.mode = 0;
					action.direction = 2;
				}
				else
				{

				}

			}






			else if (reledir_fish2ball>-180 && reledir_fish2ball <= -90)
			{




				if (reledir_ball2goal > 0 && reledir_ball2goal <= 90)//ԭʼת�� 14��
				{
					action.mode = 0;
					action.direction = 12;
				}
				else if (reledir_ball2goal > -90 && reledir_ball2goal <= 0)//ԭʼת�� 0��
				{
					action.mode = 1;
					action.direction = 14;
				}
				else if (reledir_ball2goal > -180 && reledir_ball2goal <= -90)//ͨ��ת��  12��
				{
					action.mode = 1;
					action.direction = 0;
				}
				else if (reledir_ball2goal > 90 && reledir_ball2goal <= 180)//ֱ��
				{
					action.mode = 0;
					action.direction = 7;
				}
				else
				{

				}

			}





			else if (reledir_fish2ball>90 && reledir_fish2ball <= 180)
			{




				if (reledir_ball2goal > 0 && reledir_ball2goal <= 90)//ԭʼת�� 14��
				{
					action.mode = 0;
					action.direction = 0;
				}
				else if (reledir_ball2goal > -90 && reledir_ball2goal <= 0)//ԭʼת�� 0��
				{
					action.mode = 1;
					action.direction = 2;
				}
				else if (reledir_ball2goal > -180 && reledir_ball2goal <= -90)//ͨ��ת��  12��
				{
					action.mode = 0;
					action.direction = 7;
				}
				else if (reledir_ball2goal > 90 && reledir_ball2goal <= 180)//ֱ��
				{
					action.mode = 0;
					action.direction = 14;
				}
				else
				{

				}

			}

			else
			{

			}





		}



		m_FishInfo.SetAction(action);
	}

	void Roundp2p1(CPoint aimpt, CFishAction &action, int fishID, CFishInfo m_FishInfo)
	{
		CPoint FishPt;// �����ĵ�λ��
		double FishDir;// ��ͷ�ķ���
		CPoint FishHeadPt;//��ͷ��λ��
		CPoint LastFishPt;
		CPoint FishRotatePt;//���ת��λ��
		CPoint FishTailPt;//��β�͵�λ��		
		CPoint GoalPt1, GoalPt2;//��ʱĿ��㣬GoalPt2û���õ�
		CPoint Pt1, Pt2, Pt3, Pt4;
		CPoint f_headpt;//point of fish's head

		double dir1 = 0;
		double dir0;
		double dist0;
		double dist1 = 0;
		double dir2 = 0;
		double dist2 = 0;//��ʱ�õ��ķ���;���
		CPoint centerpt1, centerpt2;//��Ϊ��Ҫ�Ƶ���������	
		CPoint centerpt3, centerpt4, centerpt5, centerpt6;
		CPoint centerpt0, centerpt00;
		double dis1, dis2;
		dis1 = 0;
		dis2 = 0;
		double radius;///��Ҫ�ζ��İ뾶,�������������.
		FishPt = m_FishInfo.GetCenterPoint();
		f_headpt = m_FishInfo.GetHeaderPoint();
		FishDir = m_FishInfo.GetDirection();
		dist1 = Distance(FishPt, aimpt);
		dir1 = Angle(f_headpt, aimpt);
		dir1 -= FishDir;
		dir1 = Checkangle(dir1) * 180 / PI;
		action.speed = 15;
		m_FishInfo.SetAction(action);
		if (dist1>100)
		{
			if (dir1>-5 && dir1<5)
			{
				action.mode = 0;
				action.direction = 7;
			}
			else if (dir1<-5 && dir1>-10)
			{
				action.mode = 0;
				action.direction = 5;
			}
			else if (dir1<-10 && dir1>-30)
			{
				action.mode = 0;
				action.direction = 4;
			}
			else if (dir1<-30 && dir1>-50)
			{
				action.mode = 0;
				action.direction = 2;
			}
			else if (dir1<-50 && dir1>-70)
			{
				action.mode = 0;
				action.direction = 1;
			}
			else if (dir1<-70 && dir1>-90)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-90)
			{
				action.mode = 1;
				action.direction = 0;
			}
			else if (dir1>5 && dir1<10)
			{
				action.mode = 0;
				action.direction = 9;
			}
			else if (dir1>10 && dir1<30)
			{
				action.mode = 0;
				action.direction = 10;
			}
			else if (dir1>30 && dir1<50)
			{
				action.mode = 0;
				action.direction = 12;
			}
			else if (dir1>50 && dir1<70)
			{
				action.mode = 0;
				action.direction = 13;
			}
			else if (dir1>70 && dir1<90)
			{
				action.mode = 0;
				action.direction = 14;
			}
			//			else if(dir1>80&&dir1<90)
			//			{
			//				action.mode=0;
			//				action.direction=14;
			//			}
			else
			{
				action.mode = 1;
				action.direction = 14;
			}
		}

		else
		{
			if (dir1>-5 && dir1<5)
			{
				action.mode = 0;
				action.direction = 7;
			}
			else if (dir1<-5 && dir1>-20)
			{
				action.mode = 0;
				action.direction = 4;
			}
			else if (dir1<-20 && dir1>-40)
			{
				action.mode = 0;
				action.direction = 1;
			}
			else if (dir1<-40 && dir1>-60)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-60 && dir1>-70)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-70 && dir1>-90)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-90 && dir1>-120)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-120)
			{
				action.mode = 1;
				action.direction = 0;
			}
			else if (dir1>5 && dir1<20)
			{
				action.mode = 0;
				action.direction = 10;
			}
			else if (dir1>20 && dir1<40)
			{
				action.mode = 0;
				action.direction = 13;
			}
			else if (dir1>40 && dir1<60)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1>60 && dir1<70)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1>70 && dir1<90)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1<120)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else
			{
				action.mode = 1;
				action.direction = 14;
			}
		}
		m_FishInfo.SetAction(action);
	}
	void Roundp2p0(CPoint aimpt, CFishAction &action, int fishID, CFishInfo m_FishInfo)
	{
		CPoint FishPt;// �����ĵ�λ��
		double FishDir;// ��ͷ�ķ���
		CPoint FishHeadPt;//��ͷ��λ��
		CPoint LastFishPt;
		CPoint FishRotatePt;//���ת��λ��
		CPoint FishTailPt;//��β�͵�λ��		
		CPoint GoalPt1, GoalPt2;//��ʱĿ��㣬GoalPt2û���õ�
		CPoint Pt1, Pt2, Pt3, Pt4;
		CPoint f_headpt;//point of fish's head

		double dir1 = 0;
		double dir0;
		double dist0;
		double dist1 = 0;
		double dir2 = 0;
		double dist2 = 0;//��ʱ�õ��ķ���;���
		CPoint centerpt1, centerpt2;//��Ϊ��Ҫ�Ƶ���������	
		CPoint centerpt3, centerpt4, centerpt5, centerpt6;
		CPoint centerpt0, centerpt00;
		double dis1, dis2;
		dis1 = 0;
		dis2 = 0;
		double radius;///��Ҫ�ζ��İ뾶,�������������.
		FishPt = m_FishInfo.GetCenterPoint();
		f_headpt = m_FishInfo.GetHeaderPoint();
		FishDir = m_FishInfo.GetDirection();
		dist1 = Distance(FishPt, aimpt);
		dir1 = Angle(f_headpt, aimpt);
		dir1 -= FishDir;
		dir1 = Checkangle(dir1) * 180 / PI;
		action.speed = 10;
		m_FishInfo.SetAction(action);
		if (dist1>100)
		{
			if (dir1>-5 && dir1<5)
			{
				action.mode = 0;
				action.direction = 7;
			}
			else if (dir1<-5 && dir1>-10)
			{
				action.mode = 0;
				action.direction = 5;
			}
			else if (dir1<-10 && dir1>-30)
			{
				action.mode = 0;
				action.direction = 4;
			}
			else if (dir1<-30 && dir1>-50)
			{
				action.mode = 0;
				action.direction = 2;
			}
			else if (dir1<-50 && dir1>-70)
			{
				action.mode = 0;
				action.direction = 1;
			}
			else if (dir1<-70 && dir1>-90)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-90)
			{
				action.mode = 1;
				action.direction = 0;
			}
			else if (dir1>5 && dir1<10)
			{
				action.mode = 0;
				action.direction = 9;
			}
			else if (dir1>10 && dir1<30)
			{
				action.mode = 0;
				action.direction = 10;
			}
			else if (dir1>30 && dir1<50)
			{
				action.mode = 0;
				action.direction = 12;
			}
			else if (dir1>50 && dir1<70)
			{
				action.mode = 0;
				action.direction = 13;
			}
			else if (dir1>70 && dir1<90)
			{
				action.mode = 0;
				action.direction = 14;
			}
			//			else if(dir1>80&&dir1<90)
			//			{
			//				action.mode=0;
			//				action.direction=14;
			//			}
			else
			{
				action.mode = 1;
				action.direction = 14;
			}
		}

		else
		{
			if (dir1>-5 && dir1<5)
			{
				action.mode = 0;
				action.direction = 7;
			}
			else if (dir1<-5 && dir1>-20)
			{
				action.mode = 0;
				action.direction = 4;
			}
			else if (dir1<-20 && dir1>-40)
			{
				action.mode = 0;
				action.direction = 1;
			}
			else if (dir1<-40 && dir1>-60)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-60 && dir1>-70)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-70 && dir1>-90)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-90 && dir1>-120)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-120)
			{
				action.mode = 1;
				action.direction = 0;
			}
			else if (dir1>5 && dir1<20)
			{
				action.mode = 0;
				action.direction = 10;
			}
			else if (dir1>20 && dir1<40)
			{
				action.mode = 0;
				action.direction = 13;
			}
			else if (dir1>40 && dir1<60)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1>60 && dir1<70)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1>70 && dir1<90)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1<120)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else
			{
				action.mode = 1;
				action.direction = 14;
			}
		}
		m_FishInfo.SetAction(action);
	}

	void Roundp2p3(bool ready, CPoint aimpt, CFishAction &action, int fishID, CFishInfo m_FishInfo, CBallInfo  &m_goalinfo, CHANNEL m_Channel[])
	{
		CPoint FishPt;// �����ĵ�λ��
		double FishDir;// ��ͷ�ķ���
		CPoint FishHeadPt;//��ͷ��λ��
		CPoint LastFishPt;
		CPoint FishRotatePt;//���ת��λ��
		CPoint FishTailPt;//��β�͵�λ��		
		CPoint GoalPt1, GoalPt2;//��ʱĿ��㣬GoalPt2û���õ�
		CPoint Pt1, Pt2, Pt3, Pt4;
		CPoint f_headpt;//point of fish's head

		double dir1 = 0;
		double dir0;
		double dist0;
		double dist1 = 0;
		double dir2 = 0;
		double dist2 = 0;//��ʱ�õ��ķ���;���
		CPoint centerpt1, centerpt2;//��Ϊ��Ҫ�Ƶ���������	
		CPoint centerpt3, centerpt4, centerpt5, centerpt6;
		CPoint centerpt0, centerpt00;
		double dis1, dis2;
		dis1 = 0;
		dis2 = 0;
		double radius;///��Ҫ�ζ��İ뾶,�������������.
		FishPt = m_FishInfo.GetCenterPoint();
		f_headpt = m_FishInfo.GetHeaderPoint();
		FishDir = m_FishInfo.GetDirection();
		dist1 = Distance(FishPt, aimpt);
		dir1 = Angle(f_headpt, aimpt);
		dir1 -= FishDir;
		dir1 = Checkangle(dir1) * 180 / PI;
		action.speed = 14;//13gaicheng14
		m_FishInfo.SetAction(action);

		///////////////////////////xgm//////////////////////////////////
		double dir_fish2ball;//
		double dir_ball2goal;
		double reledir_fish2ball;
		double reledir_ball2goal;
		CPoint b_pt;//������ĵ�����
		b_pt = m_goalinfo.GetBallPoint();
		CPoint g_pt;//�������ĵ�����//distance
		g_pt = m_Channel[0].center;
		///////////////////////////////////////////////

		///////////////////xgm/////////////////////////
		dir_fish2ball = Angle(FishPt, b_pt);
		dir_ball2goal = Angle(b_pt, g_pt);

		reledir_fish2ball = dir_fish2ball - FishDir;
		reledir_fish2ball = Checkangle(reledir_fish2ball) * 180 / PI;

		reledir_ball2goal = dir_ball2goal - FishDir;
		reledir_ball2goal = Checkangle(reledir_ball2goal) * 180 / PI;
		////////////////////////////////////////////////

		if ((ready == true) && dist1<40 && ((reledir_fish2ball > 0 && reledir_fish2ball <= 90) || (reledir_fish2ball>-90 && reledir_fish2ball <= 0)))
		{
			//			MessageBox(0,TEXT("dd"),TEXT("sdf"),0);
			if (reledir_fish2ball>-90 && reledir_fish2ball <= 0)
			{

				if (reledir_ball2goal > 0 && reledir_ball2goal <= 90)//ԭʼת�� 14��
				{
					action.mode = 1;
					action.direction = 14;
				}
				else if (reledir_ball2goal > -90 && reledir_ball2goal <= 0)//ԭʼת�� 0��
				{
					action.mode = 1;
					action.direction = 0;
				}
				//else if (reledir_ball2goal > -180 && reledir_ball2goal <= -90)//ͨ��ת��  12��
				//{
				//	action.mode = 0;
				//	action.direction = 7;
				//}
				//else if (reledir_ball2goal > 90 && reledir_ball2goal <= 180)//ֱ��
				//{
				//	action.mode = 0;
				//	action.direction = 2;
				//}
				else
				{

				}

			}
			else if (reledir_fish2ball > 0 && reledir_fish2ball <= 90)
			{

				if (reledir_ball2goal > 0 && reledir_ball2goal <= 90)//ԭʼת�� 14��
				{
					action.mode = 1;
					action.direction = 14;
				}
				else if (reledir_ball2goal > -90 && reledir_ball2goal <= 0)//ԭʼת�� 0��
				{
					action.mode = 1;
					action.direction = 0;
				}
				//else if (reledir_ball2goal > -180 && reledir_ball2goal <= -90)//ͨ��ת��  12��
				//{
				//	action.mode = 0;
				//	action.direction = 12;
				//}
				//else if (reledir_ball2goal > 90 && reledir_ball2goal <= 180)//ֱ��
				//{
				//	action.mode = 0;
				//	action.direction = 7;
				//}
				else
				{

				}

			}
			else
			{

			}
		}
		else
		{
			if (dist1>100)
			{
				action.speed = 15;
				if (dir1>-5 && dir1<5)
				{
					action.mode = 0;
					action.direction = 7;
				}
				else if (dir1<-5 && dir1>-10)
				{
					action.mode = 0;
					action.direction = 5;
				}
				else if (dir1<-10 && dir1>-30)
				{
					action.mode = 0;
					action.direction = 4;
				}
				else if (dir1<-30 && dir1>-50)
				{
					action.mode = 0;
					action.direction = 2;
				}
				else if (dir1<-50 && dir1>-70)
				{
					action.mode = 0;
					action.direction = 1;
				}
				else if (dir1<-70 && dir1>-90)
				{
					action.mode = 0;
					action.direction = 0;
				}
				else if (dir1<-90)
				{
					action.mode = 0; //�ĳ�0��
					action.direction = 0;
				}
				else if (dir1>5 && dir1<10)
				{
					action.mode = 0;
					action.direction = 9;
				}
				else if (dir1>10 && dir1<30)
				{
					action.mode = 0;
					action.direction = 10;
				}
				else if (dir1>30 && dir1<50)
				{
					action.mode = 0;
					action.direction = 12;
				}
				else if (dir1>50 && dir1<70)
				{
					action.mode = 0;
					action.direction = 13;
				}
				else if (dir1>70 && dir1<90)
				{
					action.mode = 0;
					action.direction = 14;
				}
				//			else if(dir1>80&&dir1<90)
				//			{
				//				action.mode=0;
				//				action.direction=14;
				//			}
				else
				{
					action.mode = 1;
					action.direction = 14;
				}
			}

			else
			{
				if (dir1>-5 && dir1<5)
				{
					action.mode = 0;
					action.direction = 7;
				}
				else if (dir1<-5 && dir1>-20)
				{
					action.mode = 0;
					action.direction = 4;
				}
				else if (dir1<-20 && dir1>-40)
				{
					action.mode = 0;
					action.direction = 1;
				}
				else if (dir1<-40 && dir1>-60)
				{
					action.mode = 0;
					action.direction = 0;
				}
				else if (dir1<-60 && dir1>-70)
				{
					action.mode = 0;
					action.direction = 0;
				}
				else if (dir1<-70 && dir1>-90)
				{
					action.mode = 0;
					action.direction = 0;
				}
				else if (dir1<-90 && dir1>-120)
				{
					action.mode = 0;
					action.direction = 0;
				}
				else if (dir1<-120)
				{
					action.mode = 1;
					action.direction = 0;
				}
				else if (dir1>5 && dir1<20)
				{
					action.mode = 0;
					action.direction = 10;
				}
				else if (dir1>20 && dir1<40)
				{
					action.mode = 0;
					action.direction = 13;
				}
				else if (dir1>40 && dir1<60)
				{
					action.mode = 0;
					action.direction = 14;
				}
				else if (dir1>60 && dir1<70)
				{
					action.mode = 0;
					action.direction = 14;
				}
				else if (dir1>70 && dir1<90)
				{
					action.mode = 0;
					action.direction = 14;
				}
				else if (dir1<120)
				{
					action.mode = 0;
					action.direction = 14;
				}
				else
				{
					action.mode = 1;
					action.direction = 14;
				}
			}
		}
		m_FishInfo.SetAction(action);
	}
	//��������
	void PushBallToLeft(CPoint aimpt, CPoint g_pt, CBallInfo  &m_goalinfo, CFishAction m_action[], CFishInfo m_FishInfo[], CHANNEL m_Channel[])
	{
		//ͼ�����Ϊ768*576���е�Ϊ384*288
		CPoint f_pt;//������ĵ�����
		f_pt = m_FishInfo[0].GetCenterPoint();
		double f_dir;//��ķ���[-PI,PI]
		f_dir = m_FishInfo[0].GetDirection();
		CPoint f_headpt;//��ͷ������
		f_headpt = m_FishInfo[0].GetHeaderPoint();

		CPoint b_pt;//������ĵ�����
		b_pt = m_goalinfo.GetBallPoint();

		CPoint tempt;//�������ʱ����������ߣ���Ҫ��������ұߵ���ʱ��

		double dirfishtoball;
		dirfishtoball = Angle(f_pt, b_pt);
		double disfishtoball;
		disfishtoball = Distance(f_pt, b_pt);
		double dirballtogoal;
		dirballtogoal = Angle(b_pt, g_pt);

		dirfishtoball -= f_dir;
		dirfishtoball = Checkangle(dirfishtoball);
		dirfishtoball = dirfishtoball * 180 / PI;

		double r = 14.0;

		bool ready;
		tempt.x = b_pt.x - (r + 200)*cos(dirballtogoal);//������������������,��Ҫ��������ұߵ���ʱ��
		tempt.y = b_pt.y - (r + 200)*sin(dirballtogoal);//������������������,��Ҫ��������ұߵ���ʱ��
		//�����ԣ������ҷ������ʱ����ʱĿ��㶼Ϊ���ţ��������tempt0��tempt1�����ã���ʱ���ҽ���ʱ��ԼΪ1min,�������ʱ��ԼΪ3min

		if (f_headpt.x>b_pt.x)//16gaicheng3
		{
			ready = true;
		}
		else
		{
			ready = false;
		}
		if (f_headpt.x>b_pt.x)//�������ұߣ���ζ�������ֱ�Ӷ���
		{

			if (disfishtoball<60)
			{
				m_action[0].mode = 0;
				m_action[0].speed = 12;
			}
			else
			{
				m_action[0].mode = 0;
				m_action[0].speed = 15;
			}
			//Roundp2p(aimpt, m_action[0], 0, m_FishInfo[0]);//gaichengqitadiaoyonghanshu
			Roundp2p3(ready, aimpt, m_action[0], 0, m_FishInfo[0], m_goalinfo, m_Channel);
		}

		else//��������ߣ���ζ����������Ƶ�����ұ߲���ֱ�Ӷ���
		{
			if ((f_pt.y>50) && (f_pt.y<510))
			{
				if (disfishtoball>150)//�ж�������ľ��룬����������150������temptΪ��ʱĿ��㡣
				{
					m_action[0].speed = 15;
					Roundp2p(tempt, m_action[0], 0, m_FishInfo[0]);
				}

				if ((disfishtoball>60) && (disfishtoball<150)) //�ж�������ľ��룬�������С��150������60������ϰ汾1VS1���ҽ������ԡ�
				{
					if (f_pt.y<b_pt.y - r)//����������
					{
						m_action[0].speed = 15;
						if (f_dir<PI / 6 && f_dir>-PI / 6)
						{
							m_action[0].mode = 0;
							m_action[0].direction = 7;
						}
						else if (f_dir>PI / 2 && f_dir<-PI / 3)
						{
							m_action[0].mode = 1;
							m_action[0].direction = 13;
						}
						else
						{
							m_action[0].mode = 0;
							m_action[0].direction = f_dir<0 ? 11 : 13;///�Ķ�(�������ϲ��ԣ��ӹ�����Ч����)
						}
					}
					else if (f_pt.y>b_pt.y + r)//����������
					{
						m_action[0].speed = 15;
						if (f_dir<PI / 6 && f_dir>-PI / 6)
						{
							m_action[0].mode = 0;
							m_action[0].direction = 7;
						}
						else if (f_dir<-PI / 2 && f_dir>1 / 3 * PI)
						{
							m_action[0].mode = 1;
							m_action[0].direction = 1;
						}
						else
						{
							m_action[0].mode = 0;
							m_action[0].direction = f_dir<0 ? 1 : 2;///�Ķ����������ϲ��ԣ��ӹ�����Ч���ã�
						}

					}
					else//fish is in the same y-axis line with the ball
					{
						m_action[0].speed = 15;
						if (f_dir<PI / 3 && f_dir>-PI / 3)
						{
							m_action[0].mode = 1;
							m_action[0].direction = f_dir<0 ? 1 : 13;
						}
						else
						{
							m_action[0].mode = 0;
							m_action[0].direction = 7;
						}
					}
				}

				if (disfishtoball<60)  //��������β˦β����
				{
					if ((f_dir>PI / 2) && (f_dir<PI))	 //˦��λ��
					{
						if (f_pt.y>b_pt.y)
						{
							m_action[0].speed = 15;
							m_action[0].direction = 0;
							m_action[0].mode = 1;
						}
						else
						{
							m_action[0].speed = 15;
							m_action[0].direction = 14;
							m_action[0].mode = 1;
						}
					}
					if ((f_dir>(-PI)) && (f_dir<(-PI / 2)))	 //˦��λ��
					{
						if (f_pt.y>b_pt.y)
						{
							m_action[0].speed = 15;
							m_action[0].direction = 0;
							m_action[0].mode = 1;
						}
						else
						{
							m_action[0].speed = 15;
							m_action[0].direction = 14;
							m_action[0].mode = 1;
						}

					}
					if ((f_dir>0) && (f_dir<PI / 2))	 //��˦��λ��
					{
						if (f_pt.y>b_pt.y)
						{
							m_action[0].speed = 15;
							m_action[0].direction = 3;
							m_action[0].mode = 0;
						}
						else
						{
							m_action[0].speed = 15;
							m_action[0].direction = 7;
							m_action[0].mode = 0;
						}
					}

					if ((f_dir<(-PI / 2)) && (f_dir>-PI))	 //��˦��λ��
					{
						if (f_pt.y>b_pt.y)
						{
							m_action[0].speed = 15;
							m_action[0].direction = 7;
							m_action[0].mode = 0;
						}
						else
						{
							m_action[0].speed = 15;
							m_action[0].direction = 11;
							m_action[0].mode = 0;
						}

					}
				}
			}
			if (f_pt.y<50)
			{
				if ((f_dir<5 * PI / 6) && f_dir>0)
				{
					m_action[0].direction = 7;
					m_action[0].speed = 15;
				}
				if ((f_dir>5 * PI / 6) || (f_dir<-PI / 2))
				{
					m_action[0].direction = 3;
					m_action[0].speed = 15;
				}
				if (f_dir>-PI / 2 && f_dir<0)
				{
					m_action[0].direction = 11;
					m_action[0].speed = 15;
				}
			}
			if (f_pt.y>510)
			{
				if ((f_dir>-2 * PI / 3) && f_dir<0)
				{
					m_action[0].direction = 7;
					m_action[0].speed = 15;
				}
				if ((f_dir>PI / 2) || (f_dir<-2 * PI / 3))
				{
					m_action[0].direction = 11;
					m_action[0].speed = 15;
				}
				if (f_dir>0 && f_dir<PI / 2)
				{
					m_action[0].direction = 3;
					m_action[0].speed = 15;
				}
			}
		}



	}


	//���Ҷ�����
	void PushBallToRight(CPoint aimpt, CPoint g_pt, CBallInfo  &m_goalinfo, CFishAction m_action[], CFishInfo m_FishInfo[], CHANNEL m_Channel[])
	{
		//ͼ�����Ϊ768*576���е�Ϊ384*288
		CPoint f_pt;//������ĵ�����
		f_pt = m_FishInfo[0].GetCenterPoint();
		double f_dir;//��ķ���[-PI,PI]
		f_dir = m_FishInfo[0].GetDirection();
		CPoint f_headpt;//��ͷ������
		f_headpt = m_FishInfo[0].GetHeaderPoint();

		CPoint b_pt;//������ĵ�����
		b_pt = m_goalinfo.GetBallPoint();

		//CPoint g_pt;//���ŵ����ĵ�����
		//g_pt=m_Channel[0].center;

		// CPoint aimpt;

		CPoint tempt;//���ҽ���ʱ���������ұߣ���Ҫ���������ߵ���ʱ��

		double dirfishtoball;
		dirfishtoball = Angle(f_pt, b_pt);
		double disfishtoball;
		disfishtoball = Distance(f_pt, b_pt);
		double dirballtogoal;
		dirballtogoal = Angle(b_pt, g_pt);

		dirfishtoball -= f_dir;
		dirfishtoball = Checkangle(dirfishtoball);
		dirfishtoball = dirfishtoball * 180 / PI;
		
		bool ready;

		double r = 14.0;

		tempt.x = b_pt.x - (r + 200)*cos(dirballtogoal);//���ҽ������������ұ�,��Ҫ���������ߵ���ʱ��
		tempt.y = b_pt.y - (r + 200)*sin(dirballtogoal);//���ҽ������������ұ�,��Ҫ���������ߵ���ʱ��

		//�����ԣ������ҷ������ʱ����ʱĿ��㶼Ϊ���ţ��������tempt0��tempt1�����ã���ʱ���ҽ���ʱ��ԼΪ1min,�������ʱ��ԼΪ3min
		if (f_headpt.x<b_pt.x)  //16gaicheng3
		{
			ready = true;
		}
		else
		{
			ready = false;
		}
		if (f_headpt.x<b_pt.x)//��������ߣ���ζ�������ֱ�Ӷ���
		{

			if (disfishtoball<60)
			{
				m_action[0].mode = 0;
				m_action[0].speed = 12;
			}
			else
			{
				m_action[0].mode = 0;
				m_action[0].speed = 15;
			}
			//Roundp2p(aimpt, m_action[0], 0, m_FishInfo[0]);//gaichengliyigetiaoyonghanhu
			Roundp2p3(ready, aimpt, m_action[0], 0, m_FishInfo[0], m_goalinfo, m_Channel);

		}

		else//�������ұߣ���ζ����������Ƶ������߲���ֱ�Ӷ���
		{
			if ((f_pt.y>50) && (f_pt.y<510))
			{
				if (disfishtoball>150)//�ж�������ľ��룬����������150������tempt1Ϊ��ʱĿ��㡣
				{
					m_action[0].speed = 15;
					Roundp2p(tempt, m_action[0], 0, m_FishInfo[0]);
				}
				if ((disfishtoball<150) && (disfishtoball>60)) //�ж�������ľ��룬�������С��150������60��������ϰ汾���ҽ������ԡ�   
				{
					if (f_pt.y<b_pt.y - r)//����������
					{
						m_action[0].speed = 15;
						if (f_dir>5 / 6 * PI&&f_dir<-5 / 6 * PI)
						{
							m_action[0].mode = 0;
							m_action[0].direction = 7;
						}
						else if (f_dir>-2 / 3 * PI&&f_dir<PI / 2)
						{
							m_action[0].mode = 1;//������ת��
							m_action[0].direction = 1;
						}
						else
						{
							m_action[0].mode = 0;
							m_action[0].direction = f_dir<0 ? 3 : 11;
						}
						m_FishInfo[0].SetAction(m_action[0]);

					}
					else if (f_pt.y>b_pt.y + r)//����������
					{
						m_action[0].speed = 15;
						if (f_dir>5 / 6 * PI&&f_dir<-5 / 6 * PI)
						{
							m_action[0].mode = 0;
							m_action[0].direction = 7;
						}
						else if (f_dir>-PI / 2 && f_dir<2 / 3 * PI)
						{
							m_action[0].mode = 1;//����ת��
							m_action[0].direction = 13;//����ת
						}
						else
						{
							m_action[0].mode = 0;//ǰ��ת��
							m_action[0].direction = f_dir<0 ? 3 : 11;
						}
						m_FishInfo[0].SetAction(m_action[0]);

					}
					else//fish is in the same y-axis line with the ball (��������Y��ͬ�ࣩ
					{
						m_action[0].speed = 15;
						if (f_dir>2 / 3 * PI&&f_dir<-2 / 3 * PI)//
						{
							m_action[0].mode = 1;
							m_action[0].direction = f_dir>0 ? 1 : 13;//0-6��ת��7�м�ֵ��8-14��ת
						}
						else
						{
							m_action[0].mode = 0;
							m_action[0].direction = 7;
						}
						m_FishInfo[0].SetAction(m_action[0]);
					}

				}
				if (disfishtoball<60)//������β˦��
				{
					if ((f_dir>0) && (f_dir<PI / 2))	 //˦��λ��
					{
						if (f_pt.y>b_pt.y)
						{
							m_action[0].speed = 15;
							m_action[0].direction = 14;
							m_action[0].mode = 1;
						}
						else
						{
							m_action[0].speed = 15;
							m_action[0].direction = 0;
							m_action[0].mode = 1;
						}
					}

					if ((f_dir<0) && (f_dir>(-PI / 2)))	 //˦��λ��
					{
						if (f_pt.y<b_pt.y)
						{
							m_action[0].speed = 15;
							m_action[0].direction = 0;
							m_action[0].mode = 1;
						}
						else
						{
							m_action[0].speed = 15;
							m_action[0].direction = 14;
							m_action[0].mode = 1;
						}
					}

					if ((f_dir>PI / 2) && (f_dir<PI))	 //��˦��λ��
					{
						if (f_pt.y>b_pt.y)
						{
							m_action[0].speed = 15;
							m_action[0].direction = 9;
							m_action[0].mode = 0;
						}
						else
						{
							m_action[0].speed = 15;
							m_action[0].direction = 7;
							m_action[0].mode = 0;
						}

					}
					if ((f_dir<(-PI / 2)) && (f_dir>(-PI)))	 //��˦��λ��
					{
						if (f_pt.y>b_pt.y)
						{
							m_action[0].speed = 15;
							m_action[0].direction = 7;
							m_action[0].mode = 0;
						}
						else
						{
							m_action[0].speed = 15;
							m_action[0].direction = 5;
							m_action[0].mode = 0;
						}
					}
				}
			}
			if (f_pt.y<50)
			{
				if (f_dir>PI / 6 && f_dir<PI)
				{
					m_action[0].direction = 7;
					m_action[0].speed = 15;
				}
				if (f_dir>-PI&&f_dir<-PI / 2)
				{
					m_action[0].direction = 3;
					m_action[0].speed = 15;
				}
				if (f_dir>-PI / 2 && f_dir<PI / 6)
				{
					m_action[0].direction = 11;
					m_action[0].speed = 15;
				}
			}
			if (f_pt.y>510)
			{
				if (f_dir>-PI&&f_dir<-PI / 6)
				{
					m_action[0].direction = 7;
					m_action[0].speed = 15;
				}
				if (f_dir>PI / 2 && f_dir<PI)
				{
					m_action[0].direction = 11;
					m_action[0].speed = 15;
				}
				if (f_dir>-PI / 6 && f_dir<PI / 2)
				{
					m_action[0].direction = 3;
					m_action[0].speed = 15;
				}
			}
		}

	}

	void tail(CPoint aimpt, CFishAction &action, int fishID, CFishInfo m_FishInfo)
	{
		CPoint FishPt;// �����ĵ�λ��
		double FishDir;// ��ͷ�ķ���
		CPoint FishHeadPt;//��ͷ��λ��
		CPoint LastFishPt;
		CPoint FishRotatePt;//���ת��λ��
		CPoint FishTailPt;//��β�͵�λ��		
		CPoint GoalPt1, GoalPt2;//��ʱĿ��㣬GoalPt2û���õ�
		CPoint Pt1, Pt2, Pt3, Pt4;
		CPoint f_headpt;//point of fish's head

		double dir1 = 0;
		double dir0;
		double dist0;
		double dist1 = 0;
		double dir2 = 0;
		double dist2 = 0;//��ʱ�õ��ķ���;���
		CPoint centerpt1, centerpt2;//��Ϊ��Ҫ�Ƶ���������	
		CPoint centerpt3, centerpt4, centerpt5, centerpt6;
		CPoint centerpt0, centerpt00;
		double dis1, dis2;
		dis1 = 0;
		dis2 = 0;
		double radius;///��Ҫ�ζ��İ뾶,�������������.
		FishPt = m_FishInfo.GetCenterPoint();
		f_headpt = m_FishInfo.GetHeaderPoint();
		FishDir = m_FishInfo.GetDirection();
		dist1 = Distance(FishPt, aimpt);
		dir1 = Angle(f_headpt, aimpt);
		dir1 -= FishDir;
		dir1 = Checkangle(dir1) * 180 / PI;
		action.speed = 13;
		m_FishInfo.SetAction(action);
		if (dist1>100)
		{
			if (dir1>-5 && dir1<5)
			{
				action.mode = 0;
				action.direction = 7;
			}
			else if (dir1<-5 && dir1>-10)
			{
				action.mode = 0;
				action.direction = 5;
			}
			else if (dir1<-10 && dir1>-30)
			{
				action.mode = 0;
				action.direction = 4;
			}
			else if (dir1<-30 && dir1>-50)
			{
				action.mode = 0;
				action.direction = 2;
			}
			else if (dir1<-50 && dir1>-70)
			{
				action.mode = 0;
				action.direction = 1;
			}
			else if (dir1<-70 && dir1>-90)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-90)
			{
				action.mode = 1;
				action.direction = 0;
			}
			else if (dir1>5 && dir1<10)
			{
				action.mode = 0;
				action.direction = 9;
			}
			else if (dir1>10 && dir1<30)
			{
				action.mode = 0;
				action.direction = 10;
			}
			else if (dir1>30 && dir1<50)
			{
				action.mode = 0;
				action.direction = 12;
			}
			else if (dir1>50 && dir1<70)
			{
				action.mode = 0;
				action.direction = 13;
			}
			else if (dir1>70 && dir1<90)
			{
				action.mode = 0;
				action.direction = 14;
			}
			//			else if(dir1>80&&dir1<90)
			//			{
			//				action.mode=0;
			//				action.direction=14;
			//			}
			else
			{
				action.mode = 1;
				action.direction = 14;
			}
		}

		else
		{
			action.speed = sqrt(dist1);
			if (dir1>-5 && dir1<5)
			{
				action.mode = 0;
				action.direction = 7;
			}
			else if (dir1<-5 && dir1>-20)
			{
				action.mode = 0;
				action.direction = 4;
			}
			else if (dir1<-20 && dir1>-40)
			{
				action.mode = 0;
				action.direction = 1;
			}
			else if (dir1<-40 && dir1>-60)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-60 && dir1>-70)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-70 && dir1>-90)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-90 && dir1>-120)
			{
				action.mode = 0;
				action.direction = 0;
			}
			else if (dir1<-120)
			{
				action.mode = 1;
				action.direction = 0;
			}
			else if (dir1>5 && dir1<20)
			{
				action.mode = 0;
				action.direction = 10;
			}
			else if (dir1>20 && dir1<40)
			{
				action.mode = 0;
				action.direction = 13;
			}
			else if (dir1>40 && dir1<60)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1>60 && dir1<70)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1>70 && dir1<90)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else if (dir1<120)
			{
				action.mode = 0;
				action.direction = 14;
			}
			else
			{
				action.mode = 1;
				action.direction = 14;
			}
		}
		m_FishInfo.SetAction(action);
	}
};




#endif
