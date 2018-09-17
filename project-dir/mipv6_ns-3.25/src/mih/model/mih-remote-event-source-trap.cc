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

#include "ns3/log.h"
#include "mih-session.h"
#include "mih-header.h"
#include "mih-remote-event-source-trap.h"

NS_LOG_COMPONENT_DEFINE ("RemoteEventSourceTrap");

namespace ns3 {
  namespace mih {
    RemoteEventSourceTrap::RemoteEventSourceTrap (void)
    {
      NS_LOG_FUNCTION (this);
    }
    RemoteEventSourceTrap::~RemoteEventSourceTrap (void)
    {
      NS_LOG_FUNCTION (this);
      m_session = 0;
    }
    void 
    RemoteEventSourceTrap::SetSession (Ptr<Session> session)
    {
      NS_LOG_FUNCTION (this << session);
      m_session = session;
    }
    // Callback accessors;
    void 
    RemoteEventSourceTrap::LinkDetected (MihfId mihfId, 
					 LinkDetectedInformationList linkDetectedInformationList)
    {
      NS_LOG_FUNCTION (this);
      Buffer buffer;
      Ptr<Packet> packet;
      // Fill the buffer;
      NS_ASSERT (mihfId == m_session->GetFromMihfId ());
      mihfId.TlvSerialize (buffer);
      m_session->GetToMihfId ().TlvSerialize (buffer);
      TlvSerialize (buffer, linkDetectedInformationList);
      // Fill in packet to send;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Add Mih Header;
      MihHeader mihHeader;
      uint16_t transactionId = m_session->m_nextTransactionId;
      m_session->m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::EVENT);
      mihHeader.SetOpCode (MihHeader::INDICATION);
      mihHeader.SetActionId (MihHeader::MIH_LINK_DETECTED);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send packet;
      m_session->SendEvent (packet);
    }
    void 
    RemoteEventSourceTrap::LinkUp (MihfId mihfId,
				   LinkIdentifier linkIdentifier, 
				   Address oldAR,
				   Address newAR, 
				   bool ipRenewalFlag, 
				   MobilityManagementSupport mbbSupport)
    {
      NS_LOG_FUNCTION (this);
      Buffer buffer;
      Ptr<Packet> packet;
      // Fill the buffer;
      NS_ASSERT (mihfId == m_session->GetFromMihfId ());
      mihfId.TlvSerialize (buffer);
      m_session->GetToMihfId ().TlvSerialize (buffer);
      linkIdentifier.TlvSerialize (buffer);
      Tlv::Serialize (buffer, oldAR, TLV_OLD_ACCESS_ROUTER);
      Tlv::Serialize (buffer, newAR, TLV_NEW_ACCESS_ROUTER);
      Tlv::SerializeBool (buffer, ipRenewalFlag, TLV_IP_RENEWAL_FLAG);
      mbbSupport.TlvSerialize (buffer);
      // Fill in packet to send;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Add Mih Header;
      MihHeader mihHeader;
      uint16_t transactionId = m_session->m_nextTransactionId;
      m_session->m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::EVENT);
      mihHeader.SetOpCode (MihHeader::INDICATION);
      mihHeader.SetActionId (MihHeader::MIH_LINK_UP);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send packet;
      m_session->SendEvent (packet);
    }
    void
    RemoteEventSourceTrap::LinkDown (MihfId mihfId, 
                                     LinkIdentifier linkIdentifier,
                                     Address oldAR,
                                     LinkDownReason reasonCode)
    {
      NS_LOG_FUNCTION (this);
      Buffer buffer;
      Ptr<Packet> packet;
      // Fill the buffer;
      NS_ASSERT (mihfId == m_session->GetFromMihfId ());
      mihfId.TlvSerialize (buffer);
      m_session->GetToMihfId ().TlvSerialize (buffer);
      linkIdentifier.TlvSerialize (buffer);
      Tlv::Serialize (buffer, oldAR, TLV_OLD_ACCESS_ROUTER);
      reasonCode.TlvSerialize (buffer);
      // Fill in packet to send;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Add Mih Header;
      MihHeader mihHeader;
      uint16_t transactionId = m_session->m_nextTransactionId;
      m_session->m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::EVENT);
      mihHeader.SetOpCode (MihHeader::INDICATION);
      mihHeader.SetActionId (MihHeader::MIH_LINK_DOWN);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send packet;
      m_session->SendEvent (packet);
      
    }
    void
    RemoteEventSourceTrap::LinkParametersReport (MihfId mihfId, 
                                                 LinkIdentifier linkIdentifier, 
                                                 LinkParameterReportList parameters)
    {
      NS_LOG_FUNCTION (this);
      Buffer buffer;
      Ptr<Packet> packet;
      // Fill the buffer;
      NS_ASSERT (mihfId == m_session->GetFromMihfId ());
      mihfId.TlvSerialize (buffer);
      m_session->GetToMihfId ().TlvSerialize (buffer);
      linkIdentifier.TlvSerialize (buffer);
      TlvSerialize (buffer, parameters);
      // Fill in packet to send;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Add Mih Header;
      MihHeader mihHeader;
      uint16_t transactionId = m_session->m_nextTransactionId;
      m_session->m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::EVENT);
      mihHeader.SetOpCode (MihHeader::INDICATION);
      mihHeader.SetActionId (MihHeader::MIH_LINK_PARAMETERS_REPORT);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send packet;
      m_session->SendEvent (packet);
      
    }
    void
    RemoteEventSourceTrap::LinkGoingDown (MihfId mihfId, 
                                          LinkIdentifier linkIdentifier,
                                          uint64_t timeInterval,
                                          LinkGoingDownReason reasonCode)
    {
      NS_LOG_FUNCTION (this);
      Buffer buffer;
      Ptr<Packet> packet;
      // Fill the buffer;
      NS_ASSERT (mihfId == m_session->GetFromMihfId ());
      mihfId.TlvSerialize (buffer);
      m_session->GetToMihfId ().TlvSerialize (buffer);
      linkIdentifier.TlvSerialize (buffer);
      Tlv::SerializeU64 (buffer, timeInterval, TLV_TIME_INTERVAL);
      reasonCode.TlvSerialize (buffer);
      // Fill in packet to send;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Add Mih Header;
      MihHeader mihHeader;
      uint16_t transactionId = m_session->m_nextTransactionId;
      m_session->m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::EVENT);
      mihHeader.SetOpCode (MihHeader::INDICATION);
      mihHeader.SetActionId (MihHeader::MIH_LINK_GOING_DOWN);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send packet;
      m_session->SendEvent (packet);
      
    }
    void 
    RemoteEventSourceTrap::LinkHandoverImminent (MihfId mihfId,
                                                 LinkIdentifier oldLinkId,
                                                 LinkIdentifier newLinkId, 
                                                 Address oldAR, 
                                                 Address newAR)
    {
      NS_LOG_FUNCTION (this);
      Buffer buffer;
      Ptr<Packet> packet;
      // Fill the buffer;
      NS_ASSERT (mihfId == m_session->GetFromMihfId ());
      mihfId.TlvSerialize (buffer);
      m_session->GetToMihfId ().TlvSerialize (buffer);
      oldLinkId.TlvSerialize (buffer);
      newLinkId.TlvSerialize (buffer);
      Tlv::Serialize (buffer, oldAR, TLV_OLD_ACCESS_ROUTER);
      Tlv::Serialize (buffer, newAR, TLV_NEW_ACCESS_ROUTER);
      // Fill in packet to send;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Add Mih Header;
      MihHeader mihHeader;
      uint16_t transactionId = m_session->m_nextTransactionId;
      m_session->m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::EVENT);
      mihHeader.SetOpCode (MihHeader::INDICATION);
      mihHeader.SetActionId (MihHeader::MIH_LINK_HANDOVER_IMMINENT);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send packet;
      m_session->SendEvent (packet);
      
    }
    void
    RemoteEventSourceTrap::LinkHandoverComplete (MihfId mihfId, 
                                                 LinkIdentifier oldLinkId, 
                                                 LinkIdentifier newLinkId, 
                                                 Address oldAR, 
                                                 Address newAR, 
                                                 Status handoverStatus)
    {
      NS_LOG_FUNCTION (this);
      Buffer buffer;
      Ptr<Packet> packet;
      // Fill the buffer;
      NS_ASSERT (mihfId == m_session->GetFromMihfId ());
      mihfId.TlvSerialize (buffer);
      m_session->GetToMihfId ().TlvSerialize (buffer);
      oldLinkId.TlvSerialize (buffer);
      newLinkId.TlvSerialize (buffer);
      Tlv::Serialize (buffer, oldAR, TLV_OLD_ACCESS_ROUTER);
      Tlv::Serialize (buffer, newAR, TLV_NEW_ACCESS_ROUTER);
      handoverStatus.TlvSerialize (buffer);
      // Fill in packet to send;
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Add Mih Header;
      MihHeader mihHeader;
      uint16_t transactionId = m_session->m_nextTransactionId;
      m_session->m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::EVENT);
      mihHeader.SetOpCode (MihHeader::INDICATION);
      mihHeader.SetActionId (MihHeader::MIH_LINK_HANDOVER_COMPLETE);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send packet;
      m_session->SendEvent (packet);
    }
  }
}
