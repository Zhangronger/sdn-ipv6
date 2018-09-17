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

#ifndef   	MIH_TRANSACTION_H
#define   	MIH_TRANSACTION_H

#include <deque>
#include <stdint.h>
#include "ns3/ref-count-base.h"
#include "ns3/packet.h"
#include "ns3/nstime.h"
#include "ns3/socket.h"
#include "ns3/event-id.h"
#include "mih-callbacks.h"

namespace ns3 {
  namespace mih {
    class Transaction : public RefCountBase {
    public:
      enum State {
	INIT,
	FAILURE,
	PROCESS_MSG,
	WAIT_ACK,
	WAIT_RESPONSE_MSG,
	SUCCESS,
      };
      enum Event {
      };
      Transaction (Ptr<Packet> packet, 
                   MihfId fromMihfid, 
                   MihfId toMihfid, 
                   Address to, 
                   uint16_t tid);
      virtual ~Transaction (void);
      virtual Time GetStartTime (void);
      virtual uint16_t GetTransactionId (void);
      virtual void SetToBeDeleted (void);
      virtual bool IsToBeDeleted (void);
      virtual Ptr<Packet> GetPacket (void);
      virtual void SetState (enum State state);
      virtual enum State GetState (void);
      void SetNotifyDoneCallback (Callback<void> doneCb);
    protected:
      Ptr<Packet> m_packet;
      MihfId m_fromMihfId;
      MihfId m_toMihfId;
      Address m_to;
      Time m_tstamp;
      bool m_toBedeleted;
      uint16_t m_transactionId;
      enum State m_state;
      Callback<void> m_notifyDone;
    };
    class RegisterRequestTransaction : public Transaction {
    public:
      RegisterRequestTransaction (Ptr<Packet> packet, 
                                  MihfId fromMihfid, 
                                  MihfId toMihfid, 
                                  Address to, 
                                  uint16_t tid, 
                                  MihRegisterConfirmCallback registerConfirmCallback);
      virtual ~RegisterRequestTransaction (void);
      void RegisterConfirm (MihfId mihfid, 
                            Status status,
                            uint32_t validLifetime);
    protected:
      MihRegisterConfirmCallback m_registerConfirmCallback;
    };
    class RegisterResponseTransaction : public Transaction {
    public:
      RegisterResponseTransaction (Ptr<Packet> packet,
                                   MihfId fromMihfid, 
                                   MihfId toMihfid, 
                                   Address to, 
                                   uint16_t tid, 
                                   Ptr<Socket> socket);
      virtual ~RegisterResponseTransaction (void);
      void SendRegisterResponse (MihfId mihfid, 
                                 Status status, 
                                 uint32_t validLifetime);
    protected:
      Ptr<Socket> m_socket;
    };
    class CapabilityDiscoverRequestTransaction : public Transaction {
    public:
      CapabilityDiscoverRequestTransaction (Ptr<Packet> packet, 
                                            MihfId fromMihfid, 
                                            MihfId toMihfid, 
                                            Address to, 
                                            uint16_t tid, 
                                            MihCapabilityDiscoverConfirmCallback capabilityDiscoverConfirmCallback);
      virtual ~CapabilityDiscoverRequestTransaction (void);
      void CapabilityDiscoverConfirm (MihfId mihfId, 
                                      Status status, 
                                      NetworkTypeAddressList networkTypeAddessList, 
                                      EventList events,
                                      MihCommandList commands, 
                                      InformationServiceQueryTypeList miisQueries,
                                      TransportSupportList transportOptions, 
                                      MakeBeforeBreakSupportList mbbHoSupportList);
    protected:
      MihCapabilityDiscoverConfirmCallback m_capabilityDiscoverConfirmCallback;
    };
    class CapabilityDiscoverResponseTransaction : public Transaction {
    public:
      CapabilityDiscoverResponseTransaction (Ptr<Packet> packet, 
                                             MihfId fromMihfid, 
                                             MihfId toMihfid, 
                                             Address to, 
                                             uint16_t tid, 
                                             Ptr<Socket> socket);
      virtual ~CapabilityDiscoverResponseTransaction (void);
      void SendCapabilityDiscoverResponse (MihfId mihfId, 
                                           Status status,
                                           NetworkTypeAddressList networkTypeAddresses,
                                           EventList events,
                                           MihCommandList commands,
                                           InformationServiceQueryTypeList miisQueries,
                                           TransportSupportList transportOptions,
                                           MakeBeforeBreakSupportList mbbSupportList);
    protected:
      Ptr<Socket> m_socket;
    };
    class EventSubscribeRequestTransaction : public Transaction {
    public:
      EventSubscribeRequestTransaction (Ptr<Packet> packet, 
                                        MihfId fromMihfid, 
                                        MihfId toMihfid, 
                                        Address to, 
                                        uint16_t tid,
                                        MihEventSubscribeConfirmCallback subscribeConfirmCallback);
      virtual ~EventSubscribeRequestTransaction (void);
      void EventSubscribeConfirm (MihfId mihfId, 
                                  Status status, 
                                  LinkIdentifier linkIdentifier, 
                                  EventList events);
    protected:
      MihEventSubscribeConfirmCallback m_subscribeConfirmCallback;
    };
    class EventSubscribeResponseTransaction : public Transaction {
    public:
      EventSubscribeResponseTransaction (Ptr<Packet> packet, 
                                         MihfId fromMihfid, 
                                         MihfId toMihfid, 
                                         Address to, 
                                         uint16_t tid,
                                         Ptr<Socket> socket);
      virtual ~EventSubscribeResponseTransaction (void);
      void SendEventSubcribeResponse (MihfId mihfId,
                                      Status status,
                                      LinkIdentifier linkIdentifier,
                                      EventList events);
      
