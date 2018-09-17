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

#ifndef   	MIH_OPERATION_MODE_H
#define   	MIH_OPERATION_MODE_H

#include "mih-tlv.h"
#include "mih-link-states-response.h"
#include "mih-choice-helper.h"

namespace ns3 {
  namespace mih {
    class OperationMode : public LinkStatesResponse {
    public:
      enum Type {
        INVALID = 0xff,
	NORMAL_MODE = 0,
	POWER_SAVING_MODE = 1,
	POWER_DOWN = 2,
      };
      OperationMode (enum Type mode = OperationMode::INVALID);
      OperationMode (OperationMode const &o);
      enum Type GetPowerMode (void);
      CHOICE_HELPER_HEADER (OperationMode, LinkStatesResponse);
      TLV_TYPE_HELPER_HEADER (OperationMode);
    protected:
      enum Type m_powerOperationMode;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_OPERATION_MODE_H */
