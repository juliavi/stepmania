#include "global.h"
/*
-----------------------------------------------------------------------------
 Class: HoldJudgment

 Desc: A graphic displayed in the HoldJudgment during Dancing.

 Copyright (c) 2001-2002 by the person(s) listed below.  All rights reserved.
	Chris Danford
-----------------------------------------------------------------------------
*/

#include "HoldJudgment.h"
#include "RageUtil.h"
#include "GameConstantsAndTypes.h"
#include "PrefsManager.h"
#include "ThemeManager.h"


CachedThemeMetric	OK_COMMAND	("HoldJudgment","OKCommand");
CachedThemeMetric	NG_COMMAND	("HoldJudgment","NGCommand");

CachedThemeMetric	OK_ODD_COMMAND	("HoldJudgment","OKOddCommand");
CachedThemeMetric	NG_ODD_COMMAND	("HoldJudgment","NGOddCommand");

CachedThemeMetric	OK_EVEN_COMMAND	("HoldJudgment","OKEvenCommand");
CachedThemeMetric	NG_EVEN_COMMAND	("HoldJudgment","NGEvenCommand");


HoldJudgment::HoldJudgment()
{
	OK_COMMAND.Refresh();
	NG_COMMAND.Refresh();

	OK_ODD_COMMAND.Refresh();
	NG_ODD_COMMAND.Refresh();

	OK_EVEN_COMMAND.Refresh();
	NG_EVEN_COMMAND.Refresh();

	m_iCount = 0;

	m_sprJudgment.Load( THEME->GetPathToG("HoldJudgment 1x2") );
	m_sprJudgment.StopAnimating();
	Reset();
	this->AddChild( &m_sprJudgment );
}

void HoldJudgment::Update( float fDeltaTime )
{
	ActorFrame::Update( fDeltaTime );
}

void HoldJudgment::DrawPrimitives()
{
	ActorFrame::DrawPrimitives();
}

void HoldJudgment::Reset()
{
	m_sprJudgment.SetDiffuse( RageColor(1,1,1,0) );
	m_sprJudgment.SetXY( 0, 0 );
	m_sprJudgment.StopTweening();
	m_sprJudgment.SetEffectNone();
}

void HoldJudgment::SetHoldJudgment( HoldNoteScore hns )
{
	//LOG->Trace( "Judgment::SetJudgment()" );

	Reset();

	switch( hns )
	{
	case HNS_NONE:
		ASSERT(0);
	case HNS_OK:
		m_sprJudgment.SetState( 0 );
		m_sprJudgment.Command( (m_iCount%2) ? OK_ODD_COMMAND : OK_EVEN_COMMAND );
		m_sprJudgment.Command( OK_COMMAND );
		break;
	case HNS_NG:
		m_sprJudgment.SetState( 1 );
		m_sprJudgment.Command( (m_iCount%2) ? NG_ODD_COMMAND : NG_EVEN_COMMAND );
		m_sprJudgment.Command( NG_COMMAND );
		break;
	default:
		ASSERT(0);
	}

	m_iCount++;
}
