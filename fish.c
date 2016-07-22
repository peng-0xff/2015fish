BOOL CStrategy::Strategy0(CFishAction m_action[], CFishInfo m_FishInfo[], CBallInfo  &m_goalinfo, OBSTAINFO m_obst[], CHANNEL m_Channel[])
{
	CPoint f_pt = m_FishInfo[0].GetCenterPoint();
	CPoint f_headpt = m_FishInfo[0].GetHeaderPoint();
	double f_dir = m_FishInfo[0].GetDirection();
	CPoint b_pt = m_goalinfo.GetBallPoint();
	CPoint g_pt = m_Channel[0].center;
	double dirBallToGoal = Angle(b_pt, g_pt);
	double disBallToGoal = Distance(b_pt, g_pt);
	//CPoint e_pt = m_FishInfo[8].GetCenterPoint();
	
	
	double disfishtoaimpt;
	disfishtoaimpt = this->Distance(f_pt, b_pt);

	double width = m_Channel[0].width;
	bool ready;

	const int r = 3;//13改成3
	int l;
	if (b_pt.y <= 50 || b_pt.y >= 420)
	{
		l = 15;
	}
	else
	{
		l = 55;
	}

//	Roundp2p1(e_pt, m_action[1], 1, m_FishInfo[1]);           ////

	CPoint tempLeft, tempUp, tempDown, temp1, temp2, temp3;
	tempLeft.x = b_pt.x - l*cos(dirBallToGoal);
	tempLeft.y = b_pt.y - l*sin(dirBallToGoal);
	tempUp.x = b_pt.x;
	tempUp.y = b_pt.y - 60;    //TODO  考虑改大参数，惯性问题  25+16+buffer
	tempDown.x = b_pt.x;
	tempDown.y = b_pt.y + 60;
	temp1.x = b_pt.x - 0 * cos(dirBallToGoal);
	temp1.y = b_pt.y - 0 * sin(dirBallToGoal);
	temp2.x = b_pt.x - 45;
	temp2.y = f_pt.y;
	temp3.x = b_pt.x + 45;
	temp3.y = f_pt.y;

	
	static bool isRight, closeToGoal, closeToGoal1;
	if (g_pt.x>312)
	{
		isRight = true;
		if (f_headpt.x<b_pt.x -3)  //16gaicheng3
		{
			ready = true;
		}
		else
		{
			ready = false;
		}
		
	/*	if (disBallToGoal <= 100 || b_pt.y>430 || b_pt.y<50 || (b_pt.x>630 && (b_pt.y<(g_pt.y - width / 2 - 15) || b_pt.y>(g_pt.y + width / 2 + 15) ) ) )
		{
			closeToGoal = true;
		}
		else
		{
			closeToGoal = false;
		}*/
		if (disBallToGoal <= 125)
		{
			closeToGoal1 = true;
		}
		else
		{
			closeToGoal1 = false;
		}
		if ((b_pt.x>630 && (b_pt.y<(g_pt.y - width / 2 - 15) || b_pt.y>(g_pt.y + width / 2 + 15))))

		{
			closeToGoal = true;
		}
		else
		{
			closeToGoal = false;
		}


	}
	else
	{
		isRight = false;
		if (f_headpt.x>b_pt.x + 3)//16gaicheng3
		{
			ready = true;
		}
		else
		{
			ready = false;
		}
		//if ( disBallToGoal <= 100 ||b_pt.y>430 || b_pt.y<50 || (b_pt.x<120 && (b_pt.y<(g_pt.y - width / 2 - 15) || b_pt.y>(g_pt.y + width / 2 + 15))))        //去掉了 disBallToGoal <= 100 ||  这个条件
		//{
		//	closeToGoal = true;
		//}
		//else
		//{
		//	closeToGoal = false;
		//}
		if (disBallToGoal <= 125)
		{
			closeToGoal1 = true;
		}
		else
		{
			closeToGoal1 = false;
		}
		if ((b_pt.x<120 && (b_pt.y<(g_pt.y - width / 2 - 15) || b_pt.y>(g_pt.y + width / 2 + 15))))

			{
				closeToGoal = true;
			}
			else
			{
				closeToGoal = false;
			}


	}


	if (isRight == true)
	{
		if (f_headpt.x < b_pt.x - r)
		{
			//			Roundp2p2(ready,temp1, m_action[0], 0, m_FishInfo[0], m_goalinfo, m_Channel);
			//			Roundp2p1(tempLeft, m_action[0], 0, m_FishInfo[0]);
			if (closeToGoal == true)
			{
				Roundp2p1(tempLeft, m_action[0], 0, m_FishInfo[0]);
				//if (ttong(f_pt,b_pt))
				//{
				//	if (disfishtoaimpt <= 11)
				//	{
				//		m_action[0].speed = 13;
				//	
				//			m_action[0].mode = 1;
				//			m_action[0].direction = f_dir<0 ? 0 : 14;//0-6左转，7中间值，8-14右转
				//		
				//	}

				//}
			}
			else
			{
				if (closeToGoal1 == true)
				{
					PushBallToRight(temp1, g_pt, m_goalinfo, m_action, m_FishInfo, m_Channel);   //向右甩尾
				}
				///Roundp2p3(ready, temp1, m_action[0], 0, m_FishInfo[0], m_goalinfo, m_Channel);
				Roundp2p3(ready, temp1, m_action[0], 0, m_FishInfo[0], m_goalinfo, m_Channel);
				
			}
		}
		else
		{ 

			if (f_headpt.y<b_pt.y - r)  //鱼上球下
			{
				if (f_headpt.x<b_pt.x + 40)  //把35改成40
				{
					Roundp2p1(temp2, m_action[0], 0, m_FishInfo[0]);
					
				}
				else
				{
					Roundp2p1(tempUp, m_action[0], 0, m_FishInfo[0]); // 游到球上方
					
				}
			}
			else if (f_headpt.y>b_pt.y + r)   //鱼下球上
			{
				if (f_headpt.x<b_pt.x + 40)
				{
					Roundp2p1(temp2, m_action[0], 0, m_FishInfo[0]);
					
					
				}
				else
				{
					Roundp2p1(tempDown, m_action[0], 0, m_FishInfo[0]);
					
				}
			}
			else
			{

				//other(m_action[0], 0, m_FishInfo[0]);
				//m_action[0].speed = 15;
				//if (f_dir > 2 / 3 * PI || f_dir < -2 / 3 * PI)
				//{
				//	m_action[0].mode = 1;
				//	m_action[0].direction = f_dir>0 ? 0 : 14;//0-6左转，7中间值，8-14右转
				//}
				//else
				//{
				//	m_action[0].mode = 0;                                                                                                                                                                                                                             
				//	m_action[0].direction = 7;
				//}
				//m_FishInfo[0].SetAction(m_action[0]);
				m_action[0].speed = 15;
				if (f_dir > 3 / 4 * PI || f_dir < -3 / 4 * PI)
				{
					m_action[0].mode = 1;
					m_action[0].direction = f_dir>0 ? 0 : 14;//0-6左转，7中间值，8-14右转
				}
				else if ((f_dir >-3 / 4 * PI && f_dir <  -1 / 4 * PI) || (f_dir >1 / 4 * PI && f_dir <  3 / 4 * PI))
				{
					if (f_pt.y < 50)
					{
						if ((f_dir >-3 / 4 * PI && f_dir < -1 / 4 * PI))
						{
							m_action[0].mode = 1;
							m_action[0].direction = 14;
						}
						else if ((f_dir >1 / 4 * PI && f_dir < 3 / 4 * PI))  //改改直游
						{
							m_action[0].mode = 0;
							m_action[0].direction = 7;
						}
					}
					else if (f_pt.y>430)
					{
						if ((f_dir >-3 / 4 * PI && f_dir < -1 / 4 * PI))
						{
							m_action[0].mode = 0;
							m_action[0].direction = 7;
						}
						else if ((f_dir >1 / 4 * PI && f_dir < 3 / 4 * PI))
						{
							m_action[0].mode = 1;
							m_action[0].direction = 14;
						}
					}
					else
					{
						m_action[0].mode = 0;
						m_action[0].direction = 7;
					}
				}
				else
				{
					m_action[0].mode = 1;
					m_action[0].direction = f_dir<0 ? 0 : 14;
				}
				m_FishInfo[0].SetAction(m_action[0]);
			}
		}
	}
	else
	{
		if (f_headpt.x>b_pt.x + r)
		{
			//			Roundp2p2(temp1, m_action[0], 0, m_FishInfo[0], m_goalinfo, m_Channel);
			//			Roundp2p1(tempLeft, m_action[0], 0, m_FishInfo[0]);
			if (closeToGoal == true)
			{
				Roundp2p1(tempLeft, m_action[0], 0, m_FishInfo[0]);
			}
			else
			{
				if (closeToGoal1 == true)
				{
					PushBallToLeft(temp1, g_pt, m_goalinfo, m_action, m_FishInfo, m_Channel);  //向左甩尾
				}
				Roundp2p3(ready, temp1, m_action[0], 0, m_FishInfo[0], m_goalinfo, m_Channel);
				
			}
		}
		else
		{
			if (f_headpt.y<b_pt.y - r)
			{
				if (f_headpt.x>b_pt.x - 40)
				{
					Roundp2p1(temp3, m_action[0], 0, m_FishInfo[0]);
				}
				else
				{
					Roundp2p1(tempUp, m_action[0], 0, m_FishInfo[0]);
				}
			}
			else if (f_headpt.y>b_pt.y + r)
			{
				if (f_headpt.x>b_pt.x - 40)
				{
					Roundp2p1(temp3, m_action[0], 0, m_FishInfo[0]);
				}
				else
				{
					Roundp2p1(tempDown, m_action[0], 0, m_FishInfo[0]);
				}
			}
			else
			{
				other(m_action[0], 0, m_FishInfo[0]);
				////m_action[0].speed = 15;
				////if (f_dir > 2 / 3 * PI || f_dir < -2 / 3 * PI)
				////{
				////	m_action[0].mode = 1;
				////	m_action[0].direction = f_dir>0 ? 0 : 14;//0-6左转，7中间值，8-14右转
				////}
				////else
				////{
				////	m_action[0].mode = 0;
				////	m_action[0].direction = 7;
				////}
				////m_FishInfo[0].SetAction(m_action[0]);
				//m_action[0].speed = 15;
				//if (f_dir > 3 / 4 * PI || f_dir < -3 / 4 * PI)
				//{
				//	m_action[0].mode = 1;
				//	m_action[0].direction = f_dir>0 ? 0 : 14;//0-6左转，7中间值，8-14右转
				//}
				//else if ((f_dir >-3 / 4 * PI && f_dir <  -1 / 4 * PI) || (f_dir >1 / 4 * PI && f_dir <  3 / 4 * PI))
				//{
				//	if (f_pt.y < 50)
				//	{
				//		if ((f_dir >-3 / 4 * PI && f_dir < -1 / 4 * PI))
				//		{
				//			m_action[0].mode = 1;
				//			m_action[0].direction = 14;
				//		}
				//		else if ((f_dir >1 / 4 * PI && f_dir < 3 / 4 * PI))
				//		{
				//			m_action[0].mode = 0;
				//			m_action[0].direction = 7;
				//		}
				//	}
				//	else if (f_pt.y>430)
				//	{
				//		if ((f_dir >-3 / 4 * PI && f_dir < -1 / 4 * PI))
				//		{
				//			m_action[0].mode = 0;
				//			m_action[0].direction = 7;
				//		}
				//		else if ((f_dir >1 / 4 * PI && f_dir < 3 / 4 * PI))
				//		{
				//			m_action[0].mode = 1;
				//			m_action[0].direction = 14;
				//		}
				//	}
				//	else
				//	{
				//		m_action[0].mode = 0;
				//		m_action[0].direction = 7;
				//	}
				//}
				//else
				//{
				//	m_action[0].mode = 1;
				//	m_action[0].direction = f_dir<0 ? 0 : 14;
				//}
				//m_FishInfo[0].SetAction(m_action[0]);
			}
		}
	}

	return true;
}
