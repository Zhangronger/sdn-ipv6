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

#include "mih-link-detected-information.h"

namespace ns3 {
  namespace mih {
    LinkDetectedInformation::LinkDetectedInformation (void)
    {}
    LinkDetectedInformation::LinkDetectedInformation (LinkIdentifier linkIdentifier,
						      NetworkIdentifier networkIdentifier,
						      NetworkAuxiliaryIdentifier networkAuxiliaryIdentifier,
						      SignalStrength signalStrength,
						      uint16_t sinr,
						      DataRate dataRate,
						      MihCapabilityFlag mihCapabilityFlag,
						      NetworkCapabilities networkCapabilities) :
      m_linkIdentifier (linkIdentifier),
      m_networkIdentifier (networkIdentifier),
      m_networkAuxiliaryIdentifier (networkAuxiliaryIdentifier),
      m_signalStrength (signalStrength),
      m_sinr (sinr),
      m_dataRate (dataRate),
      m_mihCapabilityFlag (mihCapabilityFlag),
      m_networkCapabilities (networkCapabilities)
    {}
    LinkDetectedInformation::LinkDetectedInformation (LinkDetectedInformation const &o) :
      m_linkIdentifier (o.m_linkIdentifier),
      m_networkIdentifier (o.m_networkIdentifier),
      m_networkAuxiliaryIdentifier (o.m_networkAuxiliaryIdentifier),
      m_signalStrength (o.m_signalStrength),
      m_sinr (o.m_sinr),
      m_dataRate (o.m_dataRate),
      m_mihCapabilityFlag (o.m_mihCapabilityFlag),
      m_networkCapabilities (o.m_networkCapabilities)
    {}
    LinkIdentifier 
    LinkDetectedInformation::GetLinkIdentifier (void)
    {
      return m_linkIdentifier;
    }
    NetworkIdentifier 
    LinkDetectedInformation::GetNetworkIdentifier (void)
    {
      return m_networkIdentifier;
    }
    NetworkAuxiliaryIdentifier
    LinkDetectedInformation::GetNetworkAuxiliaryIdentifier (void)
    {
      return m_networkAuxiliaryIdentifier;
    }
    SignalStrength 
    LinkDetectedInformation::GetSignalStrength (void)
    {
      return m_signalStrength;
    }
    uint16_t 
    LinkDetectedInformation::GetSinr (void)
    {
      return m_sinr;
    }
    DataRate 
    LinkDetectedInformation::GetDataRate (void)
    {
      return m_dataRate;
    }
    MihCapabilityFlag 
    LinkDetectedInformation::GetMihCapabilityFlag (void)
    {
      return m_mihCapabilityFlag;
    }
    NetworkCapabilities 
    LinkDetectedInformation::GetNetworkCapabilities (void) 
    {
      return m_networkCapabilities;
    }
    uint32_t
    LinkDetectedInformation::GetTlvSerializedSize (void) const {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      payloadLength = m_linkIdentifier.GetTlvSerializedSize () +
        m_networkIdentifier.GetTlvSerializedSize () +
        m_networkAuxiliaryIdentifier.GetTlvSerializedSize () +
        m_signalStrength.GetTlvSerializedSize () +
        Tlv::GetSerializedSizeU16 () +
        m_dataRate.GetTlvSerializedSize () +
        m_mihCapabilityFlag.GetTlvSerializedSize () +
        m_networkCapabilities.GetTlvSerializedSize ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      return 1 + lengthOfLengthField + payloadLength;
    }
    void
    LinkDetectedInformation::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;
      
      payloadLength = m_linkIdentifier.GetTlvSerializedSize () +
        m_networkIdentifier.GetTlvSerializedSize () +
        m_networkAuxiliaryIdentifier.GetTlvSerializedSize () +
        m_signalStrength.GetTlvSerializedSize () +
        Tlv::GetSerializedSizeU16 () +
        m_dataRate.GetTlvSerializedSize () +
        m_mihCapabilityFlag.GetTlvSerializedSize () +
        m_networkCapabilities.GetTlvSerializedSize ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field + Length field only;
      
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length field;

      m_linkIdentifier.TlvSerialize (buffer);
      m_networkIdentifier.TlvSerialize (buffer);
      m_networkAuxiliaryIdentifier.TlvSerialize (buffer);
      m_signalStrength.TlvSerialize (buffer);
      Tlv::SerializeU16 (buffer, m_sinr, TLV_SINR);
      m_dataRate.TlvSerialize (buffer);
      m_mihCapabilityFlag.TlvSerialize (buffer);
      m_networkCapabilities.TlvSerialize (buffer);
    }
    uint32_t 
    LinkDetectedInformation::TlvDeserialize (Buffer &buffer) 
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

      totalBytesRead += m_linkIdentifier.TlvDeserialize (buffer);
      totalBytesRead += m_networkIdentifier.TlvDeserialize (buffer);
      totalBytesRead += m_networkAuxiliaryIdentifier.TlvDeserialize (buffer);
      totalBytesRead += m_signalStrength.TlvDeserialize (buffer);
      totalBytesRead += Tlv::DeserializeU16 (buffer, m_sinr, TLV_SINR);
      totalBytesRead += m_dataRate.TlvDeserialize (buffer);
      totalBytesRead += m_mihCapabilityFlag.TlvDeserialize (buffer);
      totalBytesRead += m_networkCapabilities.TlvDeserialize (buffer);
      return totalBytesRead;
    }
    TLV_TYPE_HELPER_IMPLEM (LinkDetectedInformation, TLV_LINK_DETECTED_INFORMATION)
    Ptr<LinkDetectedInformation> 
    LinkDetectedInformation::CreateFromTlvType (uint8_t val)
    {
      NS_ASSERT (val == TLV_LINK_DETECTED_INFORMATION);
      return Create<LinkDetectedInformation> ();
    }
    uint32_t
    GetTlvSerializedSize (const LinkDetectedInformationList &linkDetectedInformationList)
    {
      return Tlv::GetSerializedSize<LinkDetectedInformation> (linkDetectedInformationList);
    }
    void
    TlvSerialize (Buffer &buffer, const LinkDetectedInformationList &linkDetectedInformationList)
    {
      Tlv::Serialize<LinkDetectedInformation> (buffer, linkDetectedInformationList, TLV_LINK_DETECTED_INFORMATION_LIST);
    }
    uint32_t
    TlvDeserialize (Buffer &buffer, LinkDetectedInformationList &linkDetectedInformationList)
    {
      return Tlv::Deserialize<LinkDetectedInformation> (buffer, linkDetectedInformationList, TLV_LINK_DETECTED_INFORMATION_LIST);      
    }    
    std::ostream&
    operator << (std::ostream &os, LinkDetectedInformation &a)
    {
      os << "LinK Identifier = " << a.GetLinkIdentifier ();
      return os;
    }
    std::ostream&
    operator << (std::ostream&os, LinkDetectedInformationList &a)
    {
      for (uint32_t j = 0; j < a.size (); j++)
        {
          os << *(PeekPointer(a[j])) << " ";
        }
      return os;
    }
  } // namespace mih
} // namespace ns3
