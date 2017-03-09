; Auto-generated. Do not edit!


(cl:in-package kinect-msg)


;//! \htmlinclude KinectCommand.msg.html

(cl:defclass <KinectCommand> (roslisp-msg-protocol:ros-message)
  ((start
    :reader start
    :initarg :start
    :type cl:fixnum
    :initform 0)
   (objNum
    :reader objNum
    :initarg :objNum
    :type cl:fixnum
    :initform 0))
)

(cl:defclass KinectCommand (<KinectCommand>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <KinectCommand>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'KinectCommand)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kinect-msg:<KinectCommand> is deprecated: use kinect-msg:KinectCommand instead.")))

(cl:ensure-generic-function 'start-val :lambda-list '(m))
(cl:defmethod start-val ((m <KinectCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect-msg:start-val is deprecated.  Use kinect-msg:start instead.")
  (start m))

(cl:ensure-generic-function 'objNum-val :lambda-list '(m))
(cl:defmethod objNum-val ((m <KinectCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect-msg:objNum-val is deprecated.  Use kinect-msg:objNum instead.")
  (objNum m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <KinectCommand>) ostream)
  "Serializes a message object of type '<KinectCommand>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'start)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'objNum)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <KinectCommand>) istream)
  "Deserializes a message object of type '<KinectCommand>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'start)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'objNum)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<KinectCommand>)))
  "Returns string type for a message object of type '<KinectCommand>"
  "kinect/KinectCommand")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'KinectCommand)))
  "Returns string type for a message object of type 'KinectCommand"
  "kinect/KinectCommand")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<KinectCommand>)))
  "Returns md5sum for a message object of type '<KinectCommand>"
  "c2394b59af5274a47f8538009ed2d9f9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'KinectCommand)))
  "Returns md5sum for a message object of type 'KinectCommand"
  "c2394b59af5274a47f8538009ed2d9f9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<KinectCommand>)))
  "Returns full string definition for message of type '<KinectCommand>"
  (cl:format cl:nil "uint8 start~%uint8 objNum~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'KinectCommand)))
  "Returns full string definition for message of type 'KinectCommand"
  (cl:format cl:nil "uint8 start~%uint8 objNum~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <KinectCommand>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <KinectCommand>))
  "Converts a ROS message object to a list"
  (cl:list 'KinectCommand
    (cl:cons ':start (start msg))
    (cl:cons ':objNum (objNum msg))
))
