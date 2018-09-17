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

#include "mih-number-of-queues.h"

namespace ns3 {
  namespace mih {
    NumberOfQueues::NumberOfQueues (uint8_t numberOfQueues) :
      m_numberOfQueues (numberOfQueues)
    {
      SimulationSingleton<TlvObjectFactory<LinkDescriptorsResponse> >::Get ()->AddTlvTypeConstructor (TLV_NUMBER_OF_QUEUES, MakeCallback (&NumberOfQueues::Create));
    }
    NumberOfQueues::NumberOfQueues (NumberOfQueues const &o) :
      m_numberOfQueues (o.m_numberOfQueues)
    {}
    uint8_t 
    NumberOfQueues::GetValue (void)
    {
      return m_numberOfQueues;
    }
    CHOICE_HELPER_IMPLEM (NumberOfQueues, LinkDescriptorsResponse)
    TLV_TYPE_HELPER_IMPLEM (NumberOfQueues, TLV_NUMBER_OF_QUEUES);
  } // namespace mih
} // namespace ns3
