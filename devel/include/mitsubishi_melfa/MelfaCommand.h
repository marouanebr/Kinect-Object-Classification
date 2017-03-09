// Generated by gencpp from file mitsubishi_melfa/MelfaCommand.msg
// DO NOT EDIT!


#ifndef MITSUBISHI_MELFA_MESSAGE_MELFACOMMAND_H
#define MITSUBISHI_MELFA_MESSAGE_MELFACOMMAND_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace mitsubishi_melfa
{
template <class ContainerAllocator>
struct MelfaCommand_
{
  typedef MelfaCommand_<ContainerAllocator> Type;

  MelfaCommand_()
    : iControl_type(0)
    , Type_Monitor1(0)
    , Type_Monitor2(0)
    , Type_Monitor3(0)
    , Type_Monitor4(0)
    , x(0.0)
    , y(0.0)
    , z(0.0)
    , rot_x(0.0)
    , rot_y(0.0)
    , rot_z(0.0)
    , j1(0.0)
    , j2(0.0)
    , j3(0.0)
    , j4(0.0)
    , j5(0.0)
    , j6(0.0)  {
    }
  MelfaCommand_(const ContainerAllocator& _alloc)
    : iControl_type(0)
    , Type_Monitor1(0)
    , Type_Monitor2(0)
    , Type_Monitor3(0)
    , Type_Monitor4(0)
    , x(0.0)
    , y(0.0)
    , z(0.0)
    , rot_x(0.0)
    , rot_y(0.0)
    , rot_z(0.0)
    , j1(0.0)
    , j2(0.0)
    , j3(0.0)
    , j4(0.0)
    , j5(0.0)
    , j6(0.0)  {
  (void)_alloc;
    }



   typedef int32_t _iControl_type_type;
  _iControl_type_type iControl_type;

   typedef uint8_t _Type_Monitor1_type;
  _Type_Monitor1_type Type_Monitor1;

   typedef uint8_t _Type_Monitor2_type;
  _Type_Monitor2_type Type_Monitor2;

   typedef uint8_t _Type_Monitor3_type;
  _Type_Monitor3_type Type_Monitor3;

   typedef uint8_t _Type_Monitor4_type;
  _Type_Monitor4_type Type_Monitor4;

   typedef float _x_type;
  _x_type x;

   typedef float _y_type;
  _y_type y;

   typedef float _z_type;
  _z_type z;

   typedef float _rot_x_type;
  _rot_x_type rot_x;

   typedef float _rot_y_type;
  _rot_y_type rot_y;

   typedef float _rot_z_type;
  _rot_z_type rot_z;

   typedef float _j1_type;
  _j1_type j1;

   typedef float _j2_type;
  _j2_type j2;

   typedef float _j3_type;
  _j3_type j3;

   typedef float _j4_type;
  _j4_type j4;

   typedef float _j5_type;
  _j5_type j5;

   typedef float _j6_type;
  _j6_type j6;




  typedef boost::shared_ptr< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> const> ConstPtr;

}; // struct MelfaCommand_

typedef ::mitsubishi_melfa::MelfaCommand_<std::allocator<void> > MelfaCommand;

typedef boost::shared_ptr< ::mitsubishi_melfa::MelfaCommand > MelfaCommandPtr;
typedef boost::shared_ptr< ::mitsubishi_melfa::MelfaCommand const> MelfaCommandConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mitsubishi_melfa

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'mitsubishi_melfa': ['/home/marouane/Documents/fp_workspace/rosCode/src/mitsubishi_melfa/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> >
{
  static const char* value()
  {
    return "20d55ef6218f6462a4e3a3d41d3d4072";
  }

  static const char* value(const ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x20d55ef6218f6462ULL;
  static const uint64_t static_value2 = 0xa4e3a3d41d3d4072ULL;
};

template<class ContainerAllocator>
struct DataType< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mitsubishi_melfa/MelfaCommand";
  }

  static const char* value(const ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 iControl_type\n\
char Type_Monitor1\n\
char Type_Monitor2\n\
char Type_Monitor3\n\
char Type_Monitor4\n\
float32 x\n\
float32 y\n\
float32 z \n\
float32 rot_x\n\
float32 rot_y\n\
float32 rot_z\n\
float32 j1\n\
float32 j2\n\
float32 j3 \n\
float32 j4\n\
float32 j5\n\
float32 j6\n\
";
  }

  static const char* value(const ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.iControl_type);
      stream.next(m.Type_Monitor1);
      stream.next(m.Type_Monitor2);
      stream.next(m.Type_Monitor3);
      stream.next(m.Type_Monitor4);
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.z);
      stream.next(m.rot_x);
      stream.next(m.rot_y);
      stream.next(m.rot_z);
      stream.next(m.j1);
      stream.next(m.j2);
      stream.next(m.j3);
      stream.next(m.j4);
      stream.next(m.j5);
      stream.next(m.j6);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct MelfaCommand_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mitsubishi_melfa::MelfaCommand_<ContainerAllocator>& v)
  {
    s << indent << "iControl_type: ";
    Printer<int32_t>::stream(s, indent + "  ", v.iControl_type);
    s << indent << "Type_Monitor1: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.Type_Monitor1);
    s << indent << "Type_Monitor2: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.Type_Monitor2);
    s << indent << "Type_Monitor3: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.Type_Monitor3);
    s << indent << "Type_Monitor4: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.Type_Monitor4);
    s << indent << "x: ";
    Printer<float>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<float>::stream(s, indent + "  ", v.y);
    s << indent << "z: ";
    Printer<float>::stream(s, indent + "  ", v.z);
    s << indent << "rot_x: ";
    Printer<float>::stream(s, indent + "  ", v.rot_x);
    s << indent << "rot_y: ";
    Printer<float>::stream(s, indent + "  ", v.rot_y);
    s << indent << "rot_z: ";
    Printer<float>::stream(s, indent + "  ", v.rot_z);
    s << indent << "j1: ";
    Printer<float>::stream(s, indent + "  ", v.j1);
    s << indent << "j2: ";
    Printer<float>::stream(s, indent + "  ", v.j2);
    s << indent << "j3: ";
    Printer<float>::stream(s, indent + "  ", v.j3);
    s << indent << "j4: ";
    Printer<float>::stream(s, indent + "  ", v.j4);
    s << indent << "j5: ";
    Printer<float>::stream(s, indent + "  ", v.j5);
    s << indent << "j6: ";
    Printer<float>::stream(s, indent + "  ", v.j6);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MITSUBISHI_MELFA_MESSAGE_MELFACOMMAND_H