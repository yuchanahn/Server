// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

using global::System;
using global::FlatBuffers;

public struct Base : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static Base GetRootAsBase(ByteBuffer _bb) { return GetRootAsBase(_bb, new Base()); }
  public static Base GetRootAsBase(ByteBuffer _bb, Base obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public Base __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public Class CType { get { int o = __p.__offset(4); return o != 0 ? (Class)__p.bb.GetInt(o + __p.bb_pos) : Class.Base; } }

  public static Offset<Base> CreateBase(FlatBufferBuilder builder,
      Class cType = Class.Base) {
    builder.StartObject(1);
    Base.AddCType(builder, cType);
    return Base.EndBase(builder);
  }

  public static void StartBase(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddCType(FlatBufferBuilder builder, Class cType) { builder.AddInt(0, (int)cType, 0); }
  public static Offset<Base> EndBase(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<Base>(o);
  }
  public static void FinishBaseBuffer(FlatBufferBuilder builder, Offset<Base> offset) { builder.Finish(offset.Value); }
  public static void FinishSizePrefixedBaseBuffer(FlatBufferBuilder builder, Offset<Base> offset) { builder.FinishSizePrefixed(offset.Value); }
};

