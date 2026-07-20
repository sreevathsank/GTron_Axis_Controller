/* 
 * File:   custom_macros.h
 * Author: sreevathsank
 *
 * Created on 30 June, 2025, 3:24 PM
 */

#ifndef CUSTOM_MACROS_H
#define	CUSTOM_MACROS_H

#include "all_headers.h"

#define ever                                    (;;)

// Debug Logger Related Macros.
#define DBG_MSG_LEN                             256 // Length of the Debug Message Log.
#define DBG_LOG_PREFIX                          26  // Length of Task being printed as a prefix for debug log.
#define DBG_LOG_DATA_LEN                        ( DBG_MSG_LEN - DBG_LOG_PREFIX )
#define DBG_LOG_QUEUE_LEN                       6   // No of items contained by the queue used by the Debug Logger Task.

// Can Read Write Queue.
#define CAN_RD_WR_QUEUE_ITEMS                   6   // The no. of items the CAN Queue holds.
#define CAN_READ_FLAG                           1   // Flag value to denote CAN Read operation to be set in the CAN Queue.
#define CAN_WRITE_FLAG                          2   // Flag value to denote CAN Write operation to be set in the CAN Queue.
#define CAN_BUFFER_FIFO_0                       0   // Denotes the FIFO0 CAN Buffer.
#define CAN_BUFFER_FIFO_1                       1   // Denotes the FIFO1 CAN Buffer.

// Macros to set the event bit flags.
#define SET_EVENT_GRP_SELECT_STATE_FLAG         ( 1UL << 0UL )      // Set the 0th bit flag of the event group. Sets the Run bit flag.
#define SET_EVENT_GRP_RUN_STATE_FLAG            ( 1UL << 1UL )      // Set the 0th bit flag of the event group. Sets the Run bit flag.
#define SET_EVENT_GRP_PASS_STATE_FLAG           ( 1UL << 2UL )      // Set the 1st bit flag of the event group. Sets the Pause bit flag.
#define SET_EVENT_GRP_PAUSE_STATE_FLAG          ( 1UL << 3UL )      // Set the 0th bit flag of the event group. Sets the Run bit flag.
#define SET_EVENT_GRP_FAIL_STATE_FLAG           ( 1UL << 4UL )      // Set the 0th bit flag of the event group. Sets the Run bit flag.
#define SET_EVENT_GRP_BUZZOFFDR_STATE_FLAG      ( 1UL << 5UL )      // Set the 0th bit flag of the event group. Sets the Run bit flag.
#define SET_EVENT_GRP_BUZZOFFER_STATE_FLAG      ( 1UL << 6UL )      // Set the 0th bit flag of the event group. Sets the Run bit flag.
#define SET_EVENT_GRP_DISABLE_ALL_STATE_FLAG    ( 1UL << 7UL )      // Set the 0th bit flag of the event group. Sets the Run bit flag.
#define SET_EVENT_GRP_DISABLE_HW_BTN_STATE_FLAG ( 1UL << 8UL )      // Set the 0th bit flag of the event group. Sets the Run bit flag.
#define SET_EVENT_GRP_F_B_DOOR_LIM_FLAG         ( 1UL << 9UL )     // Set the 5th bit flag of the event group. Sets the Front and Back Door Limit Bit Flag.
#define SET_EVENT_GRP_EPANEL_DOOR_LIM_FLAG      ( 1UL << 10UL )     // Set the 6th bit flag of the event group. Sets the E-Panel Door Limit bit flag.
#define SET_EVENT_GRP_RUN_BUTTON_FLAG           ( 1UL << 11UL )     
#define SET_EVENT_GRP_PAUSE_BUTTON_FLAG         ( 1UL << 12UL )
#define SET_EVENT_GRP_STOP_BUTTON_FLAG          ( 1UL << 13UL )
#define SET_EVENT_GRP_BZROFF_BUTTON_FLAG        ( 1UL << 14UL )
#define SET_EVENT_GRP_RUN_BTN_EN_FLAG           ( 1UL << 15UL )
#define SET_EVENT_GRP_RUN_BTN_DIS_FLAG          ( 1UL << 16UL )
#define SET_EVENT_GRP_PAUSE_BTN_EN_FLAG         ( 1UL << 17UL )
#define SET_EVENT_GRP_PAUSE_BTN_DIS_FLAG        ( 1UL << 18UL )
#define SET_EVENT_GRP_STOP_BTN_EN_FLAG          ( 1UL << 19UL )
#define SET_EVENT_GRP_STOP_BTN_DIS_FLAG         ( 1UL << 20UL )
#define SET_EVENT_GRP_BZROFF_BTN_EN_FLAG        ( 1UL << 21UL )
#define SET_EVENT_GRP_BZROFF_BTN_DIS_FLAG       ( 1UL << 22UL )

                                            
#define SET_ALL_STATE_FLAGS                     ( SET_EVENT_GRP_SELECT_STATE_FLAG | \
                                                  SET_EVENT_GRP_RUN_STATE_FLAG | \
                                                  SET_EVENT_GRP_PAUSE_STATE_FLAG | \
                                                  SET_EVENT_GRP_PASS_STATE_FLAG | \
                                                  SET_EVENT_GRP_FAIL_STATE_FLAG | \
                                                  SET_EVENT_GRP_BUZZOFFDR_STATE_FLAG | \
                                                  SET_EVENT_GRP_BUZZOFFER_STATE_FLAG | \
                                                  SET_EVENT_GRP_DISABLE_ALL_STATE_FLAG | \
                                                  SET_EVENT_GRP_DISABLE_HW_BTN_STATE_FLAG )

