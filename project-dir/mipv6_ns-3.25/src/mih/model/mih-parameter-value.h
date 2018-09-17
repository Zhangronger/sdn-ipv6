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

#ifndef   	MIH_PARAMETER_VALUE_H
#define   	MIH_PARAMETER_VALUE_H

#include "ns3/ref-count-base.h"
#include "mih-choice-helper.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class ParameterValue : public RefCountBase, public Tlv {
    public:
      CHOICE_HELPER_PURE_VIRTUAL_HEADER (ParameterValue);
      TLV_TYPE_HELPER_HEADER (ParameterValue);
      virtual uint32_t GetTlvSerializedSize (void) const = 0;
      virtual void Print (std::ostream &os) const = 0;
      virtual void TlvSerialize (Buffer &buffer) const = 0;
      virtual uint32_t TlvDeserialize (Buffer &buffer) = 0;
    protected:
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_PARAMETER_VALUE_H */
