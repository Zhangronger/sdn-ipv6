/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */            
/*
 * Copyright (c) 2008 IT-SUDPARIS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as 
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Providence SALUMU M. <Providence.Salumu_Munga@it-sudparis.eu>
 */

#ifndef   	MIH_TLV_H
#define   	MIH_TLV_H

#include <iostream>
#include <vector>
#include <stdint.h>
#include "ns3/buffer.h"
#include "ns3/address.h"
#include "ns3/assert.h"

#define TLV_TYPE_HELPER_HEADER(className)		\
  virtual uint8_t GetTlvType (void) const;		\
  static uint8_t GetRegisteredTlvType (void);           \
  virtual uint8_t GetTlvTypeValue (void) const;         \

#define TLV_TYPE_HELPER_IMPLEM(className,tlvTypeValue)			\
  uint8_t                                                               \
  className::GetRegisteredTlvType (void)				\
  {                                                                     \
    static uint8_t typ = ns3::mih::Tlv::RegisterTlvType ();             \
    return typ;                                                         \
  }                                                                     \
  uint8_t                                                               \
  className::GetTlvType (void) const                                    \
  {                                                                     \
    return GetRegisteredTlvType ();                                     \
  }                                                                     \
  uint8_t                                                               \
  className::GetTlvTypeValue (void) const                               \
  {                                                                     \
  NS_ASSERT_MSG (tlvTypeValue > 0, "Illegal TlvTypeValue entered for #className"); \
  return tlvTypeValue;                                                  \
  }

namespace ns3 {
  
  class Address;
  
  namespace mih {