#define SET_ALL_BTN_FLAGS                       ( SET_EVENT_GRP_F_B_DOOR_LIM_FLAG | \
                                                  SET_EVENT_GRP_EPANEL_DOOR_LIM_FLAG | \
                                                  SET_EVENT_GRP_RUN_BUTTON_FLAG | \
                                                  SET_EVENT_GRP_PAUSE_BUTTON_FLAG | \
                                                  SET_EVENT_GRP_STOP_BUTTON_FLAG | \
                                                  SET_EVENT_GRP_BZROFF_BUTTON_FLAG )

#define SET_ALL_BTN_EN_DIS_FLAGS                ( SET_EVENT_GRP_RUN_BTN_EN_FLAG | \
                                                  SET_EVENT_GRP_RUN_BTN_DIS_FLAG | \
                                                  SET_EVENT_GRP_PAUSE_BTN_EN_FLAG | \
                                                  SET_EVENT_GRP_PAUSE_BTN_DIS_FLAG | \
                                                  SET_EVENT_GRP_STOP_BTN_EN_FLAG | \
                                                  SET_EVENT_GRP_STOP_BTN_DIS_FLAG | \
                                                  SET_EVENT_GRP_BZROFF_BTN_EN_FLAG | \
                                                  SET_EVENT_GRP_BZROFF_BTN_DIS_FLAG )

#define SET_DOOR_LIMITS_FLAGS                   ( SET_EVENT_GRP_F_B_DOOR_LIM_FLAG | \
                                                  SET_EVENT_GRP_EPANEL_DOOR_LIM_FLAG )
                                                       
#define SET_ALL_EVENT_GROUP_BIT_FLAGS           ( SET_ALL_STATE_FLAGS | \
                                                  SET_ALL_BTN_FLAGS | \
                                                  SET_ALL_BTN_EN_DIS_FLAGS )
                    
#define EVNT_GRP_VAL    0xFFFFFFFF

