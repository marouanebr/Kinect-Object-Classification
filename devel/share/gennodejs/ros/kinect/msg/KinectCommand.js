// Auto-generated. Do not edit!

// (in-package kinect.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class KinectCommand {
  constructor() {
    this.start = 0;
    this.objNum = 0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type KinectCommand
    // Serialize message field [start]
    bufferInfo = _serializer.uint8(obj.start, bufferInfo);
    // Serialize message field [objNum]
    bufferInfo = _serializer.uint8(obj.objNum, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type KinectCommand
    let tmp;
    let len;
    let data = new KinectCommand();
    // Deserialize message field [start]
    tmp = _deserializer.uint8(buffer);
    data.start = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [objNum]
    tmp = _deserializer.uint8(buffer);
    data.objNum = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'kinect/KinectCommand';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c2394b59af5274a47f8538009ed2d9f9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 start
    uint8 objNum
    
    `;
  }

};

module.exports = KinectCommand;
