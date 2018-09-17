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
#include "ns3/address.h"
#include "mih-link-identifier.h"

NS_LOG_COMPONENT_DEFINE ("LinkIdentifier");

namespace ns3 {
  namespace mih {
    LinkIdentifier::LinkIdentifier (LinkType linkType, Address deviceLinkAddress, Address poaLinkAddress) :
      m_type (linkType),
      m_mobileNodeAddress (deviceLinkAddress),
      m_poaAddress (poaLinkAddress)
    {}
    LinkIdentifier::LinkIdentifier (LinkIdentifier const &o) :
      m_type (o.m_type),
      m_mobileNodeAddress (o.m_mobileNodeAddress),
      m_poaAddress (o.m_poaAddress)
    {}
    LinkIdentifier&
    LinkIdentifier::operator= (const LinkIdentifier &o)
    {
      m_type = o.m_type;
      m_mobileNodeAddress = o.m_mobileNodeAddress;
      m_poaAddress = o.m_poaAddress;
      return *this;
    }
    TLV_TYPE_HELPER_IMPLEM (LinkIdentifier, TLV_LINK_IDENTIFIER)
    Ptr<LinkIdentifier> 
    LinkIdentifier::CreateFromTlvType (uint8_t tlvTypeValue)
    {
      NS_ASSERT (tlvTypeValue == TLV_LINK_IDENTIFIER);
      return Create<LinkIdentifier> ();
    }
    LinkType
    LinkIdentifier::GetType (void)
    {
      return m_type;
    }
    void
    LinkIdentifier::SetType (LinkType linkType)
    {
      m_type = linkType;
    }
    Address 
    LinkIdentifier::GetDeviceLinkAddress (void)
    {
      return m_mobileNodeAddress;
    }
    void
    LinkIdentifier::SetDeviceLinkAddress (Address addr)
    {
      m_mobileNodeAddress = addr;
    }
    Address 
    LinkIdentifier::GetPoALinkAddress (void)
    {
      return m_poaAddress;
    }
    void
    LinkIdentifier::SetPoALinkAddress (Address addr)
    {
      m_poaAddress = addr;
    }
    bool 
    LinkIdentifier::IsEqual (LinkIdentifier const &o) const
    {
      return (m_type.IsEqual (o.m_type) && 
              m_mobileNodeAddress == o.m_mobileNodeAddress && 
              m_poaAddress == o.m_poaAddress);
    }
    uint32_t 
    LinkIdentifier::GetTlvSerializedSize (void) const
    {
      return m_type.GetTlvSerializedSize () + 
        Tlv::GetSerializedSize (m_mobileNodeAddress) + 
        Tlv::GetSerializedSize (m_poaAddress) + 2 // Type + Length
        ;
    }
    void 
    LinkIdentifier::Print (std::ostream &os) const
    {
      os << "["
        "LinkType = " << m_type << " "
        "MN Address = " << m_mobileNodeAddress << " "
        "PoA Address = " << m_poaAddress << "]" << std::endl
        ;
    }
    void
    LinkIdentifier::TlvSerialize (Buffer &buffer) const
    {
      uint32_t formerBufferSize = buffer.GetSize ();
      buffer.AddAtEnd (2); // Type + Length room space;
      Buffer::Iterator i = buffer.Begin ();
      i.Next (formerBufferSize);
      i.WriteU8 (GetTlvTypeValue ());
      i.WriteU8 (GetTlvSerializedSize () - 2);
      m_type.TlvSerialize (buffer);
      Tlv::Serialize (buffer, m_mobileNodeAddress, TLV_MN_LINK_IDENTIFIER);
      Tlv::Serialize (buffer, m_poaAddress, TLV_POA_LINK_IDENTIFIER);
    }
    uint32_t 
    LinkIdentifier::TlvDeserialize (Buffer &buffer)
    {
      uint32_t size = 0;
      Buffer::Iterator i = buffer.Begin ();
      NS_ASSERT (i.ReadU8 () == GetTlvTypeValue ());
      buffer.RemoveAtStart (2); // Type + Length;
      size  += m_type.TlvDeserialize (buffer);
      size  += Tlv::Deserialize (buffer, m_mobileNodeAddress, TLV_MN_LINK_IDENTIFIER);
      size  += Tlv::Deserialize (buffer, m_poaAddress, TLV_POA_LINK_IDENTIFIER);
      return size + 2; // + Type + Length;
    }
    std::ostream &
    operator << (std::ostream &os, const LinkIdentifier &a)
    {
      os << "[Type = " << a.m_type << ", L2 Address = " << a.m_mobileNodeAddress << ", PoA Address = " << a.m_poaAddress << "]"
        ;
      return os;
    }
    std::ostream &
    operator << (std::ostream &os, LinkIdentifierList &a)
    {
      for (LinkIdentifierListI i = a.begin (); i != a.end (); i++)
        {
          os << *(*i);
        }
      return os;
    }
    uint32_t 
    GetTlvSerializedSize (LinkIdentifierList &linkIdentifierList)
    {
      return Tlv::GetSerializedSize<LinkIdentifier> (linkIdentifierList);
    }
    void 
    TlvSerialize (Buffer &buffer, LinkIdentifierList &linkIdentifierList)
    {
      return Tlv::Serialize<LinkIdentifier> (buffer, linkIdentifierList, TLV_LINK_IDENTIFIER_LIST);
    }
    uint32_t 
    TlvDeserialize (Buffer &buffer, LinkIdentifierList &linkIdentifierList)
    {
      return Tlv::Deserialize<LinkIdentifier> (buffer, linkIdentifierList, TLV_LINK_IDENTIFIER_LIST);
    }
  } // namespace mih
} // namespace ns3
