;; Auto-generated. Do not edit!


(when (boundp 'mitsubishi_melfa::PositionCommand)
  (if (not (find-package "MITSUBISHI_MELFA"))
    (make-package "MITSUBISHI_MELFA"))
  (shadow 'PositionCommand (find-package "MITSUBISHI_MELFA")))
(unless (find-package "MITSUBISHI_MELFA::POSITIONCOMMAND")
  (make-package "MITSUBISHI_MELFA::POSITIONCOMMAND"))

(in-package "ROS")
;;//! \htmlinclude PositionCommand.msg.html


(defclass mitsubishi_melfa::PositionCommand
  :super ros::object
  :slots (_x _y _z _velocity_factor ))

(defmethod mitsubishi_melfa::PositionCommand
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:velocity_factor __velocity_factor) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _velocity_factor (float __velocity_factor))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:velocity_factor
   (&optional __velocity_factor)
   (if __velocity_factor (setq _velocity_factor __velocity_factor)) _velocity_factor)
  (:serialization-length
   ()
   (+
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; float32 _z
    4
    ;; float32 _velocity_factor
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _z
       (sys::poke _z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _velocity_factor
       (sys::poke _velocity_factor (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _z
     (setq _z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _velocity_factor
     (setq _velocity_factor (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get mitsubishi_melfa::PositionCommand :md5sum-) "63a595af437927f7d77813a9c7f45b16")
(setf (get mitsubishi_melfa::PositionCommand :datatype-) "mitsubishi_melfa/PositionCommand")
(setf (get mitsubishi_melfa::PositionCommand :definition-)
      "float32 x
float32 y
float32 z 
float32 velocity_factor

")



(provide :mitsubishi_melfa/PositionCommand "63a595af437927f7d77813a9c7f45b16")


