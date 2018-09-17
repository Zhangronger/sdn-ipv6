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

#include "mih-transport-support-list.h"

namespace ns3 {
  namespace mih {
    TransportSupportList::TransportSupportList (uint16_t transports) :
      m_bitmap (transports)
    {}
    TransportSupportList::TransportSupportList (TransportSupportList const &o) :
      m_bitmap (o.m_bitmap)
    {}
    TransportSupportList::~TransportSupportList (void)
    {}
    TLV_TYPE_HELPER_IMPLEM (TransportSupportList, TLV_TRANSPORT_OPTION_LIST)
    uint16_t 
    TransportSupportList::GetTransportSupports (void)
    {
      return m_bitmap;
    }
    uint32_t 
    TransportSupportList::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU16 ();
    }
    void 
    TransportSupportList::Print (std::ostream &os) const
    {
      os <<
        "Transport Option = 0x" << std::hex << (uint16_t)m_bitmap 
                    << std::endl
        ;
    }
    void
    TransportSupportList::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU16 (buffer, m_bitmap, TLV_TRANSPORT_OPTION_LIST);
    }
    uint32_t 
    TransportSupportList::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeU16 (buffer, m_bitmap, TLV_TRANSPORT_OPTION_LIST);
    }
  } // namespace mih
} // namespace ns3
