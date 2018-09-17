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

#include "mih-operation-mode.h"

namespace ns3 {
  namespace mih {
    OperationMode::OperationMode (enum OperationMode::Type mode) :
      m_powerOperationMode (mode)
    {
      SimulationSingleton<TlvObjectFactory<LinkStatesResponse> >::Get ()->AddTlvTypeConstructor (TLV_OPERATION_MODE,
                                                                                            MakeCallback (&OperationMode::Create));
    }
    OperationMode::OperationMode (OperationMode const &o) :
      m_powerOperationMode (o.m_powerOperationMode)
    {}
    enum OperationMode::Type
    OperationMode::GetPowerMode (void)
    {
      return m_powerOperationMode;
    }
    CHOICE_HELPER_IMPLEM (OperationMode, LinkStatesResponse)
    TLV_TYPE_HELPER_IMPLEM (OperationMode, TLV_OPERATION_MODE)
  } // namespace mih
} // namespace ns3
