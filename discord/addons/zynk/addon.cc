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
  if (!ReadProcessMemoryEx("ps_game.exe", (LPVOID)0x109E6F8, &lpBuffer, 4)) {
    return Napi::Boolean::New(env, FALSE);
  }

  return Napi::Value::From(env, lpBuffer);
}

Napi::Boolean setSeDebugPrivilege(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  BOOL b = SetSeDebugPrivilege();

  return Napi::Boolean::New(env, b);
}

Napi::Boolean blessOfGoddess(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  UINT lpBuffer = info[0].As<Napi::Number>().Uint32Value();

  if (!WriteProcessMemoryEx("ps_game.exe", (LPVOID)0x10A2264, &lpBuffer, 4)) {
    return Napi::Boolean::New(env, FALSE);
  }

  if (!WriteProcessMemoryEx("ps_game.exe", (LPVOID)0x10A22E8, &lpBuffer, 4)) {
    return Napi::Boolean::New(env, FALSE);
  }

  return Napi::Boolean::New(env, TRUE);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "getProcessIdEx"), Napi::Function::New(env, getProcessIdEx));
  exports.Set(Napi::String::New(env, "userCount"), Napi::Function::New(env, userCount));
  exports.Set(Napi::String::New(env, "setSeDebugPrivilege"), Napi::Function::New(env, setSeDebugPrivilege));
  exports.Set(Napi::String::New(env, "blessOfGoddess"), Napi::Function::New(env, blessOfGoddess));
  return exports;
}

NODE_API_MODULE(zynk, Init)
