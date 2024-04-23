#pragma once
#include <basetsd.h>
#include <cstdint>

enum eThreadState
{
	ThreadStateIdle,
	ThreadStateRunning,
	ThreadStateKilled,
	ThreadState3,
	ThreadState4,
};

namespace rage
{


	struct scrThreadContext
	{
		uint32_t ThreadId;
		uint32_t ScriptHash; // + 4 (program id)
		eThreadState State; // + 8
		uint32_t IP; // + 12
		uint32_t FrameSP; // 
		uint32_t SP; // + 20, aka + 28
		uint32_t TimerA; // + 24
		uint32_t TimerB; // + 28
		uint32_t TimerC; // + 32, aka + 40
		uint32_t _mUnk1;
		uint32_t _mUnk2;
		uint32_t _f2C;
		uint32_t _f30;
		uint32_t _f34;
		uint32_t _f38;
		uint32_t _f3C;
		uint32_t _f40;
		uint32_t _f44;
		uint32_t _f48;
		uint32_t _f4C;
		uint32_t _f50; // should be +88 aka +80; stack size?

		uint32_t pad1;
		uint32_t pad2;
		uint32_t pad3;

		uint32_t _set1;

		uint32_t pad[68 / 4];
	};

	static_assert(sizeof(scrThreadContext) == 0xA8, "scrThreadContext size mismatch");

	class scrThread
	{
	public:
		//virtual ~scrThread() = 0;
		virtual void deconstructor() = 0;
		virtual eThreadState Reset(UINT32 scriptHash, void* pArgs, UINT32 argCount) = 0;
		virtual eThreadState Run() = 0; // This might have opsToExecute param but i didn't see it in IDA
		virtual eThreadState Tick(UINT32 opsToExecute) = 0;
		virtual void Kill() = 0;

		// There's really no 
		eThreadState GetThreadState() {
			return *(eThreadState*)((DWORD64)this + 0x10);
		}

		scrThreadContext* GetContext() {
			return &m_ctx;
		}

		scrThreadContext m_ctx;					// 0008
		void* m_pStack;							// 00B0
		void* pad;								// 00B8
		void* pad2;								// 00C0
		const char* m_pszExitMessage;			// 00C8
		char m_pad[0x4];
		char m_name[0x40];                          // 0xD4
		//scriptHandler* m_handler;                   // 0x114
		//scriptHandlerNetComponent* m_net_component; // 0x11C
	};
}



struct scrVector
{
	float x;

private:
	UINT32 pad;

public:
	float y;

private:
	UINT32 pad2;

public:
	float z;

private:
	UINT32 pad3;
};

class GtaThread : public rage::scrThread
{
protected:
	char gta_pad[64];
	void* m_pScriptHandler;
	char gta_pad2[40];
	char flag1;
	char m_networkFlag;
	char gta_pad3[22];
public:
	virtual void					DoRun() = 0;

	virtual eThreadState Reset(UINT32 scriptHash, void* pArgs, UINT32 argCount) = 0;
	virtual eThreadState Run() = 0;
	virtual eThreadState Tick(UINT32 opsToExecute) = 0;
	virtual void					Kill();

	inline void* GetScriptHandler() { return m_pScriptHandler; }

	inline void SetScriptHandler(void* scriptHandler) { m_pScriptHandler = scriptHandler; }

	inline void RemoveCleanupFlag() {  }
};

//static_assert(sizeof(GtaThread) == 0x158, "GtaThread size mismatch");

typedef struct {
public:
	void(*Deconstructor)(GtaThread* This);
	eThreadState(*Reset)(GtaThread* This, UINT32 scriptHash, void* pArgs, UINT32 argCount);
	eThreadState(*Run)(GtaThread* This);
	eThreadState(*Tick)(GtaThread* This, UINT32 opsToExecute);
	void(*Kill)(GtaThread* This);
	void(*unk001)(); // this shouldn't even exist, frankly
} GtaThread_VTable;

class scriptHandlerMgr
{
public:
	virtual ~scriptHandlerMgr() = 0;
	virtual void Padding001() = 0;
	virtual void Padding002() = 0;
	virtual void Padding003() = 0;
	virtual void Padding004() = 0;
	virtual void Padding005() = 0;
	virtual void Padding006() = 0;
	virtual void Padding007() = 0;
	virtual void Padding008() = 0;
	virtual void Padding009() = 0;
	virtual void AttachScript(GtaThread_VTable* thread) = 0;
};