// Macros to clear a specific bit of the event group after reading it.
#define CLEAR_EVENT_GRP_SELECT_BIT_FLAG         ( EVNT_GRP_VAL & ~(1UL << 0UL) ) 
#define CLEAR_EVENT_GRP_RUN_BIT_FLAG            ( EVNT_GRP_VAL & ~(1UL << 1UL) )
#define CLEAR_EVENT_GRP_PAUSE_BIT_FLAG          ( EVNT_GRP_VAL & ~(1UL << 2UL) )
#define CLEAR_EVENT_GRP_PASS_BIT_FLAG           ( EVNT_GRP_VAL & ~(1UL << 3UL) )
#define CLEAR_EVENT_GRP_FAIL_BIT_FLAG           ( EVNT_GRP_VAL & ~(1UL << 4UL) )
#define CLEAR_EVENT_GRP_BUZZOFFDR_BIT_FLAG      ( EVNT_GRP_VAL & ~(1UL << 5UL) )
#define CLEAR_EVENT_GRP_BUZZOFFER_BIT_FLAG      ( EVNT_GRP_VAL & ~(1UL << 6UL) )
#define CLEAR_EVENT_GRP_DISABLE_ALL_BIT_FLAG    ( EVNT_GRP_VAL & ~(1UL << 7UL) )
#define CLEAR_EVENT_GRP_DISABLE_HW_BTN_BIT_FLAG ( EVNT_GRP_VAL & ~(1UL << 8UL) )
#define CLEAR_EVENT_GRP_F_B_DOOR_BIT_FLAG       ( EVNT_GRP_VAL & ~(1UL << 9UL) )
#define CLEAR_EVENT_GRP_EPANEL_DOOR_BIT_FLAG    ( EVNT_GRP_VAL & ~(1UL << 10UL) )
#define CLEAR_EVENT_GRP_RUN_BUTTON_FLAG         ( EVNT_GRP_VAL & ~(1UL << 11UL) )
#define CLEAR_EVENT_GRP_PAUSE_BUTTON_FLAG       ( EVNT_GRP_VAL & ~(1UL << 12UL) )
#define CLEAR_EVENT_GRP_STOP_BUTTON_FLAG        ( EVNT_GRP_VAL & ~(1UL << 13UL) )
#define CLEAR_EVENT_GRP_BZROFF_BUTTON_FLAG      ( EVNT_GRP_VAL & ~(1UL << 14UL) )
#define CLEAR_EVENT_GRP_RUN_BTN_EN_FLAG         ( EVNT_GRP_VAL & ~(1UL << 15UL) )  
#define CLEAR_EVENT_GRP_RUN_BTN_DIS_FLAG        ( EVNT_GRP_VAL & ~(1UL << 16UL) )  
#define CLEAR_EVENT_GRP_PAUSE_BTN_EN_FLAG       ( EVNT_GRP_VAL & ~(1UL << 17UL) )  
#define CLEAR_EVENT_GRP_PAUSE_BTN_DIS_FLAG      ( EVNT_GRP_VAL & ~(1UL << 18UL) )  
#define CLEAR_EVENT_GRP_STOP_BTN_EN_FLAG        ( EVNT_GRP_VAL & ~(1UL << 19UL) )  
#define CLEAR_EVENT_GRP_STOP_BTN_DIS_FLAG       ( EVNT_GRP_VAL & ~(1UL << 20UL) )  
#define CLEAR_EVENT_GRP_BZROFF_BTN_EN_FLAG      ( EVNT_GRP_VAL & ~(1UL << 21UL) )  
#define CLEAR_EVENT_GRP_BZROFF_BTN_DIS_FLAG     ( EVNT_GRP_VAL & ~(1UL << 22UL) )  

#define CLEAR_ALL_STATE_BIT_FLAG                ( CLEAR_EVENT_GRP_SELECT_BIT_FLAG | \
                                                  CLEAR_EVENT_GRP_RUN_BIT_FLAG | \
                                                  CLEAR_EVENT_GRP_PAUSE_BIT_FLAG | \
                                                  CLEAR_EVENT_GRP_PASS_BIT_FLAG | \
                                                  CLEAR_EVENT_GRP_FAIL_BIT_FLAG | \
                                                  CLEAR_EVENT_GRP_BUZZOFFDR_BIT_FLAG | \
                                                  CLEAR_EVENT_GRP_BUZZOFFER_BIT_FLAG | \
                                                  CLEAR_EVENT_GRP_DISABLE_ALL_BIT_FLAG | \
                                                  CLEAR_EVENT_GRP_DISABLE_HW_BTN_BIT_FLAG )

#define CLEAR_ALL_BTN_FLAGS                     ( CLEAR_EVENT_GRP_F_B_DOOR_BIT_FLAG | \
                                                  CLEAR_EVENT_GRP_EPANEL_DOOR_BIT_FLAG | \
                                                  CLEAR_EVENT_GRP_RUN_BUTTON_FLAG | \
                                                  CLEAR_EVENT_GRP_PAUSE_BUTTON_FLAG | \
                                                  CLEAR_EVENT_GRP_STOP_BUTTON_FLAG | \
                                                  CLEAR_EVENT_GRP_BZROFF_BUTTON_FLAG )

#define CLEAR_ALL_BTN_EN_DIS_FLAGS              ( CLEAR_EVENT_GRP_RUN_BTN_EN_FLAG | \
                                                  CLEAR_EVENT_GRP_RUN_BTN_DIS_FLAG | \
                                                  CLEAR_EVENT_GRP_PAUSE_BTN_EN_FLAG | \
                                                  CLEAR_EVENT_GRP_PAUSE_BTN_DIS_FLAG | \
                                                  CLEAR_EVENT_GRP_STOP_BTN_EN_FLAG | \
                                                  CLEAR_EVENT_GRP_STOP_BTN_DIS_FLAG | \
                                                  CLEAR_EVENT_GRP_BZROFF_BTN_EN_FLAG | \
                                                  CLEAR_EVENT_GRP_BZROFF_BTN_DIS_FLAG )
                                                       
#define CLEAR_ALL_EVENT_GROUP_BIT_FLAGS          ( CLEAR_ALL_STATE_BIT_FLAG | \
                                                  CLEAR_ALL_BTN_FLAGS | \
                                                  CLEAR_ALL_BTN_EN_DIS_FLAGS )

#endif	/* CUSTOM_MACROS_H */

