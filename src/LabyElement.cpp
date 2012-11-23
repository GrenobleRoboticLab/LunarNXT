#include "LunarNXT/LabyElement.h"

using namespace Lunar_lib;

LabyElement::LabyElement() { 
    for (int i = 0; i < 4; i++)
        m_pWays[i] = NULL;
	m_nVisiteCount = 0;
}

LabyElement::~LabyElement() {
	for (int i = 1; i < 4; i++)
	{
	    if(m_pWays[i])
	        delete m_pWays[i];
	}
}

void LabyElement::SetPrev(LabyElement* pPrev) {
    if (!m_pWays[0])
	    m_pWays[0] = pPrev;
}

Map::Choice LabyElement::GetLeftChoice(LabyElement** ppCurrent) {
	int nTempVisitCount = m_nVisiteCount;
	int nRet = 3;
	int i = 0;

	while (nRet == 3) {
		if (m_pWays[(m_nVisiteCount+i) % 4] != NULL && m_pWays[(m_nVisiteCount+i) % 4]->GetVisited() == 0) {
			nRet -= (4-i);
			if(ppCurrent)
				*ppCurrent = m_pWays[(m_nVisiteCount+i) % 4];
		}
		else if (m_pWays[(m_nVisiteCount+i) % 4] == NULL)
		    nTempVisitCount++;
		i++;
	}
	
	m_nVisiteCount = nTempVisitCount;
	
	return (Map::Choice)(-nRet);
}

int LabyElement::GetVisited()   { return m_nVisiteCount; }
void LabyElement::AddVisit()    { m_nVisiteCount++; }

void LabyElement::AppendElement(int index) {
    LabyElement*    pElement = new LabyElement();
    
    if (pElement)
    {
        pElement->SetPrev(this);
        m_pWays[index] = pElement; 
    }
}

LabyElement* LabyElement::GetElement(int index) { return m_pWays[index]; }
