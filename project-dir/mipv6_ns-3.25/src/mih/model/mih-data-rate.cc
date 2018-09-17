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

#include "mih-data-rate.h"

namespace ns3 {
  namespace mih {
    DataRate::DataRate (uint32_t value) :
      m_data (value)
    {}
    DataRate::DataRate (DataRate const &o) :
      m_data (o.m_data)
    {}
    TLV_TYPE_HELPER_IMPLEM (DataRate, TLV_DATA_RATE)
    uint32_t 
    DataRate::GetValue (void)
    {
      return m_data;
    }
    uint32_t
    DataRate::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU32 ();
    }
    void
    DataRate::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU32 (buffer, m_data, TLV_DATA_RATE);
    }
    uint32_t
    DataRate::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeU32 (buffer, m_data, TLV_DATA_RATE);
    }
  } // namespace mih
} // namespace ns3