    enum TlvTypeValue_E {
      TLV_EXPERIMENTAL = 110,
      TLV_INVALID = 0,
      TLV_SOURCE_MIHFID = 1,
      TLV_DESTINATION_MIHFID = 2,
      TLV_STATUS = 3,
      TLV_LINK_TYPE = 4,
      TLV_MIH_EVENT_LIST = 5,
      TLV_MIH_COMMAND_LIST = 6,
      TLV_MIIS_QUERY_TYPE_LIST = 7,
      TLV_TRANSPORT_OPTION_LIST = 8,
      TLV_MBB_HO_SUPPORT = 9,
      TLV_NETWORK_TYPE_ADDRESS_LIST = 10,
      TLV_REGISTRATION_CODE = 11,
      TLV_VALID_TIME_INTERVAL = 12,
      TLV_LINK_IDENTIFIER = 13,
      TLV_NEW_LINK_IDENTIFIER = 14,
      TLV_OLD_ACCESS_ROUTER = 15,
      TLV_NEW_ACCESS_ROUTER = 16,
      TLV_IP_RENEWAL_FLAG = 17, 
      TLV_MOBILITY_MANAGEMENT_SUPPORT = 18,
      TLV_LINK_DOWN_REASON = 20,
      TLV_TIME_INTERVAL = 21,
      TLV_LINK_GOING_DOWN_REASON = 22,
      TLV_LINK_PARAMETER_REPORT_LIST = 23,
      TLV_DEVICE_STATES_REQUEST = 24,
      TLV_LINK_IDENTIFIER_LIST = 25,
      TLV_LINK_STATUS_REQUEST = 27,
      TLV_LINK_STATUS_RESPONSE_LIST = 28,
      TLV_LINK_CONFIGURATION_PARAMETER_LIST = 29,
      TLV_LINK_CONFIGURATION_STATUS_LIST = 30,
      TLV_LINK_POA_LIST = 31,
      TLV_LINK_ACTION_REQUEST_LIST = 39,
      TLV_LINK_ACTION_RESPONSE_LIST = 40,
      TLV_LINK_DETECTED_INFORMATION = 59,
      TLV_MN_LINK_IDENTIFIER = 60,
      TLV_POA_LINK_IDENTIFIER = 61,
      TLV_NETWORK_TYPE_ADDRESS = TLV_EXPERIMENTAL + 0, // undefined
      // within
      // P802-21-D11
      TLV_LINK_ADDRESS = TLV_EXPERIMENTAL + 1, // Used in
                                               // NetworkTypeAddress;
      TLV_MBB_HO_SUPPORT_LIST = TLV_EXPERIMENTAL + 2, // MakeBeforeBreakSupport;
      TLV_LINK_STATES_REQUEST = TLV_EXPERIMENTAL + 3,
      TLV_LINK_DESCRIPTORS_REQUEST = TLV_EXPERIMENTAL + 4,
      TLV_LINK_PARAMETER_TYPE = TLV_EXPERIMENTAL + 5,
      TLV_LINK_PARAMETER_TYPE_LIST = TLV_EXPERIMENTAL + 6,
      TLV_DEVICE_STATES_RESPONSE = TLV_EXPERIMENTAL + 7,
      TLV_DEVICE_STATES_RESPONSE_LIST = TLV_EXPERIMENTAL + 8,
      TLV_LINK_STATUS_RESPONSE = TLV_EXPERIMENTAL + 9,
      TLV_LINK_STATES_RESPONSE = TLV_EXPERIMENTAL + 10,
      TLV_LINK_STATES_RESPONSE_LIST = TLV_EXPERIMENTAL + 11,
      TLV_LINK_DESCRIPTORS_RESPONSE = TLV_EXPERIMENTAL + 12,
      TLV_LINK_DESCRIPTORS_RESPONSE_LIST = TLV_EXPERIMENTAL + 13,
      TLV_LINK_PARAMETER = TLV_EXPERIMENTAL + 14,
      TLV_LINK_PARAMETER_LIST = TLV_EXPERIMENTAL + 15,
      TLV_PARAMETER_VALUE = TLV_EXPERIMENTAL + 16,
      TLV_THRESHOLD = TLV_EXPERIMENTAL + 17,
      TLV_THRESHOLD_LIST = TLV_EXPERIMENTAL + 18,
      TLV_THRESHOLD_VALUE = TLV_EXPERIMENTAL + 19,
      TLV_THRESHOLD_X_DIRECTION = TLV_EXPERIMENTAL + 20,
      TLV_BATTERY_LEVEL = TLV_EXPERIMENTAL + 21,
      TLV_CHANNEL_IDENTIFIER = TLV_EXPERIMENTAL + 22,
      TLV_DEVICE_INFORMATION = TLV_EXPERIMENTAL + 23,
      TLV_LINK_PARAMETER_VALUE = TLV_EXPERIMENTAL + 24,
      TLV_LINK_PARAMETER_802_11 = TLV_EXPERIMENTAL + 25,
      TLV_NUMBER_OF_COS = TLV_EXPERIMENTAL + 26,
      TLV_NUMBER_OF_QUEUES = TLV_EXPERIMENTAL + 27,
      TLV_OPERATION_MODE = TLV_EXPERIMENTAL + 28,
      TLV_LINK_CONFIGURATION_PARAMETER = TLV_EXPERIMENTAL + 29,
      TLV_LINK_CONFIGURATION_TIME_INTERVAL = TLV_EXPERIMENTAL + 30,
      TLV_LINK_CONFIGURATION_THRESHOLD_ACTION = TLV_EXPERIMENTAL + 31,
      TLV_LINK_CONFIGURATION_STATUS =  TLV_EXPERIMENTAL + 32,
      TLV_SINR = TLV_EXPERIMENTAL + 33,
      TLV_LINK_DETECTED_INFORMATION_LIST = TLV_EXPERIMENTAL + 34,
      TLV_NETWORK_IDENTIFIER = TLV_EXPERIMENTAL + 35,
      TLV_NETWORK_AUXILIARY_IDENTIFIER = TLV_EXPERIMENTAL + 36,
      TLV_SIGNAL_STRENGTH = TLV_EXPERIMENTAL + 37,
      TLV_DATA_RATE = TLV_EXPERIMENTAL + 38,
      TLV_CAPABILITY_FLAG = TLV_EXPERIMENTAL + 39,
      TLV_NETWORK_CAPABILITIES = TLV_EXPERIMENTAL + 40,
      TLV_LINK_PARAMETER_REPORT = TLV_EXPERIMENTAL + 41,
      TLV_QOS_PARAMETER_VALUE = TLV_EXPERIMENTAL + 42,
      TLV_LINK_ACTION = TLV_EXPERIMENTAL + 43,
      TLV_LINK_ACTION_ATTRIBUTE = TLV_EXPERIMENTAL + 44,
      TLV_LINK_ACTION_REQUEST = TLV_EXPERIMENTAL + 45,
      TLV_SCAN_RESPONSE = TLV_EXPERIMENTAL + 46,
      TLV_SCAN_RESPONSE_LIST = TLV_EXPERIMENTAL + 47,
      TLV_LINK_ACTION_RESPONSE =  TLV_EXPERIMENTAL + 48,
      TLV_LINK_ACTION_RESULT = TLV_EXPERIMENTAL + 50,
    };

