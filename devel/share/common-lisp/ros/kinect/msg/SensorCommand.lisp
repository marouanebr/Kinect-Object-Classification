; Auto-generated. Do not edit!


(cl:in-package kinect-msg)


;//! \htmlinclude SensorCommand.msg.html

(cl:defclass <SensorCommand> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (begin
    :reader begin
    :initarg :begin
    :type cl:fixnum
    :initform 0)
   (finish
    :reader finish
    :initarg :finish
    :type cl:fixnum
    :initform 0))
)

(cl:defclass SensorCommand (<SensorCommand>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SensorCommand>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SensorCommand)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kinect-msg:<SensorCommand> is deprecated: use kinect-msg:SensorCommand instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <SensorCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect-msg:id-val is deprecated.  Use kinect-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'begin-val :lambda-list '(m))
(cl:defmethod begin-val ((m <SensorCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect-msg:begin-val is deprecated.  Use kinect-msg:begin instead.")
  (begin m))

(cl:ensure-generic-function 'finish-val :lambda-list '(m))
(cl:defmethod finish-val ((m <SensorCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect-msg:finish-val is deprecated.  Use kinect-msg:finish instead.")
  (finish m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SensorCommand>) ostream)
  "Serializes a message object of type '<SensorCommand>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'begin)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'finish)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SensorCommand>) istream)
  "Deserializes a message object of type '<SensorCommand>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'begin)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'finish)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SensorCommand>)))
  "Returns string type for a message object of type '<SensorCommand>"
  "kinect/SensorCommand")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SensorCommand)))
  "Returns string type for a message object of type 'SensorCommand"
  "kinect/SensorCommand")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SensorCommand>)))
  "Returns md5sum for a message object of type '<SensorCommand>"
  "25eb2b19b6f929cb1994bd90cac57780")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SensorCommand)))
  "Returns md5sum for a message object of type 'SensorCommand"
  "25eb2b19b6f929cb1994bd90cac57780")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SensorCommand>)))
  "Returns full string definition for message of type '<SensorCommand>"
  (cl:format cl:nil "uint8 id~%uint8 begin~%uint8 finish~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SensorCommand)))
  "Returns full string definition for message of type 'SensorCommand"
  (cl:format cl:nil "uint8 id~%uint8 begin~%uint8 finish~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SensorCommand>))
  (cl:+ 0
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SensorCommand>))
  "Converts a ROS message object to a list"
  (cl:list 'SensorCommand
    (cl:cons ':id (id msg))
    (cl:cons ':begin (begin msg))
    (cl:cons ':finish (finish msg))
))
