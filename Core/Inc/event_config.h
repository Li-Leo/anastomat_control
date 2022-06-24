#pragma once
/************************************************
* Declaration
************************************************/
#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
	kEventNewTick,
	kEventReceiveNewMsg,

	kEventIDMax
} EventID;

#ifdef __cplusplus
}
#endif


