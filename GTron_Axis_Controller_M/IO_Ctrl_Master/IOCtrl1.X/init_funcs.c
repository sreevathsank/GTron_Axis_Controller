#include "init_funcs.h"

void init_Watchdog_Timer( void )
{
    // Init WatchDog Timer.
    WDT_Disable();
    WDT_TimeoutPeriodSet(WDT_CYC16384);
    WDT_Enable();
    
    if (WDT_IsEnabled()) { SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nAfter Init - WDT Enabled\n"); } 
    else { SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nAfter Init - WDT Disabled\n"); }
    
    WDT_Clear();                
    // Init WatchDog Timer done.
    
    return;
}

void determine_Reset_Cause( void )
{
    // Determining the Reset Cause.
    uint32_t rcause = RSTC_ResetCauseGet();
    switch(rcause) 
    {
        case RSTC_RESET_CAUSE_POR_RESET:
           SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nRCAUSE => POR\n");
        break;
        case RSTC_RESET_CAUSE_BODCORE_RESET:
           SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nRCAUSE => BODCORE\n");
        break;
        case RSTC_RESET_CAUSE_BODVDD_RESET:
           SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nRCAUSE => BODVDD\n");
        break;
        case RSTC_RESET_CAUSE_EXT_RESET:
           SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nRCAUSE => EXT_RST\n");
        break;
        case RSTC_RESET_CAUSE_WDT_RESET:
           SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nRCAUSE => WDT\n");
        break;
        case RSTC_RESET_CAUSE_SYST_RESET:
           SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nRCAUSE => SYST\n");
        break;
        default:
           SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "\nRCAUSE => UNKNOWN\n");
        break;
    }
    // Reset cause determined.
    
    return;
}

void call_All_Init_Funcs_Vars( void )
{
    //CAN_SILENT_Clear();
    CAN1_MessageRAMConfigSet(Can1MessageRAM);
    CAN1_TxFifoCallbackRegister(CAN1_TxFifoCallback, (uintptr_t)APP_STATE_CAN_TRANSMIT );
    CAN1_RxFifoCallbackRegister(CAN_RX_FIFO_0, CAN1_RxFifo0Callback, APP_STATE_CAN_RECEIVE);
    CAN1_RxFifoCallbackRegister(CAN_RX_FIFO_1, CAN1_RxFifo1Callback, APP_STATE_CAN_RECEIVE);
    
    xcan_rd_wr_queue = xQueueCreate(CAN_RD_WR_QUEUE_ITEMS, sizeof(Can_Queue_t));
    
    xcmd_parser_queue = xQueueCreate(CAN_RD_WR_QUEUE_ITEMS, sizeof(CAN_Cmd_Parser_t));
    
    can1_rx_fifo0_cb_info.buf_cnt = 0;
    can1_rx_fifo0_cb_info.no_of_msgs = 0;
    can1_rx_fifo0_cb_info.context = (uintptr_t)NULL;
    
    can1_rx_fifo1_cb_info.buf_cnt = 0;
    can1_rx_fifo1_cb_info.no_of_msgs = 0;
    can1_rx_fifo1_cb_info.context = (uintptr_t)NULL;

    EIC_Init_Callbacks();
    
    xbtn_state_event_grp = xEventGroupCreate();
    
    // Clear the bit flags in the Button State Event Group.
    if(xbtn_state_event_grp != NULL)
    {
        EventBits_t xbits_to_clear = ( 0);
        xEventGroupClearBits( xbtn_state_event_grp, xbits_to_clear );
    }
    else
    {
        // Print Debug Message that the event group is not created.
    }
    
    xdebug_log_queue = xQueueCreate(DBG_LOG_QUEUE_LEN, sizeof(char *));
    if(xdebug_log_queue != NULL)
    {
        //error
    }
    
    LED_Driver_SPI_Init();
    
    //init_Watchdog_Timer();
    determine_Reset_Cause();
    
    return;
}