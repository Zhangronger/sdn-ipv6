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

#include "mih-mobility-management-support.h"

namespace ns3 {
  namespace mih {
    MobilityManagementSupport::MobilityManagementSupport (uint16_t supportedProtocols) :
      m_bitmap (supportedProtocols)
    {}
    MobilityManagementSupport::MobilityManagementSupport (MobilityManagementSupport const &o) :
      m_bitmap (o.m_bitmap)
    {}
    TLV_TYPE_HELPER_IMPLEM (MobilityManagementSupport, TLV_MOBILITY_MANAGEMENT_SUPPORT)
    uint16_t 
    MobilityManagementSupport::GetSupportedProtocols (void)
    {
      return m_bitmap;
    }
    uint32_t
    MobilityManagementSupport::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU16 ();
    }
    void
    MobilityManagementSupport::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU16 (buffer, m_bitmap, TLV_MOBILITY_MANAGEMENT_SUPPORT);
    }
    uint32_t
    MobilityManagementSupport::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeU16 (buffer, m_bitmap, TLV_MOBILITY_MANAGEMENT_SUPPORT);
    }
  } // namespace mih
} // namespace ns3
