// Auto-generated. Do not edit!

// (in-package mitsubishi_melfa.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class PositionCommand {
  constructor() {
    this.x = 0.0;
    this.y = 0.0;
    this.z = 0.0;
    this.velocity_factor = 0.0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type PositionCommand
    // Serialize message field [x]
    bufferInfo = _serializer.float32(obj.x, bufferInfo);
    // Serialize message field [y]
    bufferInfo = _serializer.float32(obj.y, bufferInfo);
    // Serialize message field [z]
    bufferInfo = _serializer.float32(obj.z, bufferInfo);
    // Serialize message field [velocity_factor]
    bufferInfo = _serializer.float32(obj.velocity_factor, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type PositionCommand
    let tmp;
    let len;
    let data = new PositionCommand();
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
    // Deserialize message field [velocity_factor]
    tmp = _deserializer.float32(buffer);
    data.velocity_factor = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'mitsubishi_melfa/PositionCommand';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '63a595af437927f7d77813a9c7f45b16';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 x
    float32 y
    float32 z 
    float32 velocity_factor
    
    `;
  }

};

module.exports = PositionCommand;
