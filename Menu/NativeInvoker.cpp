//NativeInvoker.cpp
#include "main.h"

static NativeManagerContext g_context;

static UINT64 g_hash;

void(*scrNativeCallContext::SetVectorResults)(scrNativeCallContext*) = nullptr;
//函数初始化
void nativeInit(UINT64 hash) {
	g_context.Reset();
	g_hash = hash;
}

void nativePush64(UINT64 value) {
	g_context.Push(value);
}
//函数调用
uint64_t * nativeCall() {
    //获取处理器
    Hook::NativeHandler fn = Hook::GetNativeHandler(g_hash);
	if (fn != 0) {
		static void* exceptionAddress;
		//截获异常
		__try{
		    fn(&g_context);
		    scrNativeCallContext::SetVectorResults(&g_context);
        } catch (...) {
		Log::Error("Fatal Error!,Could't invoke function");
		}
	}
	//返回的指针
	return (uint64_t*)g_context.GetResultPointer();
}

