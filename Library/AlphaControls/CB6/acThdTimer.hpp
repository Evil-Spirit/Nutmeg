// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acThdTimer.pas' rev: 6.00

#ifndef acThdTimerHPP
#define acThdTimerHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SyncObjs.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Acthdtimer
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TacTimerThread;
class DELPHICLASS TacThreadedTimer;
class PASCALIMPLEMENTATION TacThreadedTimer : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	bool FEnabled;
	unsigned FInterval;
	Classes::TNotifyEvent FOnTimer;
	TacTimerThread* FTimerThread;
	Classes::TThreadPriority FThreadPriority;
	void __fastcall KillTimer(void);
	void __fastcall StartTimer(void);
	
protected:
	System::TObject* FOwner;
	bool InHandler;
	void __fastcall UpdateTimer(void);
	void __fastcall SetEnabled(bool Value);
	void __fastcall SetInterval(unsigned Value);
	void __fastcall SetOnTimer(Classes::TNotifyEvent Value);
	void __fastcall SetThreadPriority(Classes::TThreadPriority Value);
	DYNAMIC void __fastcall Timer(void);
	virtual void __fastcall TimeHandler(void);
	void __fastcall TimeEvent(System::TObject* Sender);
	
public:
	__fastcall virtual TacThreadedTimer(Classes::TComponent* AOwner);
	__fastcall virtual TacThreadedTimer(Classes::TComponent* AOwner, bool ChangeEvent);
	__fastcall virtual ~TacThreadedTimer(void);
	void __fastcall Reset(void);
	
__published:
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=1};
	__property unsigned Interval = {read=FInterval, write=SetInterval, default=1000};
	__property Classes::TNotifyEvent OnTimer = {read=FOnTimer, write=SetOnTimer};
	__property Classes::TThreadPriority ThreadPriority = {read=FThreadPriority, write=SetThreadPriority, nodefault};
};


class PASCALIMPLEMENTATION TacTimerThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
public:
	TacThreadedTimer* OwnerTimer;
	unsigned Interval;
	Syncobjs::TSimpleEvent* TimeEvent;
	virtual void __fastcall Execute(void);
	void __fastcall DoTimer(void);
public:
	#pragma option push -w-inl
	/* TThread.Create */ inline __fastcall TacTimerThread(bool CreateSuspended) : Classes::TThread(CreateSuspended) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TacTimerThread(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Acthdtimer */
using namespace Acthdtimer;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acThdTimer
