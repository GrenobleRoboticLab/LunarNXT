#include "LunarNXT/LineFinder.h"
#include "LunarNXT/Tools.h"

using namespace Lunar_lib;

LineFinder::LineFinder() : Mode() { m_nState = 0; }

void LineFinder::UpdateColor(nxt_msgs::Color msg) { 
	m_ColorMsg = msg;
	if (IsLaunched() && IsInitialized()) {
		Treat();
	}
}

void LineFinder::Treat() {
	if (CheckMoveManager()) {
		if (Tools::is_line_color(m_ColorMsg)) {
			if(m_nState < 3) {
				if (CheckLabyElement())
					m_pLabyElement->AppendElement(m_nState+1);	
				switch(m_nState) {
				case 0:
					((MoveMgr*)*m_ppMoveManager)->TurnLeft(BASE_EFFORT);
					m_nState = 3;
					break;
				case 1:
					((MoveMgr*)*m_ppMoveManager)->LinearMove(BASE_EFFORT);
					m_nState = 3;
					break;
				case 2:
					((MoveMgr*)*m_ppMoveManager)->TurnRight(BASE_EFFORT);
					m_nState = 3;
					break;	
				}
			}
		}
		else if(Tools::is_pastille_color(m_ColorMsg)) {
			m_bLineNotFound = false;
			switch(m_nState) {
			case 0:
				m_fLPos = ((MoveMgr*)*m_ppMoveManager)->GetLeftPos();
				m_fRPos = ((MoveMgr*)*m_ppMoveManager)->GetRightPos();
				((MoveMgr*)*m_ppMoveManager)->TurnLeft(BASE_EFFORT);
				break;
			case 1:
				m_fLPos = ((MoveMgr*)*m_ppMoveManager)->GetLeftPos();
				m_fRPos = ((MoveMgr*)*m_ppMoveManager)->GetRightPos();
				((MoveMgr*)*m_ppMoveManager)->LinearMove(BASE_EFFORT);
				break;
			case 2:
				m_fLPos = ((MoveMgr*)*m_ppMoveManager)->GetLeftPos();
				m_fRPos = ((MoveMgr*)*m_ppMoveManager)->GetRightPos();
				((MoveMgr*)*m_ppMoveManager)->TurnRight(BASE_EFFORT);
				break;
			case 3:
				Unlaunch();
				break;
			default: break;
			}
		}
		else if(Tools::is_ground_color(m_ColorMsg) && !m_bLineNotFound && CheckDist(1)){
			switch(m_nState) {
			case 0:
				m_nState++;
				m_bLineNotFound = true;
				((MoveMgr*)*m_ppMoveManager)->TurnRight(BASE_EFFORT);
				break;
			case 1:
				m_nState++;			
				m_bLineNotFound = true;
				((MoveMgr*)*m_ppMoveManager)->LinearMove(-BASE_EFFORT);
				break;
			case 2:
				m_nState++;
				m_bLineNotFound = true;
				((MoveMgr*)*m_ppMoveManager)->TurnLeft(BASE_EFFORT);
				break;
			default: 
				break;
			}
		}
	}
}

bool LineFinder::CheckDist(int dist) {
	if (	(((MoveMgr*)*m_ppMoveManager)->GetLeftPos() - m_fLPos > dist) || 
		(((MoveMgr*)*m_ppMoveManager)->GetRightPos() - m_fRPos > dist)) {
		return true;
	}
	return false;
}

void LineFinder::Init(LabyElement* element) { 
	m_pLabyElement = element;
	SetInitialized(true);
}

bool LineFinder::CheckLabyElement() {
	bool bRet = true;

	if (!m_pLabyElement) {
		ROS_ERROR("LabyElement is null.");
	}

	return bRet;
}
