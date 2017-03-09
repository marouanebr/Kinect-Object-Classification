// Auto-generated. Do not edit!

// (in-package mitsubishi_melfa.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class MelfaCommand {
  constructor() {
    this.iControl_type = 0;
    this.Type_Monitor1 = 0;
    this.Type_Monitor2 = 0;
    this.Type_Monitor3 = 0;
    this.Type_Monitor4 = 0;
    this.x = 0.0;
    this.y = 0.0;
    this.z = 0.0;
    this.rot_x = 0.0;
    this.rot_y = 0.0;
    this.rot_z = 0.0;
    this.j1 = 0.0;
    this.j2 = 0.0;
    this.j3 = 0.0;
    this.j4 = 0.0;
    this.j5 = 0.0;
    this.j6 = 0.0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type MelfaCommand
    // Serialize message field [iControl_type]
    bufferInfo = _serializer.int32(obj.iControl_type, bufferInfo);
    // Serialize message field [Type_Monitor1]
    bufferInfo = _serializer.char(obj.Type_Monitor1, bufferInfo);
    // Serialize message field [Type_Monitor2]
    bufferInfo = _serializer.char(obj.Type_Monitor2, bufferInfo);
    // Serialize message field [Type_Monitor3]
    bufferInfo = _serializer.char(obj.Type_Monitor3, bufferInfo);
    // Serialize message field [Type_Monitor4]
    bufferInfo = _serializer.char(obj.Type_Monitor4, bufferInfo);
    // Serialize message field [x]
    bufferInfo = _serializer.float32(obj.x, bufferInfo);
    // Serialize message field [y]
    bufferInfo = _serializer.float32(obj.y, bufferInfo);
    // Serialize message field [z]
    bufferInfo = _serializer.float32(obj.z, bufferInfo);
    // Serialize message field [rot_x]
    bufferInfo = _serializer.float32(obj.rot_x, bufferInfo);
    // Serialize message field [rot_y]
    bufferInfo = _serializer.float32(obj.rot_y, bufferInfo);
    // Serialize message field [rot_z]
    bufferInfo = _serializer.float32(obj.rot_z, bufferInfo);
    // Serialize message field [j1]
    bufferInfo = _serializer.float32(obj.j1, bufferInfo);
    // Serialize message field [j2]
    bufferInfo = _serializer.float32(obj.j2, bufferInfo);
    // Serialize message field [j3]
    bufferInfo = _serializer.float32(obj.j3, bufferInfo);
    // Serialize message field [j4]
    bufferInfo = _serializer.float32(obj.j4, bufferInfo);
    // Serialize message field [j5]
    bufferInfo = _serializer.float32(obj.j5, bufferInfo);
    // Serialize message field [j6]
    bufferInfo = _serializer.float32(obj.j6, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type MelfaCommand
    let tmp;
    let len;
    let data = new MelfaCommand();
    // Deserialize message field [iControl_type]
    tmp = _deserializer.int32(buffer);
    data.iControl_type = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [Type_Monitor1]
    tmp = _deserializer.char(buffer);
    data.Type_Monitor1 = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [Type_Monitor2]
    tmp = _deserializer.char(buffer);
    data.Type_Monitor2 = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [Type_Monitor3]
    tmp = _deserializer.char(buffer);
    data.Type_Monitor3 = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [Type_Monitor4]
    tmp = _deserializer.char(buffer);
    data.Type_Monitor4 = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [x]
    tmp = _deserializer.float32(buffer);
    data.x = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [y]
    tmp = _deserializer.float32(buffer);
    data.y = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [z]
    tmp = _deserializer.float32(buffer);
    data.z = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [rot_x]
    tmp = _deserializer.float32(buffer);
    data.rot_x = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [rot_y]
    tmp = _deserializer.float32(buffer);
    data.rot_y = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [rot_z]
    tmp = _deserializer.float32(buffer);
    data.rot_z = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [j1]
    tmp = _deserializer.float32(buffer);
    data.j1 = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [j2]
    tmp = _deserializer.float32(buffer);
    data.j2 = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [j3]
    tmp = _deserializer.float32(buffer);
    data.j3 = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [j4]
    tmp = _deserializer.float32(buffer);
    data.j4 = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [j5]
    tmp = _deserializer.float32(buffer);
    data.j5 = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [j6]
    tmp = _deserializer.float32(buffer);
    data.j6 = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'mitsubishi_melfa/MelfaCommand';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '20d55ef6218f6462a4e3a3d41d3d4072';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 iControl_type
    char Type_Monitor1
    char Type_Monitor2
    char Type_Monitor3
    char Type_Monitor4
    float32 x
    float32 y
    float32 z 
    float32 rot_x
    float32 rot_y
    float32 rot_z
    float32 j1
    float32 j2
    float32 j3 
    float32 j4
    float32 j5
    float32 j6
    
    `;
  }

};

module.exports = MelfaCommand;
