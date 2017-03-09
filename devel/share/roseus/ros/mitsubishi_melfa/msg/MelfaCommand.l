;; Auto-generated. Do not edit!


(when (boundp 'mitsubishi_melfa::MelfaCommand)
  (if (not (find-package "MITSUBISHI_MELFA"))
    (make-package "MITSUBISHI_MELFA"))
  (shadow 'MelfaCommand (find-package "MITSUBISHI_MELFA")))
(unless (find-package "MITSUBISHI_MELFA::MELFACOMMAND")
  (make-package "MITSUBISHI_MELFA::MELFACOMMAND"))

(in-package "ROS")
;;//! \htmlinclude MelfaCommand.msg.html


(defclass mitsubishi_melfa::MelfaCommand
  :super ros::object
  :slots (_iControl_type _Type_Monitor1 _Type_Monitor2 _Type_Monitor3 _Type_Monitor4 _x _y _z _rot_x _rot_y _rot_z _j1 _j2 _j3 _j4 _j5 _j6 ))

(defmethod mitsubishi_melfa::MelfaCommand
  (:init
   (&key
    ((:iControl_type __iControl_type) 0)
    ((:Type_Monitor1 __Type_Monitor1) 0)
    ((:Type_Monitor2 __Type_Monitor2) 0)
    ((:Type_Monitor3 __Type_Monitor3) 0)
    ((:Type_Monitor4 __Type_Monitor4) 0)
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:rot_x __rot_x) 0.0)
    ((:rot_y __rot_y) 0.0)
    ((:rot_z __rot_z) 0.0)
    ((:j1 __j1) 0.0)
    ((:j2 __j2) 0.0)
    ((:j3 __j3) 0.0)
    ((:j4 __j4) 0.0)
    ((:j5 __j5) 0.0)
    ((:j6 __j6) 0.0)
    )
   (send-super :init)
   (setq _iControl_type (round __iControl_type))
   (setq _Type_Monitor1 (round __Type_Monitor1))
   (setq _Type_Monitor2 (round __Type_Monitor2))
   (setq _Type_Monitor3 (round __Type_Monitor3))
   (setq _Type_Monitor4 (round __Type_Monitor4))
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _rot_x (float __rot_x))
   (setq _rot_y (float __rot_y))
   (setq _rot_z (float __rot_z))
   (setq _j1 (float __j1))
   (setq _j2 (float __j2))
   (setq _j3 (float __j3))
   (setq _j4 (float __j4))
   (setq _j5 (float __j5))
   (setq _j6 (float __j6))
   self)
  (:iControl_type
   (&optional __iControl_type)
   (if __iControl_type (setq _iControl_type __iControl_type)) _iControl_type)
  (:Type_Monitor1
   (&optional __Type_Monitor1)
   (if __Type_Monitor1 (setq _Type_Monitor1 __Type_Monitor1)) _Type_Monitor1)
  (:Type_Monitor2
   (&optional __Type_Monitor2)
   (if __Type_Monitor2 (setq _Type_Monitor2 __Type_Monitor2)) _Type_Monitor2)
  (:Type_Monitor3
   (&optional __Type_Monitor3)
   (if __Type_Monitor3 (setq _Type_Monitor3 __Type_Monitor3)) _Type_Monitor3)
  (:Type_Monitor4
   (&optional __Type_Monitor4)
   (if __Type_Monitor4 (setq _Type_Monitor4 __Type_Monitor4)) _Type_Monitor4)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:rot_x
   (&optional __rot_x)
   (if __rot_x (setq _rot_x __rot_x)) _rot_x)
  (:rot_y
   (&optional __rot_y)
   (if __rot_y (setq _rot_y __rot_y)) _rot_y)
  (:rot_z
   (&optional __rot_z)
   (if __rot_z (setq _rot_z __rot_z)) _rot_z)
  (:j1
   (&optional __j1)
   (if __j1 (setq _j1 __j1)) _j1)
  (:j2
   (&optional __j2)
   (if __j2 (setq _j2 __j2)) _j2)
  (:j3
   (&optional __j3)
   (if __j3 (setq _j3 __j3)) _j3)
  (:j4
   (&optional __j4)
   (if __j4 (setq _j4 __j4)) _j4)
  (:j5
   (&optional __j5)
   (if __j5 (setq _j5 __j5)) _j5)
  (:j6
   (&optional __j6)
   (if __j6 (setq _j6 __j6)) _j6)
  (:serialization-length
   ()
   (+
    ;; int32 _iControl_type
    4
    ;; char _Type_Monitor1
    1
    ;; char _Type_Monitor2
    1
    ;; char _Type_Monitor3
    1
    ;; char _Type_Monitor4
    1
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; float32 _z
    4
    ;; float32 _rot_x
    4
    ;; float32 _rot_y
    4
    ;; float32 _rot_z
    4
    ;; float32 _j1
    4
    ;; float32 _j2
    4
    ;; float32 _j3
    4
    ;; float32 _j4
    4
    ;; float32 _j5
    4
    ;; float32 _j6
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _iControl_type
       (write-long _iControl_type s)
     ;; char _Type_Monitor1
       (write-byte _Type_Monitor1 s)
     ;; char _Type_Monitor2
       (write-byte _Type_Monitor2 s)
     ;; char _Type_Monitor3
       (write-byte _Type_Monitor3 s)
     ;; char _Type_Monitor4
       (write-byte _Type_Monitor4 s)
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _z
       (sys::poke _z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rot_x
       (sys::poke _rot_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rot_y
       (sys::poke _rot_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rot_z
       (sys::poke _rot_z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _j1
       (sys::poke _j1 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _j2
       (sys::poke _j2 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _j3
       (sys::poke _j3 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _j4
       (sys::poke _j4 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _j5
       (sys::poke _j5 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _j6
       (sys::poke _j6 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _iControl_type
     (setq _iControl_type (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; char _Type_Monitor1
     (setq _Type_Monitor1 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _Type_Monitor2
     (setq _Type_Monitor2 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _Type_Monitor3
     (setq _Type_Monitor3 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _Type_Monitor4
     (setq _Type_Monitor4 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _z
     (setq _z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rot_x
     (setq _rot_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rot_y
     (setq _rot_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rot_z
     (setq _rot_z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _j1
     (setq _j1 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _j2
     (setq _j2 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _j3
     (setq _j3 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _j4
     (setq _j4 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _j5
     (setq _j5 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _j6
     (setq _j6 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get mitsubishi_melfa::MelfaCommand :md5sum-) "20d55ef6218f6462a4e3a3d41d3d4072")
(setf (get mitsubishi_melfa::MelfaCommand :datatype-) "mitsubishi_melfa/MelfaCommand")
(setf (get mitsubishi_melfa::MelfaCommand :definition-)
      "int32 iControl_type
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

")



(provide :mitsubishi_melfa/MelfaCommand "20d55ef6218f6462a4e3a3d41d3d4072")

