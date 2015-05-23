// grp.cc
#include <node.h>
#include <sys/types.h>
#include <grp.h>

namespace grp {

using namespace v8;
  
Local<Object> mkgroup(Isolate* isolate, const struct group* grp) {
  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "gr_name"), String::NewFromUtf8(isolate, grp->gr_name));
  //obj->Set(String::NewFromUtf8(isolate, "gr_passwd"), String::NewFromUtf8(isolate, grp->gr_passwd));
  obj->Set(String::NewFromUtf8(isolate, "gr_gid"), Number::New(isolate, grp->gr_gid));
  // TODO return member
  // grp->gr_mem
  return obj;
}

void Getgrgid(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  
  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if (!args[0]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Argument must be a number")));
    return;
  }

  gid_t gid = args[0]->NumberValue();

  struct group *grp = getgrgid(gid);

  if (grp != NULL) {
    args.GetReturnValue().Set(mkgroup(isolate, grp));
  }
}
  
void Getgrnam(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  
  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if (!args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Argument must be a string")));
    return;
  }

  String::Utf8Value name(args[0]);

  struct group *grp = getgrnam(*name);

  if (grp != NULL) {
    args.GetReturnValue().Set(mkgroup(isolate, grp));
  }
}

void Init(Local<Object> exports, Local<Object> module) {
  NODE_SET_METHOD(exports, "getgrgid", Getgrgid);
  NODE_SET_METHOD(exports, "getgrnam", Getgrnam);
}

NODE_MODULE(addon, Init)

}  // namespace grp