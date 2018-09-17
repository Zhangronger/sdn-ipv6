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

#ifndef   	MIH_THRESHOLD_H
#define   	MIH_THRESHOLD_H

#include <stdint.h>
#include <vector>
#include "ns3/ptr.h"
#include "ns3/ref-count-base.h"
#include "mih-tlv.h"

namespace ns3 {
  namespace mih {
    class Threshold : public RefCountBase, public Tlv {
    public:
      enum CrossDirectionCode {
	ABOVE_THRESHOLD =  0,
	BELOW_THRESHOLD =  1,
      };
      Threshold (uint16_t thresholdValue = 0,
		 enum CrossDirectionCode crossDirection = Threshold::ABOVE_THRESHOLD);
      Threshold (Threshold const &o);
      uint16_t GetThresholdValue (void);
      enum CrossDirectionCode GetCrossDirection (void);
      virtual void Print (std::ostream &os) const;
      virtual uint32_t GetTlvSerializedSize (void) const;
      virtual void TlvSerialize (Buffer &buffer) const;
      virtual uint32_t TlvDeserialize (Buffer &buffer);
      static Ptr<Threshold> CreateFromTlvType (uint8_t tlvTypeValue);
      TLV_TYPE_HELPER_HEADER (Threshold);
    protected:
      uint16_t m_value;
      enum CrossDirectionCode m_crossDirection;
    };
    typedef std::vector<Ptr<Threshold> > ThresholdList;
    typedef ThresholdList::iterator ThresholdListI;
    uint32_t GetTlvSerializedSize (const ThresholdList &thresholdList);
    void TlvSerialize (Buffer &buffer, const ThresholdList &thresholdList);
    uint32_t TlvDeserialize (Buffer &buffer, ThresholdList &thresholdList);
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_THRESHOLD_H */
