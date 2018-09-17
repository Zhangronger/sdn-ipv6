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

#include "mih-scan-response.h"

namespace ns3 {
  namespace mih {
    ScanResponse::ScanResponse (Address poaL2Address, 
                                NetworkIdentifier networkIdentifier,
                                SignalStrength signalStrength) :
      m_poaLinkAddress (poaL2Address),
      m_networkIdentifier (networkIdentifier),
      m_signalStrength (signalStrength)
    {}
    ScanResponse::ScanResponse (ScanResponse const &o) :
      m_poaLinkAddress (o.m_poaLinkAddress),
      m_networkIdentifier (o.m_networkIdentifier),
      m_signalStrength (o.m_signalStrength)      
    {}
    TLV_TYPE_HELPER_IMPLEM (ScanResponse, TLV_SCAN_RESPONSE);
    Ptr<ScanResponse> 
    ScanResponse::CreateFromTlvType (uint8_t val)
    {
      NS_ASSERT (val == TLV_SCAN_RESPONSE);
      return Create<ScanResponse> ();
    }
    Address 
    ScanResponse::GetPoALinkAddress (void)
    {
      return m_poaLinkAddress;
    }
    NetworkIdentifier 
    ScanResponse::GetNetworkIdentifier (void)
    {
      return m_networkIdentifier;
    }
    SignalStrength 
    ScanResponse::GetSignalStrength (void)
    {
      return m_signalStrength;
    }
    uint32_t 
    ScanResponse::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      payloadLength = Tlv::GetSerializedSize (m_poaLinkAddress) +
        m_networkIdentifier.GetTlvSerializedSize () +
        m_signalStrength.GetTlvSerializedSize ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      return 1 + lengthOfLengthField + payloadLength;
    }
    void 
    ScanResponse::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;

      payloadLength = Tlv::GetSerializedSize (m_poaLinkAddress) +
        m_networkIdentifier.GetTlvSerializedSize () +
        m_signalStrength.GetTlvSerializedSize ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field + Length field only;
      
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length field;

      Tlv::Serialize (buffer, m_poaLinkAddress, TLV_POA_LINK_IDENTIFIER);
      m_networkIdentifier.TlvSerialize (buffer);
      m_signalStrength.TlvSerialize (buffer);
    }
    uint32_t 
    ScanResponse::TlvDeserialize (Buffer &buffer)
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

      totalBytesRead += Tlv::Deserialize (buffer, m_poaLinkAddress, TLV_POA_LINK_IDENTIFIER);
      totalBytesRead += m_networkIdentifier.TlvDeserialize (buffer);
      totalBytesRead += m_signalStrength.TlvDeserialize (buffer);
      
      return totalBytesRead;
    }
    uint32_t
    GetTlvSerializedSize (const ScanResponseList &scanResponseList)
    {
      return Tlv::GetSerializedSize<ScanResponse> (scanResponseList);
    }
    void
    TlvSerialize (Buffer &buffer, const ScanResponseList &scanResponseList)
    {
      Tlv::Serialize<ScanResponse> (buffer, scanResponseList, TLV_SCAN_RESPONSE_LIST);
    }
    uint32_t
    TlvDeserialize (Buffer &buffer, ScanResponseList &scanResponseList)
    {
      return Tlv::Deserialize<ScanResponse> (buffer, scanResponseList, TLV_SCAN_RESPONSE_LIST);    
    }
  } // namespace mih
} // namespace ns3
