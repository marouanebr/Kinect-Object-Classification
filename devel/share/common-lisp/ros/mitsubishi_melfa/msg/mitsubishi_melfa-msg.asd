
(cl:in-package :asdf)

(defsystem "mitsubishi_melfa-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "MelfaCommand" :depends-on ("_package_MelfaCommand"))
    (:file "_package_MelfaCommand" :depends-on ("_package"))
    (:file "PositionCommand" :depends-on ("_package_PositionCommand"))
    (:file "_package_PositionCommand" :depends-on ("_package"))
  ))