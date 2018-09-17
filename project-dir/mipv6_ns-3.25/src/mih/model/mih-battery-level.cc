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

#include "ns3/assert.h"
#include "mih-battery-level.h"

namespace ns3 {
  namespace mih {
    BatteryLevel::BatteryLevel (uint8_t batteryLevel, LinkIdentifier linkId) :
      m_batteryLevel (batteryLevel),
      m_linkIdentifier (linkId)
    {
      NS_ASSERT_MSG (batteryLevel <= 100, "Battery level should not exceed 100%!");
      SimulationSingleton<TlvObjectFactory<DeviceStatesResponse> >::Get ()->AddTlvTypeConstructor (TLV_BATTERY_LEVEL,
                                                                                                   MakeCallback (&BatteryLevel::Create));
    }
    BatteryLevel::BatteryLevel (BatteryLevel const &o)
    {
      m_batteryLevel = o.m_batteryLevel;
    }
    CHOICE_HELPER_IMPLEM (BatteryLevel, DeviceStatesResponse)
    TLV_TYPE_HELPER_IMPLEM (BatteryLevel, TLV_BATTERY_LEVEL)
    LinkIdentifier
    BatteryLevel::GetLinkIdentifier (void)
    {
      return m_linkIdentifier;
    }
    void 
    BatteryLevel::SetLinkIdentifier (LinkIdentifier linkIdentifier)
    {
      m_linkIdentifier = linkIdentifier;
    }
    uint8_t
    BatteryLevel::GetValue (void)
    {
      return m_batteryLevel;
    }
    uint32_t 
    BatteryLevel::GetTlvSerializedSize (void) const
    {
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;
      
      payloadLength = Tlv::GetSerializedSizeU8 () +
        m_linkIdentifier.GetTlvSerializedSize ();
      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      return 1 + lengthOfLengthField + payloadLength;
    }
    void
    BatteryLevel::Print (std::ostream &os) const 
    {
      os << "Battery Level = " << (int)m_batteryLevel << std::endl;
    }
    void
    BatteryLevel::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;
      
      payloadLength = Tlv::GetSerializedSizeU8 () +
        m_linkIdentifier.GetTlvSerializedSize ();
      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field +
                                                 // Length field only;
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length
                                                       // field;
      
      Tlv::SerializeU8 (buffer, m_batteryLevel, TLV_BATTERY_LEVEL);
      m_linkIdentifier.TlvSerialize (buffer);
    }
    uint32_t
    BatteryLevel::TlvDeserialize (Buffer &buffer)
    {
      uint32_t totalBytesRead = 0;
      uint32_t roomSize;
      uint32_t payloadLengthValue = 0;
      Buffer::Iterator i = buffer.Begin ();
      NS_ASSERT (i.ReadU8 () == GetTlvTypeValue ());
      totalBytesRead++;
      roomSize = i.ReadU8 ();
      totalBytesRead++;
      
      totalBytesRead += Tlv::ReadPayloadLengthField (i, roomSize, payloadLengthValue);
      buffer.RemoveAtStart (totalBytesRead);
      
      totalBytesRead += Tlv::DeserializeU8 (buffer, m_batteryLevel, TLV_BATTERY_LEVEL);
      totalBytesRead += m_linkIdentifier.TlvDeserialize (buffer);
      
      return totalBytesRead;
    }
  } // namespace mih
} // namespace ns3
