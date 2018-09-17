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

#include "mih-link-going-down-reason.h"

namespace ns3 {
  namespace mih {
    LinkGoingDownReason::LinkGoingDownReason (enum LinkGoingDownReason::Type reason) :
      m_reason (reason)
    {}
    LinkGoingDownReason::LinkGoingDownReason (LinkGoingDownReason const &o) :
      m_reason (o.m_reason)
    {}
    TLV_TYPE_HELPER_IMPLEM (LinkGoingDownReason, TLV_LINK_GOING_DOWN_REASON)
    enum LinkGoingDownReason::Type 
    LinkGoingDownReason::GetReason (void)
    {
      return m_reason;
    }
    uint32_t
    LinkGoingDownReason::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU8 ();
    }
    void
    LinkGoingDownReason::Print (std::ostream &os) const
    {
      os << "LinkGoingDownReason = " << static_cast<int> (m_reason) << std::endl;
    }
    void
    LinkGoingDownReason::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU8 (buffer, static_cast<uint8_t> (m_reason), TLV_LINK_GOING_DOWN_REASON);
    }
    uint32_t
    LinkGoingDownReason::TlvDeserialize (Buffer &buffer)
    {
      uint32_t bytesRead = 0;
      uint8_t typ = 0;
      bytesRead += Tlv::DeserializeU8 (buffer, typ, TLV_LINK_GOING_DOWN_REASON);
      m_reason = static_cast<enum LinkGoingDownReason::Type> (typ);
      return bytesRead;
    }
  } // namespace mih
} // namespace ns3
