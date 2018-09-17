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
#include "mih-device-information.h"

namespace ns3 {
  namespace mih {
    DeviceInformation::DeviceInformation (std::string deviceInformation) :
      m_deviceInformation (deviceInformation)
    {
      NS_ASSERT_MSG (deviceInformation.length () <= 253, "Unsupported device information string");
      SimulationSingleton<TlvObjectFactory<DeviceStatesResponse> >::Get ()->AddTlvTypeConstructor (TLV_DEVICE_INFORMATION,
                                                                                                   MakeCallback (&DeviceInformation::Create));
    }
    DeviceInformation::DeviceInformation (DeviceInformation const &o)
    {
      m_deviceInformation = o.m_deviceInformation;
    }
    CHOICE_HELPER_IMPLEM (DeviceInformation, DeviceStatesResponse)
    TLV_TYPE_HELPER_IMPLEM (DeviceInformation, TLV_DEVICE_INFORMATION)
    const char* 
    DeviceInformation::PeekString (void)
    {
      return m_deviceInformation.c_str ();
    }
    LinkIdentifier 
    DeviceInformation::GetLinkIdentifier (void)
    {
      return m_linkIdentifier;
    }
    void 
    DeviceInformation::SetLinkIdentifier (LinkIdentifier linkIdentifier)
    {
      m_linkIdentifier = linkIdentifier;
    }
    uint32_t
    DeviceInformation::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      payloadLength = Tlv::GetSerializedSizeString (m_deviceInformation) +
        m_linkIdentifier.GetTlvSerializedSize ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      return 1 + lengthOfLengthField + payloadLength;
      
    }
    void 
    DeviceInformation::Print (std::ostream &os) const
    {
      os << "Device Information = " << m_deviceInformation << std::endl;
    }
    void 
    DeviceInformation::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;

      payloadLength = Tlv::GetSerializedSizeString (m_deviceInformation) +
        m_linkIdentifier.GetTlvSerializedSize ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field +
                                                 // Length field only;
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length
                                                       // field;
      Tlv::SerializeString (buffer, m_deviceInformation, GetTlvTypeValue ());
      m_linkIdentifier.TlvSerialize (buffer);
      
    }
    uint32_t 
    DeviceInformation::TlvDeserialize (Buffer &buffer)
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
      totalBytesRead += Tlv::DeserializeString (buffer, m_deviceInformation, GetTlvTypeValue ());
      totalBytesRead += m_linkIdentifier.TlvDeserialize (buffer);
      return totalBytesRead;
    }
  } // namespace mih
} // namespace ns3
