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
#include "mih-link-sap.h"

NS_LOG_COMPONENT_DEFINE ("MihLinkSap");

namespace ns3 {
  namespace mih {
    TypeId
    MihLinkSap::GetTypeId (void) {
      static TypeId tid = TypeId ("ns3::mih::MihLinkSap")
	.SetParent<Object> ();
      return tid;
    }
    MihLinkSap::~MihLinkSap (void)
    {}
    // Event Service
    void
    MihLinkSap::LinkDetected (MihfId sourceMihfId, 
                              LinkDetectedInformationList linkDetectedInfoList) 
    {
      NS_LOG_FUNCTION (this);
      m_linkDetectedTraceCallback (sourceMihfId,
                                   linkDetectedInfoList);
    }
    void
    MihLinkSap::LinkUp (MihfId sourceMihfId,
                        LinkIdentifier linkIdentifier,
                        Address oldAR, 
                        Address newAR, 
                        bool ipRenewal, 
                        MobilityManagementSupport mobilitySupport) 
    {
      NS_LOG_FUNCTION (this);
      m_linkUpTracedCallback (sourceMihfId,
                              linkIdentifier,
                              oldAR,
                              newAR,
                              ipRenewal,
                              mobilitySupport);
    }
    void 
    MihLinkSap::LinkDown (MihfId sourceMihfId, 
                          LinkIdentifier linkIdentifier, 
                          Address oldAR,
                          LinkDownReason reason) 
    {
      NS_LOG_FUNCTION (this);
      m_linkDownTracedCallback (sourceMihfId,
                                linkIdentifier,
                                oldAR,
                                reason);
    }
    void 
    MihLinkSap::LinkParametersReport (MihfId sourceMihfId, 
                                      LinkIdentifier linkIdentifier,
                                      LinkParameterReportList parameters) 
    {
      NS_LOG_FUNCTION (this);
      m_linkParametersReportTracedCallback (sourceMihfId,
                                            linkIdentifier,
                                            parameters);
    }
    void 
    MihLinkSap::LinkGoingDown (MihfId sourceMihfId, 
                               LinkIdentifier linkIdentifier,
                               uint64_t timeInterval,
                               LinkGoingDownReason reason) 
    {
      NS_LOG_FUNCTION (this);
      m_linkGoingDownTracedCallback (sourceMihfId,
                                     linkIdentifier,
                                     timeInterval,
                                     reason);
    }
    void
    MihLinkSap::LinkHandoverImminent (MihfId sourceMihfId, 
                                      LinkIdentifier oldLinkIdentifier,
                                      LinkIdentifier newLinkIdentifier,
                                      Address oldAR, 
                                      Address newAR) 
    {
      NS_LOG_FUNCTION (this);
      m_linkHOImminentTracedCallback (sourceMihfId,
                                      oldLinkIdentifier,
                                      newLinkIdentifier,
                                      oldAR,
                                      newAR);
    }
    void 
    MihLinkSap::LinkHandoverComplete (MihfId sourceMihfId, 
                                      LinkIdentifier oldLinkIdentifier, 
                                      LinkIdentifier newLinkIdentifier,
                                      Address oldAR, 
                                      Address newAR, 
                                      Status handoverStatus)
    {
      NS_LOG_FUNCTION (this);
      m_linkHOCompleteTracedCallback (sourceMihfId,
                                      oldLinkIdentifier,
                                      newLinkIdentifier,
                                      oldAR,
                                      newAR,
                                      handoverStatus);
    }
    void 
    MihLinkSap::LinkPduTransmitStatus (MihfId sourceMihfId, 
                                       LinkIdentifier linkIdentifier, 
                                       uint16_t packetIdentifier,
                                       bool transmissionStatus) 
    {
      NS_LOG_FUNCTION (this);
      m_linkPduTxStatusTracedCallback (sourceMihfId,
                                       linkIdentifier,
                                       packetIdentifier,
                                       transmissionStatus);
    }

