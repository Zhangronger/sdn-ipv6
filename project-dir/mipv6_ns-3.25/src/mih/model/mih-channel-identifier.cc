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

#include "mih-channel-identifier.h"

namespace ns3 {
  namespace mih {
    ChannelIdentifier::ChannelIdentifier (uint16_t channel) :
      m_channel (channel)
    {
      SimulationSingleton<TlvObjectFactory<LinkStatesResponse> >::Get ()->AddTlvTypeConstructor (TLV_CHANNEL_IDENTIFIER,
                                                                                                 MakeCallback (&ChannelIdentifier::Create));
    }
    ChannelIdentifier::ChannelIdentifier (ChannelIdentifier const &o)
    {
      m_channel = o.m_channel;
    }
    CHOICE_HELPER_IMPLEM (ChannelIdentifier, LinkStatesResponse)
    TLV_TYPE_HELPER_IMPLEM (ChannelIdentifier, TLV_CHANNEL_IDENTIFIER)
    uint16_t
    ChannelIdentifier::GetValue (void)
    {
      return m_channel;
    }
  } // namespace mih
} // namespace ns3
