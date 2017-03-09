;; Auto-generated. Do not edit!


(when (boundp 'kinect::SensorCommand)
  (if (not (find-package "KINECT"))
    (make-package "KINECT"))
  (shadow 'SensorCommand (find-package "KINECT")))
(unless (find-package "KINECT::SENSORCOMMAND")
  (make-package "KINECT::SENSORCOMMAND"))

(in-package "ROS")
;;//! \htmlinclude SensorCommand.msg.html


(defclass kinect::SensorCommand
  :super ros::object
  :slots (_id _begin _finish ))

(defmethod kinect::SensorCommand
  (:init
   (&key
    ((:id __id) 0)
    ((:begin __begin) 0)
    ((:finish __finish) 0)
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _begin (round __begin))
   (setq _finish (round __finish))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:begin
   (&optional __begin)
   (if __begin (setq _begin __begin)) _begin)
  (:finish
   (&optional __finish)
   (if __finish (setq _finish __finish)) _finish)
  (:serialization-length
   ()
   (+
    ;; uint8 _id
    1
    ;; uint8 _begin
    1
    ;; uint8 _finish
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _id
       (write-byte _id s)
     ;; uint8 _begin
       (write-byte _begin s)
     ;; uint8 _finish
       (write-byte _finish s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _begin
     (setq _begin (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _finish
     (setq _finish (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get kinect::SensorCommand :md5sum-) "25eb2b19b6f929cb1994bd90cac57780")
(setf (get kinect::SensorCommand :datatype-) "kinect/SensorCommand")
(setf (get kinect::SensorCommand :definition-)
      "uint8 id
uint8 begin
uint8 finish

")



(provide :kinect/SensorCommand "25eb2b19b6f929cb1994bd90cac57780")


