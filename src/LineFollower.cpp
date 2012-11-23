#include "LunarNXT/LineFollower.h"
#include "LunarNXT/Tools.h"

using namespace Lunar_lib;

// Constructeurs
LineFollower::LineFollower() : Mode() { 
	m_bOnline = false;
	m_wOrientation = Map::WEST;
}

// Mise a jour du capteur de couleurs
void LineFollower::UpdateColor(nxt_msgs::Color msg) {
	m_ColorMsg = msg;
	if (IsInitialized()) {
		Treat();
	}
	else if (IsLaunched()) {
		m_nCount = 0;
		SetInitialized(true);
		m_bOnline = true;
	}
}

// Traitement du mode
void LineFollower::Treat() {
	if(Tools::is_line_color(m_ColorMsg)) {
		m_bOnline = true;
		if (CheckMoveManager()) {
			((MoveMgr*)*m_ppMoveManager)->Stop();
			((MoveMgr*)*m_ppMoveManager)->LinearMove(0.8);
		}
	}
	else {
		if (m_bOnline) {
			m_nCount++;
			m_bOnline = false;
			if (CheckMoveManager())
				((MoveMgr*)*m_ppMoveManager)->Turn(BASE_EFFORT, ((m_wOrientation-2)*0.4));
		}
		else if(((MoveMgr*)*m_ppMoveManager)->HasGoalSet()) {
			m_nCount++;
			m_wOrientation = (Map::Cardinal)((m_wOrientation+2)%4);
			if (CheckMoveManager())
				((MoveMgr*)m_ppMoveManager)->Turn(BASE_EFFORT, -(m_wOrientation-2)*0.8);
		}
		if (m_nCount > 2) {
			m_nCount = 0;
			if (CheckMoveManager())
				((MoveMgr*)*m_ppMoveManager)->LinearMove(BASE_EFFORT, 1);
		}
	}
}

void LineFollower::SetOrientation(Map::Cardinal orientation) { m_wOrientation = orientation; }
