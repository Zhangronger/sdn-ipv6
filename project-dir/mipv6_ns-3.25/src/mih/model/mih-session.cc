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
#include "ns3/assert.h"
#include "ns3/simulator.h"
#include "mih-header.h"
#include "mih-session.h"

NS_LOG_COMPONENT_DEFINE ("Session");

namespace ns3 {
  namespace mih {
    Session::Session (void) :
      m_sourceMihfid (),
      m_sourceInetSocketAddress (),
      m_destinationMihfid (),
      m_destinationInetSocketAddress (),
      m_socket (0),
      m_initComplete (false),
      m_isRegistered (false),
      m_nextTransactionId (0),
      m_delay (0),
      m_maxSize (0),
      m_remoteEventDestinationTrap (),
      m_remoteEventSourceTrap ()
    {
      NS_LOG_FUNCTION (this);
    }
    Session::Session (MihfId sourceMihfid, Address sourceIp, 
		      MihfId destinationMihfid, Address destinationIp,
                      Ptr<Socket> socket) :
      m_sourceMihfid (sourceMihfid),
      m_sourceInetSocketAddress (sourceIp),
      m_destinationMihfid (destinationMihfid),
      m_destinationInetSocketAddress (destinationIp),
      m_socket (socket),
      m_initComplete (false),
      m_nextTransactionId (0),
      m_delay (0),
      m_maxSize (0),
      m_remoteEventDestinationTrap (),
      m_remoteEventSourceTrap ()
    {
      NS_LOG_FUNCTION (this);
      m_remoteEventSourceTrap.SetSession (Ptr<Session>(this, false));
    }
    Session::~Session (void)
    {
      NS_LOG_FUNCTION (this);
      m_socket = 0;
    }
    MihfId
    Session::GetToMihfId (void)
    {
      NS_LOG_FUNCTION (this);
      return m_destinationMihfid;
    }
    void
    Session::SetToMihfId (MihfId mihfid)
    {
      NS_LOG_FUNCTION (this);
      m_destinationMihfid = mihfid;
    }
    MihfId
    Session::GetFromMihfId (void)
    {
      NS_LOG_FUNCTION (this);
      return m_sourceMihfid;
    }
    void
    Session::SetFromMihfId (MihfId mihfid)
    {
      NS_LOG_FUNCTION (this);
      m_sourceMihfid = mihfid;
    }
    Address
    Session::GetToAddress (void)
    {
      NS_LOG_FUNCTION (this);
      return m_destinationInetSocketAddress;
    }
    void
    Session::SetToAddress (Address to)
    {
      NS_LOG_FUNCTION (this);
      m_destinationInetSocketAddress = to;
    }
    Address
    Session::GetFromAddress (void)
    {
      NS_LOG_FUNCTION (this);
      return m_sourceInetSocketAddress;
    }
    void
    Session::SetFromAddress (Address from)
    {
      NS_LOG_FUNCTION (this);
      m_sourceInetSocketAddress = from;
    }
    void
    Session::SetSocket (Ptr<Socket> socket)
    {
      NS_LOG_FUNCTION (this);
      m_socket = socket;
    }
    Ptr<Socket>
    Session::GetSocket (void)
    {
      NS_LOG_FUNCTION (this);
      return m_socket;
    }
    bool 
    Session::IsInitComplete (void)
    {
      NS_LOG_FUNCTION (this);
      return m_initComplete;
    }
    void 
    Session::SetInitComplete (void)
    {
      NS_LOG_FUNCTION (this);
      m_initComplete = true;
    }
    bool
    Session::IsRegistered (void)
    {
      return m_isRegistered;
    }
    void
    Session::SetRegistered (void)
    {
      m_isRegistered = true;
    }
    void
    Session::NotifyNewPendingRequest (void)
    {
      NS_LOG_FUNCTION (this);
      if (m_currentTransaction)
        {
          NS_ASSERT (m_currentTransaction->GetState () == Transaction::WAIT_RESPONSE_MSG);
          return;
        }
      m_currentTransaction = m_pendingRequestQueue.front ();
      m_currentTransaction->SetState (Transaction::WAIT_RESPONSE_MSG);
      m_pendingRequestQueue.pop_front ();
      m_socket->Send (m_currentTransaction->GetPacket ());
      //      m_socket->SendTo (m_currentTransaction->GetPacket (), 0, m_destinationInetSocketAddress);
    }
    void
    Session::NotifyPendingResponseDone (void)
    {
      NS_LOG_FUNCTION (this);
      // DisposePendingResponse ();
      Simulator::ScheduleNow(&Session::DisposePendingResponse, this);
    }
    void
    Session::NotifyPendingCurrentRequestDone (void)
    {
      NS_LOG_FUNCTION (this);
      Simulator::ScheduleNow(&Session::DisposePendingCurrentRequest, this);
    }
    void
    Session::DisposePendingResponse (void)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (m_pendingResponseTransaction->IsToBeDeleted ());
      m_pendingResponseTransaction = 0;
    }
    void
    Session::DisposePendingCurrentRequest (void)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (m_currentTransaction->IsToBeDeleted ());
      m_currentTransaction = 0;
      if (m_pendingRequestQueue.size () != 0)
        {
          m_currentTransaction = m_pendingRequestQueue.front ();
          m_currentTransaction->SetState (Transaction::WAIT_RESPONSE_MSG);
          m_pendingRequestQueue.pop_front ();
          m_socket->Send (m_currentTransaction->GetPacket ());
          //          m_socket->SendTo (m_currentTransaction->GetPacket (), 0, m_destinationInetSocketAddress);
        }
    }
    // Remote events access methods;
    RemoteEventSourceTrap&
    Session::GetRemoteEventSourceTrap (void)
    {
      NS_LOG_FUNCTION (this);
      return m_remoteEventSourceTrap;
    }
    RemoteEventDestinationTrap& 
    Session::GetRemoteEventDestinationTrap (void)
    {
      NS_LOG_FUNCTION (this);
      return m_remoteEventDestinationTrap;
    }
    // Event transport;
    void 
    Session::SendEvent (Ptr<Packet> packet)
    {
      NS_LOG_FUNCTION (this);
      //m_socket->Send (packet);
      m_socket->SendTo (packet, 0, m_destinationInetSocketAddress);
    }
    // Command Service transport;
    void 
    Session::SendRegisterRequest (Ptr<Packet> packet, 
				  MihRegisterConfirmCallback registerConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      MihHeader mihHeader;
      uint16_t transactionId = m_nextTransactionId;
      m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::MANAGEMENT);
      mihHeader.SetOpCode (MihHeader::REQUEST);
      mihHeader.SetActionId (MihHeader::MIH_REGISTER);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);

      Ptr<RegisterRequestTransaction> registerRequestTransaction = 
        Create<RegisterRequestTransaction> (packet, 
                                            GetFromMihfId (), 
                                            GetToMihfId (), 
                                            GetToAddress (), 
                                            transactionId,
                                            registerConfirmCallback);
      registerRequestTransaction->SetNotifyDoneCallback (MakeCallback (&Session::NotifyPendingCurrentRequestDone, 
                                                                       this));
      m_pendingRequestQueue.push_back (registerRequestTransaction);
      Simulator::ScheduleNow (&Session::NotifyNewPendingRequest, this);
    }
    MihRegisterResponseCallback 
    Session::ReceiveRegisterRequest (Ptr<Packet> packet, 
                                     uint16_t transactionId)
    {
      NS_LOG_FUNCTION (this);
      Ptr<RegisterResponseTransaction> registerResponseTransaction = 
        Create<RegisterResponseTransaction> (packet, 
                                             GetFromMihfId (), 
                                             GetToMihfId (), 
                                             GetToAddress (), 
                                             transactionId,
                                             m_socket);
      registerResponseTransaction->SetNotifyDoneCallback (MakeCallback (&Session::NotifyPendingResponseDone, 
                                                                        this));
      NS_ASSERT (m_pendingResponseTransaction == 0);
      NS_LOG_WARN ("Check to assure that the following line is bug free!");
      m_pendingResponseTransaction = registerResponseTransaction;
      return MakeCallback (&RegisterResponseTransaction::SendRegisterResponse, 
                           registerResponseTransaction);
    }
    void 
    Session::ReceiveRegisterResponse (MihfId fromMihfId, 
                                      Status status, 
                                      uint32_t validLifeTime)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (m_currentTransaction != 0);
      NS_ASSERT (m_currentTransaction->GetState () == Transaction::WAIT_RESPONSE_MSG);
      NS_ASSERT (m_currentTransaction->IsToBeDeleted () == false);
      Ptr<RegisterRequestTransaction> transaction = 
        DynamicCast<RegisterRequestTransaction, Transaction> (m_currentTransaction);
      NS_ASSERT (transaction != 0);
      transaction->RegisterConfirm (fromMihfId, status, validLifeTime);
      transaction->SetState (Transaction::SUCCESS);
      transaction->SetToBeDeleted ();
    }
    void 
    Session::SendCapabilityDiscoverRequest (Ptr<Packet> packet,
                                            MihCapabilityDiscoverConfirmCallback capabilityDiscoverConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      MihHeader mihHeader;
      uint16_t transactionId = m_nextTransactionId;
      m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::MANAGEMENT);
      mihHeader.SetOpCode (MihHeader::REQUEST);
      mihHeader.SetActionId (MihHeader::MIH_CAPABILITY_DISCOVER);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);

      Ptr<CapabilityDiscoverRequestTransaction> capabilityDiscoverRequestTransaction = 
        Create<CapabilityDiscoverRequestTransaction> (packet, 
                                                      GetFromMihfId (), 
                                                      GetToMihfId (), 
                                                      GetToAddress (), 
                                                      transactionId,
                                                      capabilityDiscoverConfirmCallback);
      capabilityDiscoverRequestTransaction->SetNotifyDoneCallback (MakeCallback (&Session::NotifyPendingCurrentRequestDone, 
                                                                                 this));
      m_pendingRequestQueue.push_back (capabilityDiscoverRequestTransaction);
      Simulator::ScheduleNow (&Session::NotifyNewPendingRequest, this);
    }
    MihCapabilityDiscoverResponseCallback 
    Session::ReceiveCapabilityDiscoverRequest (Ptr<Packet> packet, 
                                               uint16_t transactionId)
    {
      NS_LOG_FUNCTION (this);
      Ptr<CapabilityDiscoverResponseTransaction> capabilityDiscoverResponseTransaction =
        Create<CapabilityDiscoverResponseTransaction> (packet,
                                                       GetFromMihfId (), 
                                                       GetToMihfId (), 
                                                       GetToAddress (), 
                                                       transactionId,
                                                       m_socket);
      capabilityDiscoverResponseTransaction->SetNotifyDoneCallback (MakeCallback (&Session::NotifyPendingResponseDone,
                                                                                  this));
      NS_ASSERT (m_pendingResponseTransaction == 0);
      NS_LOG_WARN ("Check to assure that the following line is bug free!");
      m_pendingResponseTransaction = capabilityDiscoverResponseTransaction;
      return MakeCallback (&CapabilityDiscoverResponseTransaction::SendCapabilityDiscoverResponse,
                           capabilityDiscoverResponseTransaction);
    }
    void
    Session::ReceiveCapabilityDiscoverResponse (MihfId fromMihfId,
                                                Status status,
                                                NetworkTypeAddressList networkTypeAddresses,
                                                EventList events,
                                                MihCommandList commands,
                                                InformationServiceQueryTypeList miisQueries,
                                                TransportSupportList transportOptions,
                                                MakeBeforeBreakSupportList mbbSupportList)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (m_currentTransaction != 0);
      NS_ASSERT (m_currentTransaction->GetState () == Transaction::WAIT_RESPONSE_MSG);
      NS_ASSERT (m_currentTransaction->IsToBeDeleted () == false);
      Ptr<CapabilityDiscoverRequestTransaction> transaction =
        DynamicCast<CapabilityDiscoverRequestTransaction, Transaction> (m_currentTransaction);
      NS_ASSERT (transaction != 0);
      transaction->CapabilityDiscoverConfirm (fromMihfId,
                                              status,
                                              networkTypeAddresses,
                                              events,
                                              commands,
                                              miisQueries,
                                              transportOptions,
                                              mbbSupportList);
      transaction->SetState (Transaction::SUCCESS);
      transaction->SetToBeDeleted ();
    }
    void
    Session::SendEventSubscribeRequest (Ptr<Packet> packet,
                                        EventList events,
                                        MihLinkDetectedIndicationCallback linkDetectedEventCallback1,
                                        MihLinkUpIndicationCallback linkUpEventCallback2,
                                        MihLinkDownIndicationCallback linkDownEventCallback3,
                                        MihLinkParametersReportIndicationCallback linkParamReportEventCallback4,
                                        MihLinkGoingDownIndicationCallback linkGoingDownEventCallback5,
                                        MihLinkHandoverImminentIndicationCallback linkHOImminentEventCallback6,
                                        MihLinkHandoverCompleteIndicationCallback linkHOCompleteEventCallback7,
                                        MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusEventCallback8,
                                        MihEventSubscribeConfirmCallback subscribeConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      MihHeader mihHeader;
      uint16_t transactionId = m_nextTransactionId;
      m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::MANAGEMENT);
      mihHeader.SetOpCode (MihHeader::REQUEST);
      mihHeader.SetActionId (MihHeader::MIH_EVENT_SUBSCRIBE);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);

      Ptr<EventSubscribeRequestTransaction> eventSubscribeRequestTransaction = 
        Create<EventSubscribeRequestTransaction> (packet,
                                                  GetFromMihfId (), 
                                                  GetToMihfId (), 
                                                  GetToAddress (), 
                                                  transactionId,
                                                  subscribeConfirmCallback);
      
      eventSubscribeRequestTransaction->SetNotifyDoneCallback (MakeCallback (&Session::NotifyPendingCurrentRequestDone,
                                                                             this));
      m_pendingRequestQueue.push_back (eventSubscribeRequestTransaction);

      // Fill RemoteEventDestinationTrap;
      if (events.IsOfType (EventList::LINK_DETECTED))
        {
          m_remoteEventDestinationTrap.AddLinkDetectedCallback (linkDetectedEventCallback1);
        }
      if (events.IsOfType (EventList::LINK_UP))
        {
          m_remoteEventDestinationTrap.AddLinkUpCallback (linkUpEventCallback2);
        }
      if (events.IsOfType (EventList::LINK_DOWN))
        {
          m_remoteEventDestinationTrap.AddLinkDownCallback (linkDownEventCallback3) ;
        }
      if (events.IsOfType (EventList::LINK_PARAMETERS_REPORT))
        {
          m_remoteEventDestinationTrap.AddLinkParamatersReportCallback (linkParamReportEventCallback4);
        }
      if (events.IsOfType (EventList::LINK_GOING_DOWN))
        {
          m_remoteEventDestinationTrap.AddLinkGoingDownCallback (linkGoingDownEventCallback5);
        }
      if (events.IsOfType (EventList::LINK_HANDOVER_IMMINENT))
        {
          m_remoteEventDestinationTrap.AddLinkHandoverImminentCallback (linkHOImminentEventCallback6);
        }
      if (events.IsOfType (EventList::LINK_HANDOVER_COMPLETE))
        {
          m_remoteEventDestinationTrap.AddLinkHandoverCompleteCallback (linkHOCompleteEventCallback7);
        }
      if (events.IsOfType (EventList::LINK_PDU_TRANSMIT_STATUS))
        {
          m_remoteEventDestinationTrap.AddLinkPduTxStatusCallback (linkPduTxStatusEventCallback8);
        }
      Simulator::ScheduleNow (&Session::NotifyNewPendingRequest, this);
    }
    MihEventSubscribeConfirmCallback 
    Session::ReceiveEventSubscribeRequest (Ptr<Packet> packet, 
                                           uint16_t transactionId)
    {
      NS_LOG_FUNCTION (this);
      Ptr<EventSubscribeResponseTransaction> eventSubscribeResponseTransaction = 
        Create<EventSubscribeResponseTransaction> (packet,
                                                   GetFromMihfId (), 
                                                   GetToMihfId (), 
                                                   GetToAddress (), 
                                                   transactionId,
                                                   m_socket);
      eventSubscribeResponseTransaction->SetNotifyDoneCallback (MakeCallback (&Session::NotifyPendingResponseDone, 
                                                                              this));
      NS_ASSERT (m_pendingResponseTransaction == 0);
      m_pendingResponseTransaction = eventSubscribeResponseTransaction;
      return MakeCallback (&EventSubscribeResponseTransaction::SendEventSubcribeResponse, 
                           eventSubscribeResponseTransaction);
    }
    void 
    Session::ReceiveEventSubscribeResponse (MihfId fromMihfId, 
                                            Status status, 
                                            LinkIdentifier linkIdentifier, 
                                            EventList events)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (m_currentTransaction != 0);
      NS_ASSERT (m_currentTransaction->GetState () == Transaction::WAIT_RESPONSE_MSG);
      NS_ASSERT (m_currentTransaction->IsToBeDeleted () == false);
      Ptr<EventSubscribeRequestTransaction> transaction = 
        DynamicCast<EventSubscribeRequestTransaction, Transaction> (m_currentTransaction);
      NS_ASSERT (transaction != 0);
      transaction->EventSubscribeConfirm (fromMihfId,
                                          status,
                                          linkIdentifier,
                                          events);
      transaction->SetState (Transaction::SUCCESS);
      transaction->SetToBeDeleted ();
    }
    void 
    Session::SendLinkGetParametersRequest (Ptr<Packet> packet,
                                           MihLinkGetParametersConfirmCallback getParamtersConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      MihHeader mihHeader;
      uint16_t transactionId = m_nextTransactionId;
      m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::COMMAND);
      mihHeader.SetOpCode (MihHeader::REQUEST);
      mihHeader.SetActionId (MihHeader::MIH_LINK_GET_PARAMETERS);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      
      Ptr<LinkGetParametersRequestTransaction> linkGetParametersRequestTransaction = 
        Create<LinkGetParametersRequestTransaction> (packet,
                                                     GetFromMihfId (),
                                                     GetToMihfId (),
                                                     GetToAddress (),
                                                     transactionId,
                                                     getParamtersConfirmCallback);
      linkGetParametersRequestTransaction->SetNotifyDoneCallback (MakeCallback (&Session::NotifyPendingCurrentRequestDone, 
                                                                                this));
      m_pendingRequestQueue.push_back (linkGetParametersRequestTransaction);
      Simulator::ScheduleNow (&Session::NotifyNewPendingRequest, this);
    }
    MihLinkGetParametersConfirmCallback 
    Session::ReceiveLinkGetParametersRequest (Ptr<Packet> packet, 
                                              uint16_t transactionId)
    {
      NS_LOG_FUNCTION (this);
      Ptr<LinkGetParametersResponseTransaction> linkGetParametersResponseTransaction = 
        Create<LinkGetParametersResponseTransaction> (packet,
                                                      GetFromMihfId (), 
                                                      GetToMihfId (), 
                                                      GetToAddress (), 
                                                      transactionId,
                                                      m_socket);
      linkGetParametersResponseTransaction->SetNotifyDoneCallback (MakeCallback (&Session::NotifyPendingResponseDone, 
                                                                                 this));
      NS_ASSERT (m_pendingResponseTransaction == 0);
      m_pendingResponseTransaction = linkGetParametersResponseTransaction;
      return MakeCallback (&LinkGetParametersResponseTransaction::SendLinkGetParametersResponse, 
                           linkGetParametersResponseTransaction);
    }
    void 
    Session::ReceiveLinkGetParametersResponse (MihfId mihfId, 
                                               Status status,
                                               DeviceStatesResponseList deviceStatesResponseList,
                                               LinkStatusResponseList linkStatusResponseList)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (m_currentTransaction != 0);
      NS_ASSERT (m_currentTransaction->GetState () == Transaction::WAIT_RESPONSE_MSG);
      NS_ASSERT (m_currentTransaction->IsToBeDeleted () == false);
      Ptr<LinkGetParametersRequestTransaction> transaction =
        DynamicCast<LinkGetParametersRequestTransaction, Transaction> (m_currentTransaction);
      NS_ASSERT (transaction != 0);
      transaction->LinkGetParametersConfirm (mihfId,
                                             status,
                                             deviceStatesResponseList,
                                             linkStatusResponseList);
      transaction->SetState (Transaction::SUCCESS);
      transaction->SetToBeDeleted ();
    }
    void 
    Session::SendLinkConfigureThresholdsRequest (Ptr<Packet> packet,
                                                 MihLinkConfigureThresholdsConfirmCallback configureThresholdsConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
      MihHeader mihHeader;
      uint16_t transactionId = m_nextTransactionId;
      m_nextTransactionId++;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::COMMAND);
      mihHeader.SetOpCode (MihHeader::REQUEST);
      mihHeader.SetActionId (MihHeader::MIH_LINK_CONFIGURE_THRESHOLDS);
      mihHeader.SetTransactionId (transactionId);
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      
      Ptr<LinkConfigureThresholdsRequestTransaction> linkConfigureThresholdsRequestTransaction = 
        Create<LinkConfigureThresholdsRequestTransaction> (packet,
                                                           GetFromMihfId (),
                                                           GetToMihfId (),
                                                           GetToAddress (),
                                                           transactionId,
                                                           configureThresholdsConfirmCallback);
      linkConfigureThresholdsRequestTransaction->SetNotifyDoneCallback (MakeCallback (&Session::NotifyPendingCurrentRequestDone, 
                                                                                this));
      m_pendingRequestQueue.push_back (linkConfigureThresholdsRequestTransaction);
      Simulator::ScheduleNow (&Session::NotifyNewPendingRequest, this);
    }
    MihLinkConfigureThresholdsConfirmCallback 
    Session::ReceiveLinkConfigureThresholdsRequest (Ptr<Packet> packet, 
                                                    uint16_t transactionId)
    {
      NS_LOG_FUNCTION (this);
      Ptr<LinkConfigureThresholdsResponseTransaction> linkConfigureThresholdsResponseTransaction = 
        Create<LinkConfigureThresholdsResponseTransaction> (packet,
                                                            GetFromMihfId (), 
                                                            GetToMihfId (), 
                                                            GetToAddress (), 
                                                            transactionId,
                                                            m_socket);
      linkConfigureThresholdsResponseTransaction->SetNotifyDoneCallback (MakeCallback (&Session::NotifyPendingResponseDone, 
                                                                                       this));
      NS_ASSERT (m_pendingResponseTransaction == 0);
      m_pendingResponseTransaction = linkConfigureThresholdsResponseTransaction;
      return MakeCallback (&LinkConfigureThresholdsResponseTransaction::SendLinkConfigureThresholdsResponse, 
                           linkConfigureThresholdsResponseTransaction);
    }
    void 
    Session::ReceiveLinkConfigureThresholdsResponse (MihfId mihfId, 
                                                     Status status,
                                                     LinkIdentifier linkIdentifier, 
                                                     LinkConfigurationStatusList linkConfigurationStatusList)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (m_currentTransaction != 0);
      NS_ASSERT (m_currentTransaction->GetState () == Transaction::WAIT_RESPONSE_MSG);
      NS_ASSERT (m_currentTransaction->IsToBeDeleted () == false);
      Ptr<LinkConfigureThresholdsRequestTransaction> transaction =
        DynamicCast<LinkConfigureThresholdsRequestTransaction, Transaction> (m_currentTransaction);
      NS_ASSERT (transaction != 0);
      transaction->LinkConfigureThresholdsConfirm (mihfId,
                                                   status,
                                                   linkIdentifier,
                                                   linkConfigurationStatusList);
      transaction->SetState (Transaction::SUCCESS);
      transaction->SetToBeDeleted ();
    }
  } // namespace mih
} // namespace ns3
