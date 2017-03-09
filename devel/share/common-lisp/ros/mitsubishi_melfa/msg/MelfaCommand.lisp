; Auto-generated. Do not edit!


(cl:in-package mitsubishi_melfa-msg)


;//! \htmlinclude MelfaCommand.msg.html

(cl:defclass <MelfaCommand> (roslisp-msg-protocol:ros-message)
  ((iControl_type
    :reader iControl_type
    :initarg :iControl_type
    :type cl:integer
    :initform 0)
   (Type_Monitor1
    :reader Type_Monitor1
    :initarg :Type_Monitor1
    :type cl:integer
    :initform 0)
   (Type_Monitor2
    :reader Type_Monitor2
    :initarg :Type_Monitor2
    :type cl:integer
    :initform 0)
   (Type_Monitor3
    :reader Type_Monitor3
    :initarg :Type_Monitor3
    :type cl:integer
    :initform 0)
   (Type_Monitor4
    :reader Type_Monitor4
    :initarg :Type_Monitor4
    :type cl:integer
    :initform 0)
   (x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (z
    :reader z
    :initarg :z
    :type cl:float
    :initform 0.0)
   (rot_x
    :reader rot_x
    :initarg :rot_x
    :type cl:float
    :initform 0.0)
   (rot_y
    :reader rot_y
    :initarg :rot_y
    :type cl:float
    :initform 0.0)
   (rot_z
    :reader rot_z
    :initarg :rot_z
    :type cl:float
    :initform 0.0)
   (j1
    :reader j1
    :initarg :j1
    :type cl:float
    :initform 0.0)
   (j2
    :reader j2
    :initarg :j2
    :type cl:float
    :initform 0.0)
   (j3
    :reader j3
    :initarg :j3
    :type cl:float
    :initform 0.0)
   (j4
    :reader j4
    :initarg :j4
    :type cl:float
    :initform 0.0)
   (j5
    :reader j5
    :initarg :j5
    :type cl:float
    :initform 0.0)
   (j6
    :reader j6
    :initarg :j6
    :type cl:float
    :initform 0.0))
)

(cl:defclass MelfaCommand (<MelfaCommand>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MelfaCommand>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MelfaCommand)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mitsubishi_melfa-msg:<MelfaCommand> is deprecated: use mitsubishi_melfa-msg:MelfaCommand instead.")))

(cl:ensure-generic-function 'iControl_type-val :lambda-list '(m))
(cl:defmethod iControl_type-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:iControl_type-val is deprecated.  Use mitsubishi_melfa-msg:iControl_type instead.")
  (iControl_type m))

(cl:ensure-generic-function 'Type_Monitor1-val :lambda-list '(m))
(cl:defmethod Type_Monitor1-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:Type_Monitor1-val is deprecated.  Use mitsubishi_melfa-msg:Type_Monitor1 instead.")
  (Type_Monitor1 m))

(cl:ensure-generic-function 'Type_Monitor2-val :lambda-list '(m))
(cl:defmethod Type_Monitor2-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:Type_Monitor2-val is deprecated.  Use mitsubishi_melfa-msg:Type_Monitor2 instead.")
  (Type_Monitor2 m))

(cl:ensure-generic-function 'Type_Monitor3-val :lambda-list '(m))
(cl:defmethod Type_Monitor3-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:Type_Monitor3-val is deprecated.  Use mitsubishi_melfa-msg:Type_Monitor3 instead.")
  (Type_Monitor3 m))

(cl:ensure-generic-function 'Type_Monitor4-val :lambda-list '(m))
(cl:defmethod Type_Monitor4-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:Type_Monitor4-val is deprecated.  Use mitsubishi_melfa-msg:Type_Monitor4 instead.")
  (Type_Monitor4 m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:x-val is deprecated.  Use mitsubishi_melfa-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:y-val is deprecated.  Use mitsubishi_melfa-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:z-val is deprecated.  Use mitsubishi_melfa-msg:z instead.")
  (z m))

(cl:ensure-generic-function 'rot_x-val :lambda-list '(m))
(cl:defmethod rot_x-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:rot_x-val is deprecated.  Use mitsubishi_melfa-msg:rot_x instead.")
  (rot_x m))

(cl:ensure-generic-function 'rot_y-val :lambda-list '(m))
(cl:defmethod rot_y-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:rot_y-val is deprecated.  Use mitsubishi_melfa-msg:rot_y instead.")
  (rot_y m))

(cl:ensure-generic-function 'rot_z-val :lambda-list '(m))
(cl:defmethod rot_z-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:rot_z-val is deprecated.  Use mitsubishi_melfa-msg:rot_z instead.")
  (rot_z m))

(cl:ensure-generic-function 'j1-val :lambda-list '(m))
(cl:defmethod j1-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:j1-val is deprecated.  Use mitsubishi_melfa-msg:j1 instead.")
  (j1 m))

(cl:ensure-generic-function 'j2-val :lambda-list '(m))
(cl:defmethod j2-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:j2-val is deprecated.  Use mitsubishi_melfa-msg:j2 instead.")
  (j2 m))

(cl:ensure-generic-function 'j3-val :lambda-list '(m))
(cl:defmethod j3-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:j3-val is deprecated.  Use mitsubishi_melfa-msg:j3 instead.")
  (j3 m))

(cl:ensure-generic-function 'j4-val :lambda-list '(m))
(cl:defmethod j4-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:j4-val is deprecated.  Use mitsubishi_melfa-msg:j4 instead.")
  (j4 m))

(cl:ensure-generic-function 'j5-val :lambda-list '(m))
(cl:defmethod j5-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:j5-val is deprecated.  Use mitsubishi_melfa-msg:j5 instead.")
  (j5 m))

(cl:ensure-generic-function 'j6-val :lambda-list '(m))
(cl:defmethod j6-val ((m <MelfaCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mitsubishi_melfa-msg:j6-val is deprecated.  Use mitsubishi_melfa-msg:j6 instead.")
  (j6 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MelfaCommand>) ostream)
  "Serializes a message object of type '<MelfaCommand>"
  (cl:let* ((signed (cl:slot-value msg 'iControl_type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Type_Monitor1)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Type_Monitor2)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Type_Monitor3)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Type_Monitor4)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rot_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rot_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rot_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'j1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'j2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'j3))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'j4))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'j5))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'j6))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MelfaCommand>) istream)
  "Deserializes a message object of type '<MelfaCommand>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'iControl_type) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Type_Monitor1)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Type_Monitor2)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Type_Monitor3)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Type_Monitor4)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rot_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rot_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rot_z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'j1) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'j2) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'j3) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'j4) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'j5) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'j6) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MelfaCommand>)))
  "Returns string type for a message object of type '<MelfaCommand>"
  "mitsubishi_melfa/MelfaCommand")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MelfaCommand)))
  "Returns string type for a message object of type 'MelfaCommand"
  "mitsubishi_melfa/MelfaCommand")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MelfaCommand>)))
  "Returns md5sum for a message object of type '<MelfaCommand>"
  "20d55ef6218f6462a4e3a3d41d3d4072")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MelfaCommand)))
  "Returns md5sum for a message object of type 'MelfaCommand"
  "20d55ef6218f6462a4e3a3d41d3d4072")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MelfaCommand>)))
  "Returns full string definition for message of type '<MelfaCommand>"
  (cl:format cl:nil "int32 iControl_type~%char Type_Monitor1~%char Type_Monitor2~%char Type_Monitor3~%char Type_Monitor4~%float32 x~%float32 y~%float32 z ~%float32 rot_x~%float32 rot_y~%float32 rot_z~%float32 j1~%float32 j2~%float32 j3 ~%float32 j4~%float32 j5~%float32 j6~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MelfaCommand)))
  "Returns full string definition for message of type 'MelfaCommand"
  (cl:format cl:nil "int32 iControl_type~%char Type_Monitor1~%char Type_Monitor2~%char Type_Monitor3~%char Type_Monitor4~%float32 x~%float32 y~%float32 z ~%float32 rot_x~%float32 rot_y~%float32 rot_z~%float32 j1~%float32 j2~%float32 j3 ~%float32 j4~%float32 j5~%float32 j6~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MelfaCommand>))
  (cl:+ 0
     4
     1
     1
     1
     1
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MelfaCommand>))
  "Converts a ROS message object to a list"
  (cl:list 'MelfaCommand
    (cl:cons ':iControl_type (iControl_type msg))
    (cl:cons ':Type_Monitor1 (Type_Monitor1 msg))
    (cl:cons ':Type_Monitor2 (Type_Monitor2 msg))
    (cl:cons ':Type_Monitor3 (Type_Monitor3 msg))
    (cl:cons ':Type_Monitor4 (Type_Monitor4 msg))
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
    (cl:cons ':rot_x (rot_x msg))
    (cl:cons ':rot_y (rot_y msg))
    (cl:cons ':rot_z (rot_z msg))
    (cl:cons ':j1 (j1 msg))
    (cl:cons ':j2 (j2 msg))
    (cl:cons ':j3 (j3 msg))
    (cl:cons ':j4 (j4 msg))
    (cl:cons ':j5 (j5 msg))
    (cl:cons ':j6 (j6 msg))
))
