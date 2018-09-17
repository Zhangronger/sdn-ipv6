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
#include "mih-link-action.h"

NS_LOG_COMPONENT_DEFINE ("LinkAction");

namespace ns3 {
  namespace mih {
    LinkAction::LinkAction (enum Type actionType, uint8_t actionAttribute) :
      m_type (actionType),
      m_actionAttribute (actionAttribute)
    {}
    LinkAction::LinkAction (LinkAction const &o) :
      m_type (o.m_type),
      m_actionAttribute  (o.m_actionAttribute)
    {}
    TLV_TYPE_HELPER_IMPLEM (LinkAction, TLV_LINK_ACTION);
    bool 
    LinkAction::IsEqual (LinkAction const &o)
    {
      return (m_actionAttribute == o.m_actionAttribute && m_type == o.m_type);
    }
    uint8_t 
    LinkAction::GetActionAttribute (void)
    {
      return m_actionAttribute;
    }
    void 
    LinkAction::SetActionAttribute (uint8_t actionAttribute)
    {
      m_actionAttribute = actionAttribute;
    }
    void 
    LinkAction::SetType (enum LinkAction::Type code)
    {
      m_type = code;
    }
    enum LinkAction::Type 
    LinkAction::GetType (void)
    {
      return m_type;
    }
    uint32_t
    LinkAction::GetTlvSerializedSize (void) const
    {
      uint32_t payloadLength = 0;
      uint32_t lengthOfLengthField = 0;
      
      payloadLength = Tlv::GetSerializedSizeU8 () + 
        Tlv::GetSerializedSizeU8 ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);
      return 1 + lengthOfLengthField + payloadLength;
    }
    void 
    LinkAction::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      uint32_t lengthOfLengthField = 0;
      uint32_t payloadLength = 0;
      
      payloadLength = Tlv::GetSerializedSizeU8 () + 
        Tlv::GetSerializedSizeU8 ();

      lengthOfLengthField = Tlv::ComputeLengthOfLengthField (payloadLength);

      buffer.AddAtEnd (1 + lengthOfLengthField); // Type field + Length field only;
      
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ()); // Type field;
      Tlv::WritePayloadLengthField (i, payloadLength); // Length field;

      Tlv::SerializeU8 (buffer, static_cast<uint8_t> (m_type), TLV_LINK_ACTION);
      Tlv::SerializeU8 (buffer, m_actionAttribute, TLV_LINK_ACTION_ATTRIBUTE);
    }
    uint32_t 
    LinkAction::TlvDeserialize (Buffer &buffer)
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

      uint8_t typ = 0;
      totalBytesRead += Tlv::DeserializeU8 (buffer, typ, TLV_LINK_ACTION);
      m_type = static_cast<enum LinkAction::Type> (typ);
      totalBytesRead += Tlv::DeserializeU8 (buffer, m_actionAttribute, TLV_LINK_ACTION_ATTRIBUTE);

      return totalBytesRead;
    }
  } // namespace mih
} // namespace ns3
