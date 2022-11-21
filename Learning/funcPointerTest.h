#ifndef __FUNCPOINTERTEST_H__
#define __FUNCPOINTERTEST_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef void (*pCallback)(void* param);

extern void Register_Callback(pCallback callback_reg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FUNCPOINTERTEST_H__ */
