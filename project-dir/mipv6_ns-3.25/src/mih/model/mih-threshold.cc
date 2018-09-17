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

#include <string>
#include "ns3/log.h"
#include "mih-threshold.h"

NS_LOG_COMPONENT_DEFINE ("Threshold");

namespace ns3 {
  namespace mih {
    Threshold::Threshold (uint16_t thresholdValue, enum CrossDirectionCode crossDirection) :
      m_value (thresholdValue),
      m_crossDirection (crossDirection)
    {}
    Threshold::Threshold (Threshold const &o) :
      m_value (o.m_value),
      m_crossDirection (o.m_crossDirection)
    {}
    TLV_TYPE_HELPER_IMPLEM (Threshold, TLV_THRESHOLD)
    Ptr<Threshold> 
    Threshold::CreateFromTlvType (uint8_t tlvTypeValue)
    {
      NS_ASSERT (tlvTypeValue == TLV_THRESHOLD);
      return Create<Threshold> ();
    }
    uint16_t 
    Threshold::GetThresholdValue (void)
    {
      return m_value;
    }
    enum Threshold::CrossDirectionCode 
    Threshold::GetCrossDirection (void)
    {
      return m_crossDirection;
    }
    void
    Threshold::Print (std::ostream &os) const
    {
      std::string xdir;
      if (m_crossDirection == Threshold::ABOVE_THRESHOLD)
        {
          xdir = "ABOVE ";
          }
      else if (m_crossDirection == Threshold::BELOW_THRESHOLD)
        {
          xdir = "BELOW ";
        }
      else
        {
          xdir = "INVALID";
        }
      os << "Threshold = " << xdir << std::dec << (int)m_value << " units";
    }
    uint32_t 
    Threshold::GetTlvSerializedSize (void) const 
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      payloadLength = Tlv::GetSerializedSizeU16 () + // m_value;
        Tlv::GetSerializedSizeU8 (); // m_xdir
      lengthOfLengthField = 1;
      return 1 + lengthOfLengthField + payloadLength;
    }
    void 
    Threshold::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;

      payloadLength = Tlv::GetSerializedSizeU16 () + // m_value;
        Tlv::GetSerializedSizeU8 (); // m_xdir
      lengthOfLengthField = 1;

      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field + Length field only;
      
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length field;
      
      Tlv::SerializeU16 (buffer, m_value, TLV_THRESHOLD_VALUE);
      Tlv::SerializeU8 (buffer, static_cast<uint8_t> (m_crossDirection), TLV_THRESHOLD_X_DIRECTION);
    }
    uint32_t 
    Threshold::TlvDeserialize (Buffer &buffer)
    {
      uint32_t totalBytesRead = 0;
      uint32_t roomSize;
      uint32_t payloadLengthValue = 0;

      Buffer::Iterator i = buffer.Begin ();
      uint8_t vl = i.ReadU8 ();
      NS_LOG_WARN ("GetTlvTypeValue () = " << (int)GetTlvTypeValue () << "; TLV_THRESHOLD = " << (int)TLV_THRESHOLD << "; i.ReadU8 () = " << (int)vl);
      NS_ASSERT (vl == GetTlvTypeValue ());
      totalBytesRead++;
      roomSize = i.ReadU8 ();
      totalBytesRead++;
      
      totalBytesRead += Tlv::ReadPayloadLengthField (i, roomSize, payloadLengthValue);
      buffer.RemoveAtStart (totalBytesRead);

      totalBytesRead += Tlv::DeserializeU16 (buffer, m_value, TLV_THRESHOLD_VALUE);
      uint8_t xdir = 0;
      totalBytesRead += Tlv::DeserializeU8 (buffer, xdir, TLV_THRESHOLD_X_DIRECTION);
      m_crossDirection = static_cast<enum CrossDirectionCode> (xdir);
      return totalBytesRead;
    }    
    uint32_t
    GetTlvSerializedSize (const ThresholdList &thresholdList)
    {
      return Tlv::GetSerializedSize<Threshold> (thresholdList);
    }
    void
    TlvSerialize (Buffer &buffer, const ThresholdList &thresholdList)
    {
      Tlv::Serialize<Threshold> (buffer, thresholdList, TLV_THRESHOLD_LIST);
    }
    uint32_t
    TlvDeserialize (Buffer &buffer, ThresholdList &thresholdList)
    {
      return Tlv::Deserialize<Threshold> (buffer, thresholdList, TLV_THRESHOLD_LIST);      
    }
  } // namespace mih
} // namespace ns3
