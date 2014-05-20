#include <node.h>
#include <v8.h>
#include <sys/types.h>
#include <grp.h>

using namespace v8;


Local<Object> mkgroup(const struct group *grp) {
  Local<Object> obj = Object::New();
  obj->Set(String::NewSymbol("gr_name"), String::New(grp->gr_name));
  // obj->Set(String::NewSymbol("gr_passwd"), String::New(grp->gr_passwd));
  obj->Set(String::NewSymbol("gr_gid"), Number::New(grp->gr_gid));
  // TODO return member
  // grp->gr_mem
  return obj;
}

Handle<Value> Getgrgid(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 0) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Argument must be a number")));
    return scope.Close(Undefined());
  }

  gid_t gid = args[0]->NumberValue();

  struct group *grp = getgrgid(gid);

  if (grp == NULL) {
    return scope.Close(Undefined());
  } else {
    return scope.Close(mkgroup(grp));
  }
}


Handle<Value> Getgrnam(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 0) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsString()) {
    ThrowException(Exception::TypeError(String::New("Argument must be a string")));
    return scope.Close(Undefined());
  }

  String::Utf8Value name(args[0]);

  struct group *grp = getgrnam(*name);

  if (grp == NULL) {
    return scope.Close(Undefined());
  } else {
    return scope.Close(mkgroup(grp));
  }
}

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("getgrgid"),
    FunctionTemplate::New(Getgrgid)->GetFunction());
  exports->Set(String::NewSymbol("getgrnam"),
    FunctionTemplate::New(Getgrnam)->GetFunction());
}

NODE_MODULE(grp, init)

