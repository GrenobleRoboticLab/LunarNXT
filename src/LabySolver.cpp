#include "LunarNXT/LabySolver.h"
#include "LunarNXT/Tools.h"

using namespace Lunar_lib;

// Constructeurs
LabySolver::LabySolver() : Mode() { }

LabySolver::~LabySolver() { 
	delete m_pCurrentElement;
}

bool LabySolver::SetMoveManager(MoveMgr** ppMoveManager) {
    bool bRet = Mode::SetMoveManager(ppMoveManager);
    
    if (
        m_LineFinder.SetMoveManager(ppMoveManager)      &&
        m_Navigator.SetMoveManager(ppMoveManager)
        )
        bRet = true;
        
    return bRet;
}

void LabySolver::UpdateColor(nxt_msgs::Color msg) {
	m_ColorMsg = msg;
	if (IsLaunched() && IsInitialized())
		Treat();
	else if (IsLaunched()) {
		m_pCurrentMode = NULL;
		m_State = INIT;
	}
}

void LabySolver::Treat () {
	if (Tools::is_end_color(m_ColorMsg)) {
		m_pCurrentMode->UpdateColor(m_ColorMsg);
		if (!m_pCurrentMode->IsLaunched()) {
			switch(m_State) {
				case INIT:
					NavLauncher(std::list<Map::Choice>());
					break;
				case NAVIGATE:
					LineFinderLauncher();
					break;
				case LINEFINDER:
					Compute();
					break;
			}
		}
	}
	else
	    Unlaunch();
}

void LabySolver::NavLauncher(std::list<Map::Choice> choices) {
	m_Navigator.Init(choices);
	m_pCurrentMode = &m_Navigator;
	m_pCurrentMode->Launch();
	m_State = NAVIGATE;
}

void LabySolver::LineFinderLauncher() {
	m_LineFinder.Init(m_pCurrentElement);
	m_pCurrentMode = &m_LineFinder;
	m_pCurrentMode->Launch();
	m_State = LINEFINDER;
}

void LabySolver::Compute() {
	std::list<Map::Choice> choice = std::list<Map::Choice>();
	choice.push_back(m_pCurrentElement->GetLeftChoice(&m_pCurrentElement));
	NavLauncher(choice);
}
