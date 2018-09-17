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

#include "mih-link-descriptors-request.h"

namespace ns3 {
  namespace mih {
    LinkDescriptorsRequest::LinkDescriptorsRequest (uint16_t descriptors) :
      m_descriptors (descriptors)
    {}
    LinkDescriptorsRequest::LinkDescriptorsRequest (LinkDescriptorsRequest const &o) :
      m_descriptors (o.m_descriptors)
    {}
    TLV_TYPE_HELPER_IMPLEM (LinkDescriptorsRequest, TLV_LINK_DESCRIPTORS_REQUEST)    
    bool 
    LinkDescriptorsRequest::IsEqual (LinkDescriptorsRequest const &o) const
    {
      return (m_descriptors == o.m_descriptors);
    }
    uint16_t 
    LinkDescriptorsRequest::GetDescriptors (void)
    {
      return m_descriptors;
    }
    LinkDescriptorsRequest 
    LinkDescriptorsRequest::operator = (LinkDescriptorsRequest const &o) 
    {
      m_descriptors = o.m_descriptors;
      return *this;
    }
    uint32_t 
    LinkDescriptorsRequest::GetTlvSerializedSize (void) const 
    {
      return Tlv::GetSerializedSizeU16 ();
    }
    void 
    LinkDescriptorsRequest::Print (std::ostream &os) const 
    {
      os << "Link Descriptors Request = " << std::hex << (int)m_descriptors << std::endl;
    }
    void 
    LinkDescriptorsRequest::TlvSerialize (Buffer &buffer) const 
    {
      Tlv::SerializeU16 (buffer, m_descriptors, TLV_LINK_DESCRIPTORS_REQUEST);
    }
    uint32_t 
    LinkDescriptorsRequest::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeU16 (buffer, m_descriptors, TLV_LINK_DESCRIPTORS_REQUEST);
    }
  } // namespace mih
} // namespace ns3
