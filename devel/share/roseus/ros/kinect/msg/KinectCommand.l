;; Auto-generated. Do not edit!


(when (boundp 'kinect::KinectCommand)
  (if (not (find-package "KINECT"))
    (make-package "KINECT"))
  (shadow 'KinectCommand (find-package "KINECT")))
(unless (find-package "KINECT::KINECTCOMMAND")
  (make-package "KINECT::KINECTCOMMAND"))

(in-package "ROS")
;;//! \htmlinclude KinectCommand.msg.html


(defclass kinect::KinectCommand
  :super ros::object
  :slots (_start _objNum ))

(defmethod kinect::KinectCommand
  (:init
   (&key
    ((:start __start) 0)
    ((:objNum __objNum) 0)
    )
   (send-super :init)
   (setq _start (round __start))
   (setq _objNum (round __objNum))
   self)
  (:start
   (&optional __start)
   (if __start (setq _start __start)) _start)
  (:objNum
   (&optional __objNum)
   (if __objNum (setq _objNum __objNum)) _objNum)
  (:serialization-length
   ()
   (+
    ;; uint8 _start
    1
    ;; uint8 _objNum
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _start
       (write-byte _start s)
     ;; uint8 _objNum
       (write-byte _objNum s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _start
     (setq _start (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _objNum
     (setq _objNum (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get kinect::KinectCommand :md5sum-) "c2394b59af5274a47f8538009ed2d9f9")
(setf (get kinect::KinectCommand :datatype-) "kinect/KinectCommand")
(setf (get kinect::KinectCommand :definition-)
      "uint8 start
uint8 objNum

")



(provide :kinect/KinectCommand "c2394b59af5274a47f8538009ed2d9f9")


