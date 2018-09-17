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

#include "mih-link-type.h"

namespace ns3 {
  namespace mih {
    LinkType::LinkType (enum LinkType::Type typ) :
      m_type (typ)
    {}
    LinkType::LinkType (LinkType const &o) :
      m_type (o.m_type)
    {}
    TLV_TYPE_HELPER_IMPLEM (LinkType, TLV_LINK_TYPE)
    LinkType&
    LinkType::operator= (const LinkType &o)
    {
      m_type = o.m_type;
      return *this;
    }
    void 
    LinkType::SetType (enum LinkType::Type code)
    {
      m_type = code;
    }
    enum LinkType::Type 
    LinkType::GetType (void)
    {
      return m_type;
    }
    bool 
    LinkType::IsEqual (LinkType const &o) const
    {
      return (m_type == o.m_type);
    }
    uint32_t 
    LinkType::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU8 ();
    }
    void
    LinkType::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU8 (buffer, static_cast<uint8_t> (m_type), TLV_LINK_TYPE);
    }
    uint32_t
    LinkType::TlvDeserialize (Buffer &buffer)
    {
      uint32_t bytesRead = 0;
      uint8_t typ = 0;
      bytesRead += Tlv::DeserializeU8 (buffer, typ, TLV_LINK_TYPE);
      m_type = static_cast<enum LinkType::Type> (typ);
      return bytesRead;
    }
    bool
    operator == (LinkType const &a, LinkType const &b)
    {
      return (a.m_type == b.m_type);
    }
    bool
    operator != (LinkType const &a, LinkType const &b)
    {
      return (a.m_type != b.m_type);
    }
    std::ostream &
    operator << (std::ostream &os, const LinkType &a)
    {
      os <<
        std::right << std::dec << (int) static_cast<uint8_t> (a.m_type)
        ;
      return os;
    }
  } // namespace mih
} // namespace ns3
