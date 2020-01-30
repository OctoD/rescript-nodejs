/**
 * TODO: Add lots of tests for these functions, expecially the
 * `classify` funciton and its variants.
 */

open Js.TypedArray2;

type t;

type case =
  | String(string)
  | Buffer(Buffer.t)
  | Int8Array(Int8Array.t)
  | Uint8Array(Uint8Array.t)
  | Uint8ClampedArray(Uint8ClampedArray.t)
  | Uint16Array(Uint16Array.t)
  | Int16Array(Int16Array.t)
  | Uint32Array(Uint32Array.t)
  | Int32Array(Int32Array.t)
  | Float32Array(Float32Array.t)
  | Float64Array(Float64Array.t)
  | DataView(DataView.t);

external string: string => t = "%identity";
external buffer: Buffer.t => t = "%identity";
external int8Array: Int8Array.t => t = "%identity";
external uInt8Array: Uint8Array.t => t = "%identity";
external uInt8ClampedArray: Uint8ClampedArray.t => t = "%identity";
external uInt16Array: Uint16Array.t => t = "%identity";
external int16Array: Int16Array.t => t = "%identity";
external uInt32Array: Uint32Array.t => t = "%identity";
external int32Array: Int32Array.t => t = "%identity";
external float32Array: Float32Array.t => t = "%identity";
external float64Array: Float64Array.t => t = "%identity";
external dataView: DataView.t => t = "%identity";

[%%bs.raw {|
function jsReflectClass(data) {
  let str = Object.prototype.toString.call(data);
  return str.slice(8, -1);
}
|}]

module Unsafe = {
  [@bs.val] external jsReflectClass: t => string = "jsReflectClass";
  [@bs.get] [@bs.scope "constructor"] external jsConstructorName: t => string = "name";
};

let classifyOpt: t => option(case) = (binaryLike) => {
  if (Js.typeof(binaryLike) === "string") {
    Some(String(Obj.magic(binaryLike)))
  } else if (Buffer.isBuffer(binaryLike)) {
    Some(Buffer(Obj.magic(binaryLike)))
  } else {
    switch (Unsafe.jsReflectClass(binaryLike)) {
      | "Int8Array" => Some(Int8Array(Obj.magic(binaryLike)));
      | "Uint8Array" => Some(Uint8Array(Obj.magic(binaryLike)));
      | "Uint8ClampedArray" => Some(Uint8ClampedArray(Obj.magic(binaryLike)));
      | "Int16Array" => Some(Int16Array(Obj.magic(binaryLike)));
      | "Uint16Array" => Some(Uint16Array(Obj.magic(binaryLike)));
      | "Int32Array" => Some(Int32Array(Obj.magic(binaryLike)));
      | "Uint32Array" => Some(Uint32Array(Obj.magic(binaryLike)));
      | "Float32Array" => Some(Float32Array(Obj.magic(binaryLike)));
      | "Float64Array" => Some(Float64Array(Obj.magic(binaryLike)));
      | "DataView" => Some(DataView(Obj.magic(binaryLike)));
      | _ => None;
    };
  };
};

let classifyExn: t => case = (binaryLike) => {
  switch (classifyOpt(binaryLike)) {
    | None => failwith("Unknown Data Type");
    | Some(data) => data;
  };
};

let classify: t => Belt.Result.t(case, t) = (binaryLike) => {
  switch (classifyOpt(binaryLike)) {
    | None => Error(binaryLike);
    | Some(data) => Ok(data);
  };
};