    protected:
      Ptr<Socket> m_socket;
    };
    class LinkGetParametersRequestTransaction : public Transaction {
    public:
      LinkGetParametersRequestTransaction (Ptr<Packet> packet, 
                                           MihfId fromMihfid, 
                                           MihfId toMihfid, 
                                           Address to, 
                                           uint16_t tid,
                                           MihLinkGetParametersConfirmCallback getParamtersConfirmCallback);
      virtual ~LinkGetParametersRequestTransaction (void);
      void LinkGetParametersConfirm (MihfId mihfId, 
                                     Status status, 
                                     DeviceStatesResponseList deviceStatesResponseList, 
                                     LinkStatusResponseList linkStatusResponseList);
    protected:
      MihLinkGetParametersConfirmCallback m_getParamtersConfirmCallback;
    };
    class LinkGetParametersResponseTransaction : public Transaction {
    public:
      LinkGetParametersResponseTransaction (Ptr<Packet> packet, 
                                            MihfId fromMihfid, 
                                            MihfId toMihfid, 
                                            Address to, 
                                            uint16_t tid,
                                            Ptr<Socket> socket);
      virtual ~LinkGetParametersResponseTransaction (void);
      void SendLinkGetParametersResponse (MihfId mihfId, 
                                          Status status, 
                                          DeviceStatesResponseList deviceStatesResponseList, 
                                          LinkStatusResponseList linkStatusResponseList);
    protected:
      Ptr<Socket> m_socket;
    };
    class LinkConfigureThresholdsRequestTransaction : public Transaction {
    public:
      LinkConfigureThresholdsRequestTransaction (Ptr<Packet> packet, 
                                                 MihfId fromMihfid, 
                                                 MihfId toMihfid, 
                                                 Address to, 
                                                 uint16_t tid,
                                                 MihLinkConfigureThresholdsConfirmCallback configureThresholdsConfirmCallback);
      virtual ~LinkConfigureThresholdsRequestTransaction (void);
      void LinkConfigureThresholdsConfirm (MihfId mihfId, 
                                           Status status, 
                                           LinkIdentifier linkIdentifier, 
                                           LinkConfigurationStatusList linkConfigurationStatusList);
    protected:
      MihLinkConfigureThresholdsConfirmCallback m_configureThresholdsConfirmCallback;
    };
    class LinkConfigureThresholdsResponseTransaction : public Transaction {
    public:
      LinkConfigureThresholdsResponseTransaction (Ptr<Packet> packet, 
                                                  MihfId fromMihfid, 
                                                  MihfId toMihfid, 
                                                  Address to, 
                                                  uint16_t tid,
                                                  Ptr<Socket> socket);
      virtual ~LinkConfigureThresholdsResponseTransaction (void);
      void SendLinkConfigureThresholdsResponse (MihfId mihfId, 
                                                Status status, 
                                                LinkIdentifier linkIdentifier, 
                                                LinkConfigurationStatusList linkConfigurationStatusList);
    protected:
      Ptr<Socket> m_socket;
    };
    typedef std::deque<Ptr<Transaction> > TransactionQueue;
    typedef TransactionQueue::reverse_iterator TransactionQueueRI;
    typedef TransactionQueue::iterator TransactionQueueI;
  } // namespace mih
} // namespace ns3

#endif 	    /* !MIH_TRANSACTION_H */
