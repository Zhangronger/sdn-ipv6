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

#ifndef   	MIH_NUMBER_OF_COS_H
#define   	MIH_NUMBER_OF_COS_H

#include <stdint.h>
#include "mih-tlv.h"
#include "mih-link-descriptors-response.h"

namespace ns3 {
  namespace mih {
    class NumberOfCoS : public LinkDescriptorsResponse {
    public:
      NumberOfCoS (uint8_t numberOfCoS = 0);
      NumberOfCoS (NumberOfCoS const &o);
      uint8_t GetValue (void);
      CHOICE_HELPER_HEADER (NumberOfCoS, LinkDescriptorsResponse);
      TLV_TYPE_HELPER_HEADER (NumberOfCoS);
    protected:
      uint8_t m_numberOfCoS;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_NUMBER_OF_COS_H */
