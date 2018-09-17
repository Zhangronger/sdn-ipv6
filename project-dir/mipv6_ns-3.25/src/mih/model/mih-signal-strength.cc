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

#include "mih-signal-strength.h"

namespace ns3 {
  namespace mih {
    SignalStrength::SignalStrength (uint64_t signalStrength) : 
      m_signalStrength (signalStrength)
    {}
    SignalStrength::SignalStrength (SignalStrength const &o) :
      m_signalStrength (o.m_signalStrength)
    {}
    TLV_TYPE_HELPER_IMPLEM (SignalStrength, TLV_SIGNAL_STRENGTH);
    uint64_t 
    SignalStrength::GetValue (void)
    {
      return m_signalStrength;
    }
    uint32_t
    SignalStrength::GetTlvSerializedSize (void) const
    {
      return Tlv::GetSerializedSizeU64 ();
    }
    void
    SignalStrength::TlvSerialize (Buffer &buffer) const
    {
      Tlv::SerializeU64 (buffer, m_signalStrength, TLV_SIGNAL_STRENGTH);
    }
    uint32_t
    SignalStrength::TlvDeserialize (Buffer &buffer)
    {
      return Tlv::DeserializeU64 (buffer, m_signalStrength, TLV_SIGNAL_STRENGTH);
    }
  } // namespace mih
} // namespace ns3
