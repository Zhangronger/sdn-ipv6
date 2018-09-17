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

#include "mih-number-of-cos.h"

namespace ns3 {
  namespace mih {
    NumberOfCoS::NumberOfCoS (uint8_t numberOfCoS) :
      m_numberOfCoS (numberOfCoS)
    {
      SimulationSingleton<TlvObjectFactory<LinkDescriptorsResponse> >::Get ()->AddTlvTypeConstructor (TLV_NUMBER_OF_COS,
                                                                                                   MakeCallback (&NumberOfCoS::Create));
    }
    NumberOfCoS::NumberOfCoS (NumberOfCoS const &o) :
      m_numberOfCoS (o.m_numberOfCoS)
    {}
    uint8_t
    NumberOfCoS::GetValue (void)
    {
      return m_numberOfCoS;
    }
      CHOICE_HELPER_IMPLEM (NumberOfCoS, LinkDescriptorsResponse)
      TLV_TYPE_HELPER_IMPLEM (NumberOfCoS, TLV_NUMBER_OF_COS)
  } // namespace mih
} // namespace ns3
