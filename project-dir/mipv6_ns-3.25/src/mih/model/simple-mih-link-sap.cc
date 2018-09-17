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
#include "ns3/boolean.h"
#include "ns3/mac48-address.h"
#include "simple-mih-link-sap.h"
#include "mih-device-information.h"
#include "ns3/double.h"

NS_LOG_COMPONENT_DEFINE ("SimpleMihLinkSap");

namespace ns3 {
  namespace mih {

    NS_OBJECT_ENSURE_REGISTERED (SimpleMihLinkSap);
    
    TypeId 
    SimpleMihLinkSap::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::mih::SimpleMihLinkSap")
	.SetParent<MihLinkSap> ()
	.AddConstructor<SimpleMihLinkSap> ()
	.AddAttribute ("MihfId", "Mih Function Identifier",
		       MihfIdValue (MihfId ("default-SimpleMihLinkSap@ns3")),
		       MakeMihfIdAccessor (&SimpleMihLinkSap::m_mihfId),
		       MakeMihfIdChecker ())
        .AddAttribute ("PowerUp", "PowerUp",
                       BooleanValue (true),
                       MakeBooleanAccessor (&SimpleMihLinkSap::m_powerUp),
                       MakeBooleanChecker ())
	;
      return tid;
    }
    SimpleMihLinkSap::SimpleMihLinkSap (void) :
      m_linkIdentifier ()
    {
      NS_LOG_FUNCTION (this);
      m_eventTriggerInterval = CreateObject<UniformRandomVariable> ();
      m_eventTriggerInterval->SetAttribute ("Min", DoubleValue(0));
      m_eventTriggerInterval->SetAttribute ("Max", DoubleValue(0.5));
      m_rngChoice = CreateObject<UniformRandomVariable> ();
      m_rngChoice->SetAttribute ("Min", DoubleValue(0));
      m_rngChoice->SetAttribute ("Max", DoubleValue(3));
    }
    SimpleMihLinkSap::~SimpleMihLinkSap (void)
    {
      NS_LOG_FUNCTION_NOARGS ();
    }
    void
    SimpleMihLinkSap::DoDispose (void)
    {
      NS_LOG_FUNCTION (this);
      if (m_nextEventId.IsRunning ())
	{
	  Simulator::Cancel (m_nextEventId);
	}
      MihLinkSap::DoDispose ();
    }
    LinkType
    SimpleMihLinkSap::GetLinkType (void)
    {
      NS_LOG_FUNCTION (this);
      return m_linkIdentifier.GetType ();
    }
    void
    SimpleMihLinkSap::SetLinkType (LinkType linkType)
    {
      NS_LOG_FUNCTION (this);
      m_linkIdentifier.SetType (linkType);
    }
    Address
    SimpleMihLinkSap::GetLinkAddress (void)
    {
      NS_LOG_FUNCTION (this);
      return m_linkIdentifier.GetDeviceLinkAddress ();
    }
    void 
    SimpleMihLinkSap::SetLinkAddress (Address addr)
    {
      NS_LOG_FUNCTION (this);
      m_linkIdentifier.SetDeviceLinkAddress (addr);
    }
    LinkIdentifier
    SimpleMihLinkSap::GetLinkIdentifier (void)
    {
      NS_LOG_FUNCTION (this);
      return m_linkIdentifier;
    }
    void 
    SimpleMihLinkSap::SetLinkIdentifier (LinkIdentifier linkIdentifier)
    {
      NS_LOG_FUNCTION (this);
      m_linkIdentifier = linkIdentifier;
    }
    Address 
    SimpleMihLinkSap::GetPoAAddress (void)
    {
      NS_LOG_FUNCTION (this);
      return m_linkIdentifier.GetPoALinkAddress ();
    }
    void
    SimpleMihLinkSap::SetPoAAddress (Address addr)
    {
      NS_LOG_FUNCTION (this);
      m_linkIdentifier.SetPoALinkAddress (addr);
    }
    LinkCapabilityDiscoverConfirm
    SimpleMihLinkSap::CapabilityDiscover (void) 
    {
      NS_LOG_FUNCTION (this);
      return LinkCapabilityDiscoverConfirm (Status::SUCCESS,
					    (EventList::LINK_DETECTED |
					     EventList::LINK_UP |
					     EventList::LINK_DOWN |
					     EventList::LINK_PARAMETERS_REPORT),
					    (MihCommandList::LINK_GET_PARAMETERS |
					     MihCommandList::LINK_CONFIGURE_THRESHOLDS));
    }
    LinkGetParametersConfirm 
    SimpleMihLinkSap::GetParameters (LinkParameterTypeList linkParametersRequest, 
				     LinkStatesRequest linkStatesRequest, 
				     LinkDescriptorsRequest descriptors)
    {
      NS_LOG_FUNCTION (this);
      return LinkGetParametersConfirm ();
    }
    LinkConfigureThresholdsConfirm 
    SimpleMihLinkSap::ConfigureThresholds (LinkConfigurationParameterList configureParameters)
    {
      NS_LOG_FUNCTION (this);
      //      NS_ASSERT (m_powerUp);
      return LinkConfigureThresholdsConfirm (Status::UNSPECIFIED_FAILURE);
    }
    EventId
    SimpleMihLinkSap::Action (LinkAction action, 
			      uint64_t executionDelay, 
			      Address poaLinkAddress,
			      LinkActionConfirmCallback actionConfirmCb)
    {
      if (!m_powerUp)
        {
          if (action.GetType () != LinkAction::LINK_POWER_UP)
            {
              return EventId ();
            }
        }
      return Simulator::Schedule (MilliSeconds (executionDelay), 
                                  &SimpleMihLinkSap::DoAction, 
                                  this, 
                                  action, 
                                  poaLinkAddress, 
                                  actionConfirmCb);
    }
    void
    SimpleMihLinkSap::DoAction (LinkAction action,
                                Address poaLinkAddress,
                                LinkActionConfirmCallback actionConfirmCb)
    {
      NS_LOG_FUNCTION (this);
      if (actionConfirmCb.IsNull ())
        {
          return;
        }
      if (action.GetType () == LinkAction::LINK_POWER_DOWN)
        {
          Stop ();
          actionConfirmCb (Status (Status::SUCCESS),
                           ScanResponseList (),
                           LinkActionResponse::INCAPABLE,
                           GetLinkIdentifier ());
          return;
          
        }
      actionConfirmCb (Status (Status::SUCCESS),
                       ScanResponseList (),
                       LinkActionResponse::INCAPABLE,
                       GetLinkIdentifier ());
    }
    Ptr<DeviceStatesResponse> 
    SimpleMihLinkSap::GetDeviceStates (void)
    {
      NS_LOG_FUNCTION (this);
      return Create<DeviceInformation> ("OEM = ns-3Team");
    }
    void
    SimpleMihLinkSap::ScheduleNextTrigger (void)
    {
      NS_LOG_FUNCTION (this);
      if (!m_powerUp)
        {
          return;
        }
      uint32_t actionsN = 3; // Make this number consistent if you
			     // extend the number of possible actions
      ActionTrigger actions[actionsN];
      actions[0] = &SimpleMihLinkSap::TriggerLinkDetected;
      actions[1] = &SimpleMihLinkSap::TriggerLinkUp;
      actions[2] = &SimpleMihLinkSap::TriggerLinkDown;

      Time nextInterval = Seconds (m_eventTriggerInterval->GetValue ());
      uint8_t choice = uint8_t (m_rngChoice->GetValue ());
      std::string choiceStr = "INVALID";
      switch (choice)
	{
	case 0:
	  {
	    choiceStr = "LINK DETECTED";
	    break;
	  }
	case 1:
	  {
	    choiceStr = "LINK UP";
	    break;
	  }
	case 2:
	  {
	    choiceStr = "LINK DOWN";
	    break;
	  }
	default:
	  break;
	}
      NS_LOG_LOGIC ("A " << choiceStr << " trigger will occur at " << (Simulator::Now ().GetSeconds () + nextInterval.GetSeconds ()) << "s");
      m_nextEventId = Simulator::Schedule (nextInterval, actions[choice], this);
      return;
    }
    void
    SimpleMihLinkSap::TriggerLinkDetected (void) 
    {
      NS_LOG_FUNCTION (this);
      LinkDetected (m_mihfId,
		    LinkDetectedInformationList ());
      ScheduleNextTrigger ();
    }
    void
    SimpleMihLinkSap::TriggerLinkUp (void)
    {
      NS_LOG_FUNCTION (this);
      LinkUp (m_mihfId,
	      GetLinkIdentifier (),
	      Mac48Address ("33:33:00:00:00:10"),
	      Mac48Address ("33:33:00:00:00:20"),
	      true,
	      MobilityManagementSupport (MobilityManagementSupport::MOBILE_IPV4_RFC3344));
      ScheduleNextTrigger ();
    }
    void 
    SimpleMihLinkSap::TriggerLinkDown (void)
    {
      NS_LOG_FUNCTION (this);
      LinkDown (m_mihfId,
		GetLinkIdentifier (),
		Mac48Address ("33:33:00:00:00:10"),
		LinkDownReason (LinkDownReason::EXPLICIT_DISCONNECT));
      ScheduleNextTrigger ();
    }
    void 
    SimpleMihLinkSap::Run (void)
    {
      NS_LOG_FUNCTION (this);
      m_powerUp = true;
      ScheduleNextTrigger ();
    }
    void
    SimpleMihLinkSap::Stop (void)
    {
      NS_LOG_FUNCTION (this);
      m_powerUp = false;
      if (m_nextEventId.IsRunning ())
	{
	  Simulator::Cancel (m_nextEventId);
	}
    }
  } // namespace mih
} // namespace ns3
