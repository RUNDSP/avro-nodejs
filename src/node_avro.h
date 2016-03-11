#include <v8.h>
#include <node.h>
#include <node_buffer.h>
#include <avro/ValidSchema.hh>
#include <avro/Generic.hh>
#include <avro/Schema.hh>
#include <avro/DataFile.hh>
#include <avro/Compiler.hh>
#include <avro/Decoder.hh>
#include <avro/Encoder.hh>
#include <avro/Specific.hh>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>
#include "BufferedInputStream.hh"
#include "helpers.h"
#include "uv.h"

using namespace node;
using namespace avro;
using namespace v8;

namespace node {

struct datumBaton {
  ValidSchema schema;
  GenericDatum *datum;
  const char* errorMessage;
  Persistent<Value> onSuccess;
  Persistent<Value> onError;
};

class Avro : public node::ObjectWrap
{
public:
  Avro() : node::ObjectWrap(), dictionary_(){};
  ~Avro() {};
  std::queue<datumBaton> processQueue_;
  std::vector<datumBaton> datums_;
  DecoderPtr decoder_;
  helper::SymbolMap dictionary_;
  uv_sem_t sem_;
  uv_loop_t *avro_loop_;
  uv_async_t async_;
  uv_mutex_t datumLock_;
  uv_mutex_t queueLock_;
  avronode::BufferedInputStream *buffer_;
  bool read_;
  static void Initialize(Handle<Object> target);
private: 
  static Handle<Value> New(const v8::internal::Arguments& args);
  static Handle<Value> ClearDictionary(const v8::internal::Arguments& args);
  static Handle<Value> QueueSchema(const v8::internal::Arguments &args);
  static Handle<Value> AddSchema(const v8::internal::Arguments &args);
  static Handle<Value> PendingSchemas(const v8::internal::Arguments &args);
  static Handle<Value> Push(const v8::internal::Arguments &args);  
  static Handle<Value> BufferLength(const v8::internal::Arguments &args);
  static Handle<Value> DecodeFile(const v8::internal::Arguments &args);
  static Handle<Value> EncodeDatum(const v8::internal::Arguments &args);
  static Handle<Value> EncodeDatumFile(const v8::internal::Arguments &args);
  static Handle<Value> DecodeDatum(const v8::internal::Arguments &args);
  static Handle<Value> Close(const v8::internal::Arguments &args);

};
}
