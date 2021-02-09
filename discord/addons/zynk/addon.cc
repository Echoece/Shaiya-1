#include "addon.h"

Napi::Value getProcessIdEx(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  std::string szExeFile = info[0].As<Napi::String>().Utf8Value();
  DWORD dwProcessId = GetProcessIdEx(szExeFile.c_str());
  
  return Napi::Value::From(env, dwProcessId);
}

Napi::Value userCount(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  UINT lpBuffer;
  if (BOOL value = ReadProcessMemoryEx("ps_game.exe", (LPVOID)0x109E6F8, &lpBuffer, 4) == FALSE) {
    return Napi::Boolean::New(env, value);
  }

  return Napi::Value::From(env, lpBuffer);
}

Napi::Boolean setSeDebugPrivilege(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  BOOL value = SetSeDebugPrivilege();

  return Napi::Boolean::New(env, value);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "getProcessIdEx"), Napi::Function::New(env, getProcessIdEx));
  exports.Set(Napi::String::New(env, "userCount"), Napi::Function::New(env, userCount));
  exports.Set(Napi::String::New(env, "setSeDebugPrivilege"), Napi::Function::New(env, setSeDebugPrivilege));
  return exports;
}

NODE_API_MODULE(zynk, Init)
