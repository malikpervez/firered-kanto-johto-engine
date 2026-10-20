#ifndef GUARD_FIRERED_SAVE_H
#define GUARD_FIRERED_SAVE_H

#ifdef FIRERED
#define SAVE_STATUS_RECOVERED 3
#define SAVE_STATUS_UNSUPPORTED 5

bool8 FireRedSave_IsBusy(void);
bool8 FireRedSave_IsLoaded(void);
u8 FireRedSave_LastResult(void);
void FireRedSave_Abort(void);
void FireRedSave_NotifyPersistentWrite(void);
void FireRedSave_ResetSession(void);
u8 FireRedSave_Probe(void);
#endif

#endif
