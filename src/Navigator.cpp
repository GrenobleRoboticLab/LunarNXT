#include "LunarNXT/Navigator.h"
#include "LunarNXT/Tools.h"

#define TURN_RATIO 2 
#define PASTILLE_SIZE 2

using namespace Lunar_lib;

Navigator::Navigator() : Mode() { 
	m_bOnline = false;
}

bool Navigator::SetMoveManager(MoveMgr** ppMoveManager) {
	bool bRet = false;

	bRet = Mode::SetMoveManager(ppMoveManager);

	if (bRet)
		bRet = m_LineFollower.SetMoveManager(ppMoveManager);

	return bRet;
}

void Navigator::Treat() {
	if (Tools::is_pastille_color(m_ColorMsg))
		ApplyChoice();
	else {
		if (m_bOnline)
			m_LineFollower.UpdateColor(m_ColorMsg);
		else if (!((MoveMgr*)*m_ppMoveManager)->HasGoalSet()) 
			StartLineFollower();
	}
}

void Navigator::Init(std::list<Map::Choice> choices) { 
	m_lChoices = choices; 
	SetInitialized(true);
}

void Navigator::UpdateColor(nxt_msgs::Color msg) { 
	if (IsLaunched() && IsInitialized()) {
		m_ColorMsg = msg;
		Treat();
	}
}

void Navigator::StartLineFollower() { 
	m_LineFollower.Launch();
	m_bOnline = true;
}

void Navigator::StopLineFollower() {
	m_LineFollower.Unlaunch();
	m_bOnline = false;
}

void Navigator::ApplyChoice() {
	if (CheckDist(((MoveMgr*)*m_ppMoveManager)->GetLeftPos(), ((MoveMgr*)*m_ppMoveManager)->GetRightPos())) {
		if (m_bOnline)
			StopLineFollower();
		if (m_lChoices.size() <= 0)
			Unlaunch();
		else {
			Map::Choice choice = m_lChoices.front();
	        	m_lChoices.pop_front();

			switch (choice) {
	       			case Map::AHEAD:
	        			((MoveMgr*)*m_ppMoveManager)->LinearMove(BASE_EFFORT, PASTILLE_SIZE);
					break;
				case Map::BACK:
					((MoveMgr*)*m_ppMoveManager)->TurnAround(BASE_EFFORT, 3*MPI);
					break;
				default:
					((MoveMgr*)*m_ppMoveManager)->TurnAround(BASE_EFFORT+0.05, (choice * TURN_RATIO));
					m_LineFollower.SetOrientation((Map::Cardinal)(choice + 2));
					break;
			}

			m_fLPos = ((MoveMgr*)*m_ppMoveManager)->GetLeftPos();
			m_fRPos = ((MoveMgr*)*m_ppMoveManager)->GetRightPos();
		}
	}
}

bool Navigator::CheckDist(float a, float b) {
	bool bRet = false;

	if ((a - m_fLPos) > MPI 
	 || (b - m_fRPos) > MPI
	 || (a - m_fLPos) < -MPI
	 || (b - m_fRPos) < -MPI)
		bRet = true;
	
	return bRet;
}
