
(cl:in-package :asdf)

(defsystem "lunarNXT-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Order" :depends-on ("_package_Order"))
    (:file "_package_Order" :depends-on ("_package"))
  ))