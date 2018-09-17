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
#include "mih-transaction.h"

NS_LOG_COMPONENT_DEFINE ("Transaction");

namespace ns3 {
  namespace mih {
    //     class Transaction
    Transaction::Transaction (Ptr<Packet> packet, 
                              MihfId fromMihfid, 
                              MihfId toMihfid, 
                              Address to, 
                              uint16_t tid) :
      m_packet (packet),
      m_fromMihfId (fromMihfid),
      m_toMihfId (toMihfid),
      m_to (to),
      m_tstamp (Simulator::Now ()),
      m_toBedeleted (false),
      m_transactionId (tid),
      m_state (Transaction::INIT),
      m_notifyDone (MakeNullCallback<void> ())
    {
      NS_LOG_FUNCTION (this);
    }
    Transaction::~Transaction (void)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (m_toBedeleted == true);
      m_packet = 0;
    }
    Time 
    Transaction::GetStartTime (void)
    {
      NS_LOG_FUNCTION (this);
      return m_tstamp;
    }
    uint16_t 
    Transaction::GetTransactionId (void)
    {
      NS_LOG_FUNCTION (this);
      return m_transactionId;
    }
    void 
    Transaction::SetToBeDeleted (void)
    {
      NS_LOG_FUNCTION (this);
      m_toBedeleted = true;
      m_notifyDone ();
    }
    bool 
    Transaction::IsToBeDeleted (void)
    {
      NS_LOG_FUNCTION (this);
      return m_toBedeleted;
    }
    Ptr<Packet> 
    Transaction::GetPacket (void)
    {
      NS_LOG_FUNCTION (this);
      return m_packet;
    }
    void
    Transaction::SetState (enum Transaction::State state)
    {
      NS_LOG_FUNCTION (this);
      m_state = state;
    }
    enum Transaction::State
    Transaction::GetState (void)
    {
      NS_LOG_FUNCTION (this);
      return m_state;
    }
    void 
    Transaction::SetNotifyDoneCallback (Callback<void> doneCb)
    {
      NS_LOG_FUNCTION (this);
      m_notifyDone = doneCb;
    }
    //    class RegisterRequestTransaction
    RegisterRequestTransaction::RegisterRequestTransaction (Ptr<Packet> packet, 
                                                            MihfId fromMihfid, 
                                                            MihfId toMihfid, 
                                                            Address to, 
                                                            uint16_t tid, 
                                                            MihRegisterConfirmCallback registerConfirmCallback) :
      Transaction (packet, fromMihfid, toMihfid, to, tid),
      m_registerConfirmCallback (registerConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
    }
    RegisterRequestTransaction::~RegisterRequestTransaction (void)
    {
      NS_LOG_FUNCTION (this);
    }
    void
    RegisterRequestTransaction::RegisterConfirm (MihfId mihfid, Status status, uint32_t validLifetime)
    {
      NS_LOG_FUNCTION (this);
      m_registerConfirmCallback (mihfid, status, validLifetime);
    }
    //    class RegisterResponseTransaction
    RegisterResponseTransaction::RegisterResponseTransaction (Ptr<Packet> packet, 
                                                              MihfId fromMihfid, 
                                                              MihfId toMihfid, 
                                                              Address to, 
                                                              uint16_t tid, 
                                                              Ptr<Socket> socket) :
      Transaction (packet, fromMihfid, toMihfid, to, tid),
      m_socket (socket)
    {
      NS_LOG_FUNCTION (this);
    }
    RegisterResponseTransaction::~RegisterResponseTransaction (void)
    {
      NS_LOG_FUNCTION (this);
      m_socket = 0;
    }
    void 
    RegisterResponseTransaction::SendRegisterResponse (MihfId mihfId,
                                                       Status status,
                                                       uint32_t validLifetime)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (mihfId == m_fromMihfId);
      Buffer buffer;
      Ptr<Packet> packet;
      // TLV-Serialize in buffer;
      m_fromMihfId.TlvSerialize (buffer);
      m_toMihfId.TlvSerialize (buffer);
      status.TlvSerialize (buffer);
      if (status.GetType () == Status::SUCCESS)
        {
          Tlv::SerializeU32 (buffer, validLifetime, TLV_VALID_TIME_INTERVAL);
        }
      // Fill the packet with payload from buffer
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Mih Header;
      MihHeader mihHeader;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::MANAGEMENT);
      mihHeader.SetOpCode (MihHeader::RESPONSE);
      mihHeader.SetActionId (MihHeader::MIH_REGISTER);
      mihHeader.SetTransactionId (GetTransactionId ());
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send via socket;
      // Add possibilities to select the source interface
      m_socket->SendTo (packet, 0, m_to);
      SetToBeDeleted ();      
    }
    //    class CapabilityDiscoverRequestTransaction
    CapabilityDiscoverRequestTransaction::CapabilityDiscoverRequestTransaction (Ptr<Packet> packet, 
                                                                                MihfId fromMihfid, 
                                                                                MihfId toMihfid, 
                                                                                Address to, 
                                                                                uint16_t tid, 
                                                                                MihCapabilityDiscoverConfirmCallback capabilityDiscoverConfirmCallback) :
      Transaction (packet, fromMihfid, toMihfid, to, tid),
      m_capabilityDiscoverConfirmCallback (capabilityDiscoverConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
    }
    CapabilityDiscoverRequestTransaction::~CapabilityDiscoverRequestTransaction (void)
    {
      NS_LOG_FUNCTION (this);
    }
    void
    CapabilityDiscoverRequestTransaction::CapabilityDiscoverConfirm (MihfId mihfId, 
                                                                     Status status, 
                                                                     NetworkTypeAddressList networkTypeAddessList, 
                                                                     EventList events,
                                                                     MihCommandList commands, 
                                                                     InformationServiceQueryTypeList miisQueries,
                                                                     TransportSupportList transportOptions, 
                                                                     MakeBeforeBreakSupportList mbbHoSupportList)
    {
      NS_LOG_FUNCTION (this);
      m_capabilityDiscoverConfirmCallback (mihfId, 
                                           status, 
                                           networkTypeAddessList, 
                                           events, 
                                           commands, 
                                           miisQueries, 
                                           transportOptions, 
                                           mbbHoSupportList);
    }
    //    class CapabilityDiscoverResponseTransaction;
    CapabilityDiscoverResponseTransaction::CapabilityDiscoverResponseTransaction (Ptr<Packet> packet, 
                                                                                  MihfId fromMihfid, 
                                                                                  MihfId toMihfid, 
                                                                                  Address to, 
                                                                                  uint16_t tid, 
                                                                                  Ptr<Socket> socket) :
      Transaction (packet, fromMihfid, toMihfid, to, tid),
      m_socket (socket)
    {
      NS_LOG_FUNCTION (this);
    }
    CapabilityDiscoverResponseTransaction::~CapabilityDiscoverResponseTransaction (void)
    {
      NS_LOG_FUNCTION (this);
      m_socket = 0;
    }
    void
    CapabilityDiscoverResponseTransaction::SendCapabilityDiscoverResponse (MihfId mihfId,
                                                                           Status status,
                                                                           NetworkTypeAddressList networkTypeAddresses,
                                                                           EventList events,
                                                                           MihCommandList commands,
                                                                           InformationServiceQueryTypeList miisQueries,
                                                                           TransportSupportList transportOptions,
                                                                           MakeBeforeBreakSupportList mbbSupportList)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (mihfId == m_fromMihfId);
      Buffer buffer;
      Ptr<Packet> packet;
      // TLV-Serialize in buffer;
      m_fromMihfId.TlvSerialize (buffer);
      m_toMihfId.TlvSerialize (buffer);
      status.TlvSerialize (buffer);
      TlvSerialize (buffer, networkTypeAddresses);
      events.TlvSerialize (buffer);
      commands.TlvSerialize (buffer);
      miisQueries.TlvSerialize (buffer);
      transportOptions.TlvSerialize (buffer);
      TlvSerialize (buffer, mbbSupportList);
      // Fill the packet with payload from buffer
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Mih Header;
      MihHeader mihHeader;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::MANAGEMENT);
      mihHeader.SetOpCode (MihHeader::RESPONSE);
      mihHeader.SetActionId (MihHeader::MIH_CAPABILITY_DISCOVER);
      mihHeader.SetTransactionId (GetTransactionId ());
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send via socket;
      // Add possibilities to select the source interface
      m_socket->SendTo (packet, 0, m_to);
      SetToBeDeleted ();
    }
    //class EventSubscribeRequestTransaction;
    EventSubscribeRequestTransaction::EventSubscribeRequestTransaction (Ptr<Packet> packet, 
                                                                        MihfId fromMihfid, 
                                                                        MihfId toMihfid, 
                                                                        Address to, 
                                                                        uint16_t tid,
                                                                        MihEventSubscribeConfirmCallback subscribeConfirmCallback) :
      Transaction (packet, fromMihfid, toMihfid, to, tid),
      m_subscribeConfirmCallback (subscribeConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
    }
    EventSubscribeRequestTransaction::~EventSubscribeRequestTransaction (void)
    {}
    void
    EventSubscribeRequestTransaction::EventSubscribeConfirm (MihfId mihfId, 
                                                             Status status, 
                                                             LinkIdentifier linkIdentifier, 
                                                             EventList events)
    {
      NS_LOG_FUNCTION (this);
      m_subscribeConfirmCallback (mihfId, status,
                                  linkIdentifier, events);
    }
    //    class EventSubscribeResponseTransaction;
    EventSubscribeResponseTransaction::EventSubscribeResponseTransaction (Ptr<Packet> packet, 
                                                                          MihfId fromMihfid, 
                                                                          MihfId toMihfid, 
                                                                          Address to, 
                                                                          uint16_t tid,
                                                                          Ptr<Socket> socket) :
      Transaction (packet, fromMihfid, toMihfid, to, tid),
      m_socket (socket)
    {
      NS_LOG_FUNCTION (this);
    }
    EventSubscribeResponseTransaction::~EventSubscribeResponseTransaction (void)
    {
      NS_LOG_FUNCTION (this);
      m_socket = 0;
    }
    void
    EventSubscribeResponseTransaction::SendEventSubcribeResponse (MihfId mihfId,
                                                                  Status status,
                                                                  LinkIdentifier linkIdentifier,
                                                                  EventList events)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (mihfId == m_fromMihfId);
      Buffer buffer;
      Ptr<Packet> packet;
      // TLV-Serialize in buffer;
      m_fromMihfId.TlvSerialize (buffer);
      m_toMihfId.TlvSerialize (buffer);
      status.TlvSerialize (buffer);
      linkIdentifier.TlvSerialize (buffer);
      events.TlvSerialize (buffer);
      // Fill the packet with payload from buffer
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Mih Header;
      MihHeader mihHeader;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::MANAGEMENT);
      mihHeader.SetOpCode (MihHeader::RESPONSE);
      mihHeader.SetActionId (MihHeader::MIH_EVENT_SUBSCRIBE);
      mihHeader.SetTransactionId (GetTransactionId ());
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send via socket;
      // Add possibilities to select the source interface
      m_socket->SendTo (packet, 0, m_to);
      SetToBeDeleted ();
    }
    //    class LinkGetParametersRequestTransaction;
    LinkGetParametersRequestTransaction::LinkGetParametersRequestTransaction (Ptr<Packet> packet, 
                                                                              MihfId fromMihfid, 
                                                                              MihfId toMihfid, 
                                                                              Address to, 
                                                                              uint16_t tid,
                                                                              MihLinkGetParametersConfirmCallback getParamtersConfirmCallback) :
      Transaction (packet, fromMihfid, toMihfid, to, tid),
      m_getParamtersConfirmCallback (getParamtersConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
    }
    LinkGetParametersRequestTransaction::~LinkGetParametersRequestTransaction (void)
    {}
    void 
    LinkGetParametersRequestTransaction::LinkGetParametersConfirm (MihfId mihfId, 
                                                                   Status status, 
                                                                   DeviceStatesResponseList deviceStatesResponseList, 
                                                                   LinkStatusResponseList linkStatusResponseList)
    {
      NS_LOG_FUNCTION (this);
      m_getParamtersConfirmCallback (mihfId, status,
                                     deviceStatesResponseList,
                                     linkStatusResponseList);
    }
    //    class LinkGetParametersResponseTransaction;
    LinkGetParametersResponseTransaction::LinkGetParametersResponseTransaction (Ptr<Packet> packet, 
                                                                                MihfId fromMihfid, 
                                                                                MihfId toMihfid, 
                                                                                Address to, 
                                                                                uint16_t tid,
                                                                                Ptr<Socket> socket) :
      Transaction (packet, fromMihfid, toMihfid, to, tid),
      m_socket (socket)
    {
      NS_LOG_FUNCTION (this);
    }
    LinkGetParametersResponseTransaction::~LinkGetParametersResponseTransaction (void)
    {
      NS_LOG_FUNCTION (this);
      m_socket = 0;
    }
    void 
    LinkGetParametersResponseTransaction::SendLinkGetParametersResponse (MihfId mihfId, 
                                                                         Status status, 
                                                                         DeviceStatesResponseList deviceStatesResponseList, 
                                                                         LinkStatusResponseList linkStatusResponseList)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (mihfId == m_fromMihfId);
      Buffer buffer;
      Ptr<Packet> packet;
      // TLV-Serialize in buffer;
      m_fromMihfId.TlvSerialize (buffer);
      m_toMihfId.TlvSerialize (buffer);
      status.TlvSerialize (buffer);
      TlvSerialize (buffer, deviceStatesResponseList);
      TlvSerialize (buffer, linkStatusResponseList);
      // Fill the packet with payload from buffer
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Mih Header;
      MihHeader mihHeader;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::COMMAND);
      mihHeader.SetOpCode (MihHeader::RESPONSE);
      mihHeader.SetActionId (MihHeader::MIH_LINK_GET_PARAMETERS);
      mihHeader.SetTransactionId (GetTransactionId ());
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send via socket;
      // Add possibilities to select the source interface
      m_socket->SendTo (packet, 0, m_to);
      SetToBeDeleted ();
    }
    //    class LinkConfigureThresholdsRequestTransaction
    LinkConfigureThresholdsRequestTransaction::LinkConfigureThresholdsRequestTransaction (Ptr<Packet> packet, 
                                                                                          MihfId fromMihfid, 
                                                                                          MihfId toMihfid, 
                                                                                          Address to, 
                                                                                          uint16_t tid,
                                                                                          MihLinkConfigureThresholdsConfirmCallback configureThresholdsConfirmCallback) :
      Transaction (packet, fromMihfid, toMihfid, to, tid),
      m_configureThresholdsConfirmCallback (configureThresholdsConfirmCallback)
    {
      NS_LOG_FUNCTION (this);
    }
    LinkConfigureThresholdsRequestTransaction::~LinkConfigureThresholdsRequestTransaction (void)
    {
      NS_LOG_FUNCTION (this);
    }
    void
    LinkConfigureThresholdsRequestTransaction::LinkConfigureThresholdsConfirm (MihfId mihfId, 
                                                                               Status status, 
                                                                               LinkIdentifier linkIdentifier, 
                                                                               LinkConfigurationStatusList linkConfigurationStatusList)
    {
      NS_LOG_FUNCTION (this);
      m_configureThresholdsConfirmCallback (mihfId,
                                            status,
                                            linkIdentifier,
                                            linkConfigurationStatusList);
    }
    //    class LinkConfigureThresholdsResponseTransaction
    LinkConfigureThresholdsResponseTransaction::LinkConfigureThresholdsResponseTransaction (Ptr<Packet> packet, 
                                                                                            MihfId fromMihfid, 
                                                                                            MihfId toMihfid, 
                                                                                            Address to, 
                                                                                            uint16_t tid,
                                                                                            Ptr<Socket> socket) :
      Transaction (packet, fromMihfid, toMihfid, to, tid),
      m_socket (socket)
    {
      NS_LOG_FUNCTION (this);
    }
    LinkConfigureThresholdsResponseTransaction::~LinkConfigureThresholdsResponseTransaction (void)
    {
      NS_LOG_FUNCTION (this);
    }
    void
    LinkConfigureThresholdsResponseTransaction::SendLinkConfigureThresholdsResponse (MihfId mihfId, 
                                                                                     Status status, 
                                                                                     LinkIdentifier linkIdentifier, 
                                                                                     LinkConfigurationStatusList linkConfigurationStatusList)
    {
      NS_LOG_FUNCTION (this);
      NS_ASSERT (mihfId == m_fromMihfId);
      Buffer buffer;
      Ptr<Packet> packet;
      // TLV-Serialize in buffer;
      m_fromMihfId.TlvSerialize (buffer);
      m_toMihfId.TlvSerialize (buffer);
      status.TlvSerialize (buffer);
      linkIdentifier.TlvSerialize (buffer);
      TlvSerialize (buffer, linkConfigurationStatusList);
      // Fill the packet with payload from buffer
      packet = Create<Packet> (buffer.PeekData (), buffer.GetSize ());
      // Mih Header;
      MihHeader mihHeader;
      mihHeader.SetVersion (MihHeader::VERSION_ONE);
      mihHeader.SetServiceId (MihHeader::COMMAND);
      mihHeader.SetOpCode (MihHeader::RESPONSE);
      mihHeader.SetActionId (MihHeader::MIH_LINK_CONFIGURE_THRESHOLDS);
      mihHeader.SetTransactionId (GetTransactionId ());
      mihHeader.SetPayloadLength (packet->GetSize ());
      packet->AddHeader (mihHeader);
      // Send via socket;
      // Add possibilities to select the source interface
      m_socket->SendTo (packet, 0, m_to);
      SetToBeDeleted ();
    }
  } // namespace mih
} // namespace ns3
