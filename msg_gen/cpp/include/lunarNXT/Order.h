/* Auto-generated by genmsg_cpp for file /home/a106184/ros_workspace/lunarNXT/msg/Order.msg */
#ifndef LUNARNXT_MESSAGE_ORDER_H
#define LUNARNXT_MESSAGE_ORDER_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace lunarNXT
{
template <class ContainerAllocator>
struct Order_ {
  typedef Order_<ContainerAllocator> Type;

  Order_()
  : order()
  , value(0.0)
  {
  }

  Order_(const ContainerAllocator& _alloc)
  : order(_alloc)
  , value(0.0)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _order_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  order;

  typedef double _value_type;
  double value;


private:
  static const char* __s_getDataType_() { return "lunarNXT/Order"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "37fcf37ef978840f2eb907ffb27c7c3c"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "string order\n\
float64 value\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, order);
    ros::serialization::serialize(stream, value);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, order);
    ros::serialization::deserialize(stream, value);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(order);
    size += ros::serialization::serializationLength(value);
    return size;
  }

  typedef boost::shared_ptr< ::lunarNXT::Order_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::lunarNXT::Order_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct Order
typedef  ::lunarNXT::Order_<std::allocator<void> > Order;

typedef boost::shared_ptr< ::lunarNXT::Order> OrderPtr;
typedef boost::shared_ptr< ::lunarNXT::Order const> OrderConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::lunarNXT::Order_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::lunarNXT::Order_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace lunarNXT

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::lunarNXT::Order_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::lunarNXT::Order_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::lunarNXT::Order_<ContainerAllocator> > {
  static const char* value() 
  {
    return "37fcf37ef978840f2eb907ffb27c7c3c";
  }

  static const char* value(const  ::lunarNXT::Order_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x37fcf37ef978840fULL;
  static const uint64_t static_value2 = 0x2eb907ffb27c7c3cULL;
};

template<class ContainerAllocator>
struct DataType< ::lunarNXT::Order_<ContainerAllocator> > {
  static const char* value() 
  {
    return "lunarNXT/Order";
  }

  static const char* value(const  ::lunarNXT::Order_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::lunarNXT::Order_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string order\n\
float64 value\n\
\n\
";
  }

  static const char* value(const  ::lunarNXT::Order_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::lunarNXT::Order_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.order);
    stream.next(m.value);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct Order_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::lunarNXT::Order_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::lunarNXT::Order_<ContainerAllocator> & v) 
  {
    s << indent << "order: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.order);
    s << indent << "value: ";
    Printer<double>::stream(s, indent + "  ", v.value);
  }
};


} // namespace message_operations
} // namespace ros

#endif // LUNARNXT_MESSAGE_ORDER_H

