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

#ifndef   	MIH_HEADER_H
#define   	MIH_HEADER_H

#include "ns3/header.h"

namespace ns3 {
  namespace mih {
    class MihHeader : public Header {
    public:
      enum VersionE {
	VERSION_ONE = 1,
      };
      enum ServiceIdE {
	MANAGEMENT = 1,
	EVENT = 2,
	COMMAND = 3,
	INFORMATION = 4,
      };
      enum OpCodeE {
	REQUEST = 1,
	RESPONSE = 2,
	INDICATION = 3,
      };
      enum ActionIdE {
	/* 	MIH messages for Service Management */
	MIH_CAPABILITY_DISCOVER = 1,
	MIH_REGISTER,
	MIH_DEREGISTER,
	MIH_EVENT_SUBSCRIBE,
	MIH_EVENT_UNSUBSCRIBE,
	/* 	MIH messages for Event Service */
	MIH_LINK_DETECTED = 1,
	MIH_LINK_UP,
	MIH_LINK_DOWN,
	MIH_LINK_PARAMETERS_REPORT,
	MIH_LINK_GOING_DOWN,
	MIH_LINK_HANDOVER_IMMINENT,
	MIH_LINK_HANDOVER_COMPLETE,
	/* 	MIH messages for Command Service */
	MIH_LINK_GET_PARAMETERS = 1,
	MIH_LINK_CONFIGURE_THRESHOLDS,
	MIH_LINK_ACTIONS,
	MIH_NET_HO_CANDIDATE_QUERY,
	MIH_MN_HO_CANDIDATE_QUERY,
	MIH_N2N_HO_QUERY_RESOURCES,
	MIH_MN_HO_COMMIT,
	MIH_NET_HO_COMMIT,
	MIH_N2N_HO_COMMIT,
	MIH_MN_HO_COMPLETE,
	MIH_N2N_HO_COMPLETE,
	/* 	MIH messages for Information Service */
	MIH_GET_INFORMATION = 1,
      };
      static TypeId GetTypeId (void);
      virtual TypeId GetInstanceTypeId (void) const;
      MihHeader (void);
      void SetVersion (enum VersionE version);
      enum VersionE GetVersion (void);
      void SetServiceId (enum ServiceIdE sid);
      enum ServiceIdE GetServiceId (void);
      void SetOpCode (enum OpCodeE opcode);
      enum OpCodeE GetOpCode (void);
      void SetActionId (enum ActionIdE aid);
      enum ActionIdE GetActionId (void);
      void SetTransactionId (uint16_t transactionId);
      uint16_t GetTransactionId (void);
      void SetPayloadLength (uint16_t payloadLength);
      uint16_t GetPayloadLength (void);
      virtual uint32_t GetSerializedSize (void) const;
      void Print (std::ostream &os) const;
      virtual void Serialize (Buffer::Iterator start) const;
      virtual uint32_t Deserialize (Buffer::Iterator start);
    protected:
    private:
      uint16_t m_version : 4;
      uint16_t m_ackRequest : 1;
      uint16_t m_ackResponse : 1;
      uint16_t m_uir : 1;
      uint16_t m_moreFragment : 1;
      uint16_t m_fragmentNumber : 7;
      // uint16_t m_mid;
      uint16_t m_sid : 4;
      uint16_t m_opcode : 2;
      uint16_t m_aid : 10;
      uint16_t m_transactionId : 12;
      uint16_t m_payloadLength;
    };
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_HEADER_H */
