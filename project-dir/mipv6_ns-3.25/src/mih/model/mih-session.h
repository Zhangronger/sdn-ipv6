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

#ifndef   	MIH_SESSION_H
#define   	MIH_SESSION_H

#include <vector>
#include "ns3/ref-count-base.h"
#include "ns3/packet.h"
#include "ns3/socket.h"
#include "mih-transaction.h"
#include "mih-callbacks.h"
#include "mih-remote-event-destination-trap.h"
#include "mih-remote-event-source-trap.h"

namespace ns3 {
  namespace mih {
    class Session : public RefCountBase {
    public:
      Session (void);
      Session (MihfId sourceMihfid, Address sourceIp, 
	       MihfId destinationMihfid, Address destinationIp,
               Ptr<Socket> socket);
      ~Session (void);
      MihfId GetToMihfId (void);
      void SetToMihfId (MihfId mihfid);
      Address GetToAddress (void);
      void SetToAddress (Address to);
      MihfId GetFromMihfId (void);
      void SetFromMihfId (MihfId mihfid);
      Address GetFromAddress (void);
      void SetFromAddress (Address from);
      Ptr<Socket> GetSocket (void);
      void SetSocket (Ptr<Socket> socket);
      bool IsInitComplete (void);
      void SetInitComplete (void);
      bool IsRegistered (void);
      void SetRegistered (void);
      // Register
      void SendRegisterRequest (Ptr<Packet> packet, 
				MihRegisterConfirmCallback registerConfirmCallback);
      MihRegisterResponseCallback ReceiveRegisterRequest (Ptr<Packet> packet, 
                                                          uint16_t transactionId);
      void ReceiveRegisterResponse (MihfId from, 
                                    Status status, 
                                    uint32_t validLifeTime = 0);
      // Capability Discover
      void SendCapabilityDiscoverRequest (Ptr<Packet> packet, 
                                          MihCapabilityDiscoverConfirmCallback capabilityDiscoverConfirmCallback);
      MihCapabilityDiscoverResponseCallback ReceiveCapabilityDiscoverRequest (Ptr<Packet> packet, 
                                                                              uint16_t transactionId);
      void ReceiveCapabilityDiscoverResponse (MihfId from,
                                              Status status,
                                              NetworkTypeAddressList networkTypeAddresses,
                                              EventList events,
                                              MihCommandList commands,
                                              InformationServiceQueryTypeList miisQueries,
                                              TransportSupportList transportOptions,
                                              MakeBeforeBreakSupportList mbbSupportList);
      // Event Subscribe
      void SendEventSubscribeRequest (Ptr<Packet> packet,
                                      EventList events,
                                      MihLinkDetectedIndicationCallback linkDetectedEventCallback1,
                                      MihLinkUpIndicationCallback linkUpEventCallback2,
                                      MihLinkDownIndicationCallback linkDownEventCallback3,
                                      MihLinkParametersReportIndicationCallback linkParamReportEventCallback4,
                                      MihLinkGoingDownIndicationCallback linkGoingDownEventCallback5,
                                      MihLinkHandoverImminentIndicationCallback linkHOImminentEventCallback6,
                                      MihLinkHandoverCompleteIndicationCallback linkHOCompleteEventCallback7,
                                      MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusEventCallback8,
                                      MihEventSubscribeConfirmCallback subscribeConfirmCallback);
      MihEventSubscribeConfirmCallback ReceiveEventSubscribeRequest (Ptr<Packet> packet, 
                                                                     uint16_t transactionId);
      void ReceiveEventSubscribeResponse (MihfId mihfId, 
                                          Status status, 
                                          LinkIdentifier linkIdentifier, 
                                          EventList events);
      // LingGetParamters
      void SendLinkGetParametersRequest (Ptr<Packet> packet,
                                         MihLinkGetParametersConfirmCallback getParamtersConfirmCallback);
      MihLinkGetParametersConfirmCallback ReceiveLinkGetParametersRequest (Ptr<Packet> packet, 
                                                                           uint16_t transactionId);
      void ReceiveLinkGetParametersResponse (MihfId mihfId, 
                                             Status status,
                                             DeviceStatesResponseList deviceStatesResponseList,
                                             LinkStatusResponseList linkStatusResponseList);
      // LinkConfigureThresholds
      void SendLinkConfigureThresholdsRequest (Ptr<Packet> packet,
                                               MihLinkConfigureThresholdsConfirmCallback configureThresholdsConfiirmCallback);
      MihLinkConfigureThresholdsConfirmCallback ReceiveLinkConfigureThresholdsRequest (Ptr<Packet> packet, 
                                                                                       uint16_t transactionId);
      void ReceiveLinkConfigureThresholdsResponse (MihfId mihfId, 
                                                   Status status,
                                                   LinkIdentifier linkIdentifier, 
                                                   LinkConfigurationStatusList linkConfigurationStatusList);
      // Remote events access methods;
      RemoteEventSourceTrap& GetRemoteEventSourceTrap (void);
      RemoteEventDestinationTrap& GetRemoteEventDestinationTrap (void);
    protected:
      friend class RemoteEventSourceTrap;
      // Event transport;
      void SendEvent (Ptr<Packet> packet);
/*       void Enqueue (Ptr<Transaction> transaction, TransactionQueue queue); */
/*       void Dequeue (); */
/*       uint16_t GetNextTransactionId (void); */
/*       void HandleRead (void); */

      void NotifyNewPendingRequest (void);
      void NotifyResponseReceived (void);
      void NotifyPendingResponseDone (void);
      void NotifyPendingCurrentRequestDone (void);

      void DisposePendingResponse (void);
      void DisposePendingCurrentRequest (void);
      
      // Inner members;
      MihfId m_sourceMihfid;
      Address m_sourceInetSocketAddress;
      MihfId m_destinationMihfid;
      Address m_destinationInetSocketAddress;
      Ptr<Socket> m_socket;
      bool m_initComplete;
      bool m_isRegistered;
      
      uint16_t m_nextTransactionId;
      uint16_t m_delay;
      uint16_t m_maxSize;
      TransactionQueue m_pendingRequestQueue;
      Ptr<Transaction> m_currentTransaction;
      Ptr<Transaction> m_pendingResponseTransaction;
      TransactionQueue m_pendingEventQueue;

      RemoteEventDestinationTrap m_remoteEventDestinationTrap;
      RemoteEventSourceTrap m_remoteEventSourceTrap;
    };
    typedef std::vector<Ptr<Session> > SessionList;
    typedef SessionList::iterator SessionListI;
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_SESSION_H */
