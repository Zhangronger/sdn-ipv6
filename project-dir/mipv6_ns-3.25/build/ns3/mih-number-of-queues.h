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

#ifndef   	MIH_NUMBER_OF_QUEUES_H
#define   	MIH_NUMBER_OF_QUEUES_H

#include <stdint.h>
#include "mih-tlv.h"
#include "mih-link-descriptors-response.h"

namespace ns3 {
  namespace mih {
    class NumberOfQueues : public LinkDescriptorsResponse {
    public:
      NumberOfQueues (uint8_t numberOfQueues = 0);
      NumberOfQueues (NumberOfQueues const &o);
      uint8_t GetValue (void);
      CHOICE_HELPER_HEADER (NumberOfQueues, LinkDescriptorsResponse);
      TLV_TYPE_HELPER_HEADER (NumberOfQueues);
    protected:
      uint8_t m_numberOfQueues;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_NUMBER_OF_QUEUES_H */