    class Tlv {
    public:
      virtual ~Tlv (void);
      // TTLV-Serialization interface
      virtual uint32_t GetTlvSerializedSize (void) const = 0;
      virtual void TlvSerialize (Buffer &buffer) const = 0;
      virtual uint32_t TlvDeserialize (Buffer &buffer) = 0;
      // The following are defined through TLV_HELPER_xxx macros, so
      // there is no need to account for them.
      virtual uint8_t GetTlvType (void) const = 0;
      virtual uint8_t GetTlvTypeValue (void) const = 0;
      static uint8_t RegisterTlvType (void);
      // TLV toolkit.
      static uint32_t ComputeLengthOfLengthField (uint32_t payloadLength);
      static void WritePayloadLengthField (Buffer::Iterator &i, 
                                           uint32_t payloadLength);
      /**
       * \brief Read the payload length field from a TLV representation.
       * \return Number of bytes read.
       */
      static uint32_t ReadPayloadLengthField (Buffer::Iterator &i, 
                                              uint32_t roomSize, 
                                              uint32_t &payloadLengthValue);
      static void PrintBuffer (std::ostream &os, const Buffer &buffer);
      template<typename T>
      static uint32_t GetSerializedSize (const std::vector<Ptr<T> > &tList);
      template<typename T>
      static void Serialize (Buffer &buffer, 
                             const std::vector<Ptr<T> > &tList, 
                             uint8_t tlvTypeValue);
      template <typename T>
      static uint32_t Deserialize (Buffer &buffer, 
                                   std::vector<Ptr<T> > &tList, 
                                   uint8_t tlvTypeValue);
      // TLV for Address values;
      static uint32_t GetSerializedSize (Address address);
      static void Serialize (Buffer &buffer,
                             Address address, 
                             uint8_t tlvTypeValue);
      static uint32_t Deserialize (Buffer &buffer, 
                                   Address &address, 
                                   uint8_t tlvTypeValue);
      // TLV for bool values;
      static uint32_t GetSerializedSizeBool (void);
      static void SerializeBool (Buffer &buffer, 
                                 bool element, 
                                 uint8_t tlvTypeValue);
      static uint32_t DeserializeBool (Buffer &buffer, 
                                       bool &element, 
                                       uint8_t tlvTypeValue);    
      // TLV for uint8_t values;
      static uint32_t GetSerializedSizeU8 (void);
      static void SerializeU8 (Buffer &buffer, 
                               uint8_t element, 
                               uint8_t tlvTypeValue);
      static uint32_t DeserializeU8 (Buffer &buffer,
                                     uint8_t &element,
                                     uint8_t tlvTypeValue);
      // TLV for uint16_t values;
      static uint32_t GetSerializedSizeU16 (void);
      static void SerializeU16 (Buffer &buffer,
                                uint16_t element, 
                                uint8_t tlvTypeValue);
      static uint32_t DeserializeU16 (Buffer &buffer, 
                                      uint16_t &element, 
                                      uint8_t tlvTypeValue);
      // TLV for uint32_t values;
      static uint32_t GetSerializedSizeU32 (void);
      static void SerializeU32 (Buffer &buffer, 
                                uint32_t element, 
                                uint8_t tlvTypeValue);
      static uint32_t DeserializeU32 (Buffer &buffer,
                                      uint32_t &element,
                                      uint8_t tlvTypeValue);
      // TLV for uint64_t values;
      static uint32_t GetSerializedSizeU64 (void);
      static void SerializeU64 (Buffer &buffer,
                                uint64_t element, 
                                uint8_t tlvTypeValue);
      static uint32_t DeserializeU64 (Buffer &buffer, 
                                      uint64_t &element,
                                      uint8_t tlvTypeValue);
      // TLV for string values;
      static uint32_t GetSerializedSizeString (std::string element);
      static void SerializeString (Buffer &buffer,
                                   std::string element, 
                                   uint8_t tlvTypeValue);
      static uint32_t DeserializeString (Buffer &buffer,
                                         std::string &element, 
                                         uint8_t tlvTypeValue);
    };
    
    template<typename T>
    uint32_t 
    Tlv::GetSerializedSize (const std::vector<Ptr<T> > &tList)
    {
      uint32_t sizeOfList = tList.size ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;
      uint32_t size = 0;
      
      for (uint32_t i = 0; i < sizeOfList; i++)
        {
          payloadLength += tList[i]->GetTlvSerializedSize ();
        }
      
      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      size = 1 + lengthOfLengthField + payloadLength;
      return size;
    }
    template<typename T>
    void
    Tlv::Serialize (Buffer &buffer, 
                    const std::vector<Ptr<T> > &tList, 
                    uint8_t tlvTypeValue)
    {
      uint32_t sizeOfList = tList.size ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;
      uint32_t formerBufferSize = buffer.GetSize ();
      for (uint32_t j = 0; j < sizeOfList; j++)
        {
          payloadLength += tList[j]->GetTlvSerializedSize ();
        }
      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field +
                                                 // Length field only;
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (tlvTypeValue); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length
                                                       // field;
      for (uint32_t j = 0; j < sizeOfList; j++)
        {
          tList[j]->TlvSerialize (buffer);
        }
    }
    template <typename T>
    uint32_t
    Tlv::Deserialize (Buffer &buffer, 
                      std::vector<Ptr<T> > &tList, 
                      uint8_t tlvTypeValue) 
    {
      uint32_t totalBytesRead = 0;
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLengthValue = 0;
      Buffer::Iterator i = buffer.Begin ();
      NS_ASSERT_MSG (i.ReadU8 () == tlvTypeValue, "List TLV type values mismatch!");
      totalBytesRead++;
      lengthOfLengthField = i.ReadU8 ();
      totalBytesRead++;
      
      totalBytesRead += Tlv::ReadPayloadLengthField (i, lengthOfLengthField, payloadLengthValue);
      buffer.RemoveAtStart (totalBytesRead);
      
      uint32_t bytesReadFromList = 0;
      while (bytesReadFromList < payloadLengthValue)
        {
          i = buffer.Begin ();
          Ptr<T> item = T::CreateFromTlvType (i.ReadU8 ());
          uint32_t bytesRead = item->TlvDeserialize (buffer);
          bytesReadFromList += bytesRead;
          totalBytesRead += bytesRead;
          tList.push_back (item);
        }
      return totalBytesRead;
    }
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_TLV_H */
