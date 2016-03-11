#include <node.h>
#include <avro/DataFile.hh>
#include <avro/ValidSchema.hh>
#include <avro/Generic.hh>
#include "translate.h"

using namespace v8;
using namespace node;
using namespace avro;


class AvroFileReader: public node::ObjectWrap {

  public:
    static void Init(Handle<Object> exports);

  private:
    AvroFileReader(const char* filename);
    ~AvroFileReader();

    static Handle<Value> Read(const v8::internal::Arguments& args);
    static Handle<Value> Close(const v8::internal::Arguments& args);
    static Handle<Value> New(const v8::internal::Arguments& args);
    static Persistent<Function> constructor;
    DataFileReader<GenericDatum> *reader_;
    ValidSchema schema_;

};
