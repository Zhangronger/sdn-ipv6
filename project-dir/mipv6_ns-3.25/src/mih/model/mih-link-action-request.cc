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

#include "mih-link-action-request.h"

namespace ns3 {
  namespace mih {
    LinkActionRequest::LinkActionRequest (LinkIdentifier linkIdentifier, LinkAction action, uint64_t actionExecutionDelay) :
      m_linkIdentifier (linkIdentifier),
      m_linkAction (action),
      m_linkActionExecutionDelay (actionExecutionDelay)
    {}
    LinkActionRequest::LinkActionRequest (LinkActionRequest const &o) :
      m_linkIdentifier (o.m_linkIdentifier),
      m_linkAction (o.m_linkAction),
      m_linkActionExecutionDelay (o.m_linkActionExecutionDelay)
      
    {}
    TLV_TYPE_HELPER_IMPLEM (LinkActionRequest, TLV_LINK_ACTION_REQUEST);
    Ptr<LinkActionRequest> 
    LinkActionRequest::CreateFromTlvType (uint8_t val)
    {
      NS_ASSERT (val == TLV_LINK_ACTION_REQUEST);
      return Create<LinkActionRequest> ();
    }
    LinkIdentifier 
    LinkActionRequest::GetLinkIdentifier (void)
    {
      return m_linkIdentifier;
    }
    Address
    LinkActionRequest::GetPoaAddress (void)
    {
      return m_poaAddress;
    }
    void
    LinkActionRequest::SetPoaAddress (Address poaAddress)
    {
      m_poaAddress = poaAddress;
    }
    LinkAction 
    LinkActionRequest::GetLinkAction (void)
    {
      return m_linkAction;
    }
    uint64_t 
    LinkActionRequest::GetActionExecutionDelay (void)
    {
      return m_linkActionExecutionDelay;
    }
    uint32_t 
    LinkActionRequest::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      payloadLength = m_linkIdentifier.GetTlvSerializedSize () +
        Tlv::GetSerializedSize (m_poaAddress) +
        m_linkAction.GetTlvSerializedSize () +
        Tlv::GetSerializedSizeU64 ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      return 1 + lengthOfLengthField + payloadLength;
    }
    void 
    LinkActionRequest::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;
      
      payloadLength = m_linkIdentifier.GetTlvSerializedSize () +
        Tlv::GetSerializedSize (m_poaAddress) +
        m_linkAction.GetTlvSerializedSize () +
        Tlv::GetSerializedSizeU64 ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      
      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field + Length field only;
      
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length field;

      m_linkIdentifier.TlvSerialize (buffer);
      Tlv::Serialize (buffer, m_poaAddress, TLV_POA_LINK_IDENTIFIER);
      m_linkAction.TlvSerialize (buffer);
      Tlv::SerializeU64 (buffer, m_linkActionExecutionDelay, TLV_TIME_INTERVAL);
    }
    uint32_t 
    LinkActionRequest::TlvDeserialize (Buffer &buffer)
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
      Tlv::Deserialize (buffer, m_poaAddress, TLV_POA_LINK_IDENTIFIER);
      totalBytesRead += m_linkAction.TlvDeserialize (buffer);
      totalBytesRead += Tlv::DeserializeU64 (buffer, m_linkActionExecutionDelay, TLV_TIME_INTERVAL);

      return totalBytesRead;
    }
    uint32_t
    GetTlvSerializedSize (const LinkActionRequestList &linkActionRequestList)
    {
      return Tlv::GetSerializedSize<LinkActionRequest> (linkActionRequestList);
    }
    void
    TlvSerialize (Buffer &buffer, const LinkActionRequestList &linkActionRequestList)
    {
      Tlv::Serialize<LinkActionRequest> (buffer, linkActionRequestList, TLV_LINK_ACTION_REQUEST_LIST);
    }
    uint32_t
    TlvDeserialize (Buffer &buffer, LinkActionRequestList &linkActionRequestList)
    {
      return Tlv::Deserialize<LinkActionRequest> (buffer, linkActionRequestList, TLV_LINK_ACTION_REQUEST_LIST);    
    }
  } // namespace mih
} // namespace ns3
