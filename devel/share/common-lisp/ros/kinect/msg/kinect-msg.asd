
(cl:in-package :asdf)

(defsystem "kinect-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "KinectCommand" :depends-on ("_package_KinectCommand"))
    (:file "_package_KinectCommand" :depends-on ("_package"))
    (:file "SensorCommand" :depends-on ("_package_SensorCommand"))
    (:file "_package_SensorCommand" :depends-on ("_package"))
  ))