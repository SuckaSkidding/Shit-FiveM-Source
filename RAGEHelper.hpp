#include "includethread.h"
#include<psapi.h>
rage::scrThread* GetActiveThread();
rage::pgPtrCollection<GtaThread>* GetGtaThreadCollection();
void SetActiveThread(rage::scrThread* thread);