    // Command Service
    LinkEventSubscribeConfirm
    MihLinkSap::EventSubscribe (EventList::Type linkDetectedEventType1,
                                MihLinkDetectedIndicationCallback linkDetectedEventCallback1,
                                EventList::Type linkUpEventType2,
                                MihLinkUpIndicationCallback linkUpEventCallback2,
                                EventList::Type linkDownEventType3,
                                MihLinkDownIndicationCallback linkDownEventCallback3,
                                EventList::Type linkParamReportEventType4,
                                MihLinkParametersReportIndicationCallback linkParamReportEventCallback4,
                                EventList::Type linkGoingDownEventType5,
                                MihLinkGoingDownIndicationCallback linkGoingDownEventCallback5,
                                EventList::Type linkHOImminentEventType6,
                                MihLinkHandoverImminentIndicationCallback linkHOImminentEventCallback6,
                                EventList::Type linkHOCompleteEventType7,
                                MihLinkHandoverCompleteIndicationCallback linkHOCompleteEventCallback7,
                                EventList::Type linkPduTxStatusEventType8,
                                MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusEventCallback8)
    {
      NS_LOG_FUNCTION (this);
      EventList events;
      Status status (Status::SUCCESS);
      
      if (linkDetectedEventType1 == EventList::LINK_DETECTED)
        {
          NS_ASSERT (!linkDetectedEventCallback1.IsNull ());
          m_linkDetectedTraceCallback.ConnectWithoutContext (linkDetectedEventCallback1);
          events.SetEventList (events.GetEventList () | linkDetectedEventType1);
        }
      if (linkUpEventType2 == EventList::LINK_UP)
        {
          NS_ASSERT (!linkUpEventCallback2.IsNull ());
          m_linkUpTracedCallback.ConnectWithoutContext (linkUpEventCallback2);
          events.SetEventList (events.GetEventList () | linkUpEventType2);
        }
      if (linkDownEventType3 == EventList::LINK_DOWN)
        {
          NS_ASSERT (!linkDownEventCallback3.IsNull ());
          m_linkDownTracedCallback.ConnectWithoutContext (linkDownEventCallback3);
          events.SetEventList (events.GetEventList () | linkDownEventType3);
        }
      if (linkParamReportEventType4 == EventList::LINK_PARAMETERS_REPORT)
        {
          NS_ASSERT (!linkParamReportEventCallback4.IsNull ());
          m_linkParametersReportTracedCallback.ConnectWithoutContext (linkParamReportEventCallback4);
          events.SetEventList (events.GetEventList () | linkParamReportEventType4);
        }
      if (linkGoingDownEventType5 == EventList::LINK_GOING_DOWN)
        {
          NS_ASSERT (!linkGoingDownEventCallback5.IsNull ());
          m_linkGoingDownTracedCallback.ConnectWithoutContext (linkGoingDownEventCallback5);
          events.SetEventList (events.GetEventList () | linkGoingDownEventType5);
        }
      if (linkHOImminentEventType6 == EventList::LINK_HANDOVER_IMMINENT)
        {
          NS_ASSERT (!linkHOImminentEventCallback6.IsNull ());
          m_linkHOImminentTracedCallback.ConnectWithoutContext (linkHOImminentEventCallback6);
          events.SetEventList (events.GetEventList () | linkHOImminentEventType6);
        }
      if (linkHOCompleteEventType7 == EventList::LINK_HANDOVER_COMPLETE)
        {
          NS_ASSERT (!linkHOCompleteEventCallback7.IsNull ());
          m_linkHOCompleteTracedCallback.ConnectWithoutContext (linkHOCompleteEventCallback7);
          events.SetEventList (events.GetEventList () | linkHOCompleteEventType7);
        }
      if (linkPduTxStatusEventType8 == EventList::LINK_PDU_TRANSMIT_STATUS)
        {
          NS_ASSERT (!linkPduTxStatusEventCallback8.IsNull ());
          m_linkPduTxStatusTracedCallback.ConnectWithoutContext (linkPduTxStatusEventCallback8);
          events.SetEventList (events.GetEventList () | linkPduTxStatusEventType8);
        }
      
      return LinkEventSubscribeConfirm (status.GetType (), 
                                        events.GetEventList ());
    }
    LinkEventUnsubscribeConfirm 
    MihLinkSap::EventUnsubscribe (EventList::Type linkDetectedEventType1,
                                  MihLinkDetectedIndicationCallback linkDetectedEventCallback1,
                                  EventList::Type linkUpEventType2,
                                                            MihLinkUpIndicationCallback linkUpEventCallback2,
                                  EventList::Type linkDownEventType3,
                                  MihLinkDownIndicationCallback linkDownEventCallback3,
                                  EventList::Type linkParamReportEventType4,
                                  MihLinkParametersReportIndicationCallback linkParamReportEventCallback4,
                                  EventList::Type linkGoingDownEventType5,
                                  MihLinkGoingDownIndicationCallback linkGoingDownEventCallback5,
                                  EventList::Type linkHOImminentEventType6,
                                                            MihLinkHandoverImminentIndicationCallback linkHOImminentEventCallback6,
                                  EventList::Type linkHOCompleteEventType7,
                                  MihLinkHandoverCompleteIndicationCallback linkHOCompleteEventCallback7,
                                  EventList::Type linkPduTxStatusEventType8,
                                  MihLinkPduTransmitStatusIndicationCallback linkPduTxStatusEventCallback8)
    {
      NS_LOG_FUNCTION (this);
      EventList events;
      Status status;
      
      if (linkDetectedEventType1 == EventList::LINK_DETECTED)
        {
          NS_ASSERT (!linkDetectedEventCallback1.IsNull ());
          m_linkDetectedTraceCallback.DisconnectWithoutContext (linkDetectedEventCallback1);
          events.SetEventList (events.GetEventList () | linkDetectedEventType1);
        }
      if (linkUpEventType2 == EventList::LINK_UP)
        {
          NS_ASSERT (!linkUpEventCallback2.IsNull ());
          m_linkUpTracedCallback.DisconnectWithoutContext (linkUpEventCallback2);
          events.SetEventList (events.GetEventList () | linkUpEventType2);
        }
      if (linkDownEventType3 == EventList::LINK_DOWN)
        {
          NS_ASSERT (!linkDownEventCallback3.IsNull ());
          m_linkDownTracedCallback.DisconnectWithoutContext (linkDownEventCallback3);
          events.SetEventList (events.GetEventList () | linkDownEventType3);
        }
      if (linkParamReportEventType4 == EventList::LINK_PARAMETERS_REPORT)
        {
          NS_ASSERT (!linkParamReportEventCallback4.IsNull ());
          m_linkParametersReportTracedCallback.DisconnectWithoutContext (linkParamReportEventCallback4);
          events.SetEventList (events.GetEventList () | linkParamReportEventType4);
        }
      if (linkGoingDownEventType5 == EventList::LINK_GOING_DOWN)
        {
          NS_ASSERT (!linkGoingDownEventCallback5.IsNull ());
          m_linkGoingDownTracedCallback.DisconnectWithoutContext (linkGoingDownEventCallback5);
          events.SetEventList (events.GetEventList () | linkGoingDownEventType5);
        }
      if (linkHOImminentEventType6 == EventList::LINK_HANDOVER_IMMINENT)
        {
          NS_ASSERT (!linkHOImminentEventCallback6.IsNull ());
          m_linkHOImminentTracedCallback.DisconnectWithoutContext (linkHOImminentEventCallback6);
          events.SetEventList (events.GetEventList () | linkHOImminentEventType6);
        }
      if (linkHOCompleteEventType7 == EventList::LINK_HANDOVER_COMPLETE)
        {
          NS_ASSERT (!linkHOCompleteEventCallback7.IsNull ());
          m_linkHOCompleteTracedCallback.DisconnectWithoutContext (linkHOCompleteEventCallback7);
          events.SetEventList (events.GetEventList () | linkHOCompleteEventType7);
        }
      if (linkPduTxStatusEventType8 == EventList::LINK_PDU_TRANSMIT_STATUS)
        {
          NS_ASSERT (!linkPduTxStatusEventCallback8.IsNull ());
          m_linkPduTxStatusTracedCallback.DisconnectWithoutContext (linkPduTxStatusEventCallback8);
          events.SetEventList (events.GetEventList () | linkPduTxStatusEventType8);
        }
      
      return LinkEventUnsubscribeConfirm (status.GetType (), 
                                        events.GetEventList ());

    }
  } // namespace mih
} // namespace ns3
