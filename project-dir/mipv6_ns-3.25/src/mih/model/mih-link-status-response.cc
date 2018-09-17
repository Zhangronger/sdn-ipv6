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

#include "ns3/log.h"
#include "ns3/assert.h"
#include "mih-link-status-response.h"

NS_LOG_COMPONENT_DEFINE ("LinkStatusResponse");

namespace ns3 {
  namespace mih {
    LinkStatusResponse::LinkStatusResponse (LinkIdentifier linkIdentifier) :
      m_linkIdentifier (linkIdentifier)
    {}
    LinkStatusResponse::LinkStatusResponse (LinkStatusResponse const &o) :
      m_linkIdentifier (o.m_linkIdentifier),
      m_linkStatesResponseList (o.m_linkStatesResponseList),
      m_linkParameterList (o.m_linkParameterList),
      m_linkDescriptorsResponseList (o.m_linkDescriptorsResponseList)
    {}
    TLV_TYPE_HELPER_IMPLEM (LinkStatusResponse, TLV_LINK_STATUS_RESPONSE);
    Ptr<LinkStatusResponse> 
    LinkStatusResponse::CreateFromTlvType (uint8_t val)
    {
      NS_ASSERT (val == TLV_LINK_STATUS_RESPONSE);
      return Create<LinkStatusResponse> ();
    }
    LinkIdentifier
    LinkStatusResponse::GetLinkIdentifier (void)
    {
      return m_linkIdentifier;
    }
    LinkStatesResponseListI
    LinkStatusResponse::GetLinkStatesResponseListBegin (void)
    {
      return m_linkStatesResponseList.begin ();
    }
    LinkStatesResponseListI 
    LinkStatusResponse::GetLinkStatesResponseListEnd (void)
    {
      return m_linkStatesResponseList.end ();
    }
    void 
    LinkStatusResponse::AddLinkStatesResponse (LinkStatesResponse *linkStatesResponse)
    {
      NS_ASSERT (linkStatesResponse != 0);
      m_linkStatesResponseList.push_back (Ptr<LinkStatesResponse> (linkStatesResponse, false));
    }
    uint32_t
    LinkStatusResponse::GetLinkStatesResponseN (void)
    {
      return m_linkStatesResponseList.size ();
    }
    void
    LinkStatusResponse::SetLinkStatesResponseList (LinkStatesResponseList linkStatesResponseList)
    {
      m_linkStatesResponseList = linkStatesResponseList;
    }
    LinkParameterListI
    LinkStatusResponse::GetLinkParameterListBegin (void)
    {
      return m_linkParameterList.begin ();
    }
    LinkParameterListI
    LinkStatusResponse::GetLinkParameterListEnd (void)
    {
      return m_linkParameterList.end ();
    }
    void 
    LinkStatusResponse::AddLinkParameter (LinkParameter *linkParameter)
    {
      NS_ASSERT (linkParameter != 0);
      m_linkParameterList.push_back (Ptr<LinkParameter> (linkParameter, false));
    }
    uint32_t 
    LinkStatusResponse::GetLinkParameterN (void)
    {
      return m_linkParameterList.size ();
    }
    void
    LinkStatusResponse::SetLinkParameterList (LinkParameterList linkParameterList)
    {
      m_linkParameterList = linkParameterList;
    }
    LinkDescriptorsResponseListI 
    LinkStatusResponse::GetLinkDescriptorsResponseListBegin (void)
    {
      return m_linkDescriptorsResponseList.begin ();
    }
    LinkDescriptorsResponseListI 
    LinkStatusResponse::GetLinkDescriptorsResponseListEnd (void)
    {
      return m_linkDescriptorsResponseList.end ();
    }
    void
    LinkStatusResponse::AddLinkDescriptorsResponse (LinkDescriptorsResponse *linkDescriptorResponse)
    {
      NS_ASSERT (linkDescriptorResponse != 0);
      m_linkDescriptorsResponseList.push_back (Ptr<LinkDescriptorsResponse> (linkDescriptorResponse, false));
    }
    uint32_t
    LinkStatusResponse::GetLinkDescriptorsResponseN (void)
    {
      return m_linkDescriptorsResponseList.size ();
    }
    void
    LinkStatusResponse::SetLinkDescriptorsResponseList (LinkDescriptorsResponseList linkDescriptorsResponseList)
    {
      m_linkDescriptorsResponseList = linkDescriptorsResponseList;
    }
    uint32_t
    LinkStatusResponse::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      payloadLength = m_linkIdentifier.GetTlvSerializedSize () +
        ns3::mih::GetTlvSerializedSize (m_linkStatesResponseList) +
        ns3::mih::GetTlvSerializedSize (m_linkParameterList) +
        ns3::mih::GetTlvSerializedSize (m_linkDescriptorsResponseList);

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      return 1 + lengthOfLengthField + payloadLength;
      
    }
    void 
    LinkStatusResponse::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;
      
      payloadLength = m_linkIdentifier.GetTlvSerializedSize () +
        ns3::mih::GetTlvSerializedSize (m_linkStatesResponseList) +
        ns3::mih::GetTlvSerializedSize (m_linkParameterList) +
        ns3::mih::GetTlvSerializedSize (m_linkDescriptorsResponseList);

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field + Length field only;
      
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length field;

      m_linkIdentifier.TlvSerialize (buffer);
      ns3::mih::TlvSerialize (buffer, m_linkStatesResponseList);
      ns3::mih::TlvSerialize (buffer, m_linkParameterList);
      ns3::mih::TlvSerialize (buffer, m_linkDescriptorsResponseList);
    }
    uint32_t
    LinkStatusResponse::TlvDeserialize (Buffer &buffer)
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
      totalBytesRead += ns3::mih::TlvDeserialize (buffer, m_linkStatesResponseList);
      totalBytesRead += ns3::mih::TlvDeserialize (buffer, m_linkParameterList);
      totalBytesRead += ns3::mih::TlvDeserialize (buffer, m_linkDescriptorsResponseList);
      return totalBytesRead;
    }      
    uint32_t
    GetTlvSerializedSize (const LinkStatusResponseList &linkStatusResponseList)
    {
      return Tlv::GetSerializedSize<LinkStatusResponse> (linkStatusResponseList);
    }
    void
    TlvSerialize (Buffer &buffer, const LinkStatusResponseList &linkStatusResponseList)
    {
      Tlv::Serialize<LinkStatusResponse> (buffer, linkStatusResponseList, TLV_LINK_STATUS_RESPONSE_LIST);
    }
    uint32_t
    TlvDeserialize (Buffer &buffer, LinkStatusResponseList &linkStatusResponseList)
    {
      return Tlv::Deserialize<LinkStatusResponse> (buffer, linkStatusResponseList, TLV_LINK_STATUS_RESPONSE_LIST);    
    }
  } // namespace mih
} // namespace ns3
