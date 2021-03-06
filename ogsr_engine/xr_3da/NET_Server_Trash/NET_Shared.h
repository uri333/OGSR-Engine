#pragma once
#include "../Engine.h"

//������� ����������, ���� ������.
#define DPNSEND_GUARANTEED 0x0008
#define DPNSEND_NOCOMPLETE 0x0002
#define DPNSEND_NONSEQUENTIAL 0x0010
#define DPNSEND_PRIORITY_HIGH 0x0080

#include "net_utils.h"
#include "net_messages.h"

ENGINE_API extern ClientID BroadcastCID;

IC u32 TimeGlobal	(CTimer* timer)	{ return timer->GetElapsed_ms();	}
IC u32 TimerAsync	(CTimer* timer) { return TimeGlobal	(timer);		}
