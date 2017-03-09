// Auto-generated. Do not edit!

// (in-package kinect.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class SensorCommand {
  constructor() {
    this.id = 0;
    this.begin = 0;
    this.finish = 0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type SensorCommand
    // Serialize message field [id]
    bufferInfo = _serializer.uint8(obj.id, bufferInfo);
    // Serialize message field [begin]
    bufferInfo = _serializer.uint8(obj.begin, bufferInfo);
    // Serialize message field [finish]
    bufferInfo = _serializer.uint8(obj.finish, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type SensorCommand
    let tmp;
    let len;
    let data = new SensorCommand();
    // Deserialize message field [id]
    tmp = _deserializer.uint8(buffer);
    data.id = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [begin]
    tmp = _deserializer.uint8(buffer);
    data.begin = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [finish]
    tmp = _deserializer.uint8(buffer);
    data.finish = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'kinect/SensorCommand';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '25eb2b19b6f929cb1994bd90cac57780';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 id
    uint8 begin
    uint8 finish
    
    `;
  }

};

module.exports = SensorCommand;
