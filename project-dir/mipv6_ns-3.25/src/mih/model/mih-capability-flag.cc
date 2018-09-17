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

#include "mih-capability-flag.h"

namespace ns3 {
  namespace mih {
    MihCapabilityFlag::MihCapabilityFlag (uint8_t supportedServices) :
      m_bitmap (supportedServices)
    {}
    MihCapabilityFlag::MihCapabilityFlag (MihCapabilityFlag const &o) :
      m_bitmap (o.m_bitmap)
    {}
    TLV_TYPE_HELPER_IMPLEM (MihCapabilityFlag, TLV_CAPABILITY_FLAG)
    uint8_t
    MihCapabilityFlag::GetCapabilityList (void)
    {
      return m_bitmap;
    }
    uint32_t
    MihCapabilityFlag::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU8 ();
    }
    void
    MihCapabilityFlag::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU8 (buffer, m_bitmap, TLV_CAPABILITY_FLAG);
    }
    uint32_t
    MihCapabilityFlag::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeU8 (buffer, m_bitmap, TLV_CAPABILITY_FLAG);
    }
  } // namespace mih
} // namespace ns3
