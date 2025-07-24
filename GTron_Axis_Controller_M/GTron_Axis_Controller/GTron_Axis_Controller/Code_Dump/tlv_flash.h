/*
 * tlv_flash.h
 *
 * Created: 17-01-2025 14:42:15
 *  Author: sreevathsank
 */ 

/** 
 * Edit the members of the Param_ID enum to have your parameters.
 *
 * Edit the macro PARAM_FIRST_MEM_LOC to point to the memory location on the Flash to 
 * store the first parameter's Tag. Make sure that the value set is within the boundaries
 * of the Flash's storage.
 *
 * Define a macro PRINTF_DEBUG and set it to 0 or 1 for displaying printf messages if required.
 */

#ifndef TLV_FLASH_H_
#define TLV_FLASH_H_

#include "ext_flash.h"
#include "All_Headers.h"

#define CHAR_SIZE					1			// uint8_t size == 1 byte. Also used for booleans.
#define WORD_SIZE					2			// uint16_t size == 2 bytes.
#define INT_SIZE					4			// uint32_t / int32_t / float == 4 bytes.

// The Size of the Tag and Length of parameters.
#define TAG_SIZE					1			// 1 byte.
#define LENGTH_SIZE					1			// 1 Byte.

#define PARAM_FIRST_MEM_LOC			0x100		// Starting address of parameters stored in the Flash.

// Enum referencing all parameters to an index.
// The last member 'PARAMETER_COUNT' can be used to get the total no. of members in the enum.
typedef enum
{
	CURRENT_LIMIT_mA_FLASH,
	TORQUE_I_FLASH,
	TORQUE_P_FLASH,
	FLUX_I_FLASH,
	FLUX_P_FLASH,
	VELOCITY_I_FLASH,
	VELOCITY_P_FLASH,
	POSITION_I_FLASH,
	POSITION_P_FLASH,
	PID_POSITION_CORRECTION_WINDOW_FLASH,
	ENCODER_ALIGN_DELAY_MS_FLASH,
	HOMING_VELOCITY_FLASH,
	ENDURACE_VELOCTIY_FLASH,
	ENDURANCE_ACCELERATION_FLASH,
	ENDURANCE_JERK_FLASH,
	ROTARY_ENCODER_PPR_FLASH,
	ROTARY_ENCODER_DIRECTION_FLASH,
	LINEAR_ENCODER_CPR_FLASH,
	LINEAR_ENCODER_DIRECTION_FLASH,
	MOTOR_DIRECTION_FLASH,
	ADC_MAX_VALUE_FLASH,
	ADC_MIN_VALUE_FLASH,
	LIMIT_EDGE_DETECTION_FLASH,
	LIMIT_DELAY_MS_FLASH,
	REPEAT_RAMP_FLASH,
	ROTARY_AXIS_FLASH,
	START_RANGE_FLASH,
	END_RANGE_FLASH,
	PARAMETER_COUNT
}Param_ID;
extern Param_ID param_id;

typedef enum
{
	SUCCESS,
	NULL_PTR_ERR,
	WRITE_OP_ERR,
	READ_OP_ERR,
	TRAVERSE_SUCCESS,
	TRAVERSE_FAIL	
}ERROR_ID;
extern ERROR_ID error_id;

uint32_t gFlash_mem_ptr;	// A Tag memory pointer which stores the memory location of the tag in the Flash.

/** 
 * The structure below is the format to store key value pair type data in the Flash.
 * This type of format is used to store the Axis specific parameters.
 *
 * Tag		is the ID or name of the data.
 * Length	is the length of Value.
 * Value	is the data of the Tag / Parameter.
 */
typedef struct  
{
	uint8_t tag;
	uint8_t length;
	uint8_t value[4];
	int32_t value_32bit;
}Tlv_Flash;
extern Tlv_Flash *tlv_ptr;


typedef struct
{
	uint32_t tag_mem_loc;
	bool result;	
	bool value_check_result;
}Tlv_Traversal;
extern Tlv_Traversal *tlv_traversal;

/** 
 * \brief Writes the given ID, length of the value to be stored and the value on to the Flash.
 *
 * @param1 parameter_id		Enum Value which refers to a Parameter's Tag.
 * @param2 *value			Void Pointer which points to the data to be written.
 * @param3 length			Length of the data *value points to.
 *
 * @return uint8_t			return 1 for failure, return 0 for pass.
 */
uint8_t write_tlv_flash( Param_ID parameter_id, void *value, size_t length );

/** 
 * \brief Traverses through the Flash from the starting memory location looking for the required Tag and returns the memory location of the required Tag if found.
 * \brief Pre-requisite: Make the gFlash_mem_ptr as 0x00 or as the starting address of the first parameter.
 *
 * @param1 req_tag			The Tag to search for.
 * @param2 ptr_tlv			Address of the struct.
 *
 * @return gFlash_mem_ptr	Address of the req_tag if found in the flash.
 */
uint8_t traverse_tlv_flash ( Param_ID req_tag, Tlv_Flash *ptr_tlv, Tlv_Traversal *ptr_traverse );

/** 
 * \brief Checks the value stored in the tag to be written to and returns if it contains the same value. True if same | False if not same.
 *
 * @param1	value_to_check	The value to compare with the value stored in the Flash of the respective Parameter.
 * @param2	req_tag			The Tag of the parameter to search for in the Flash.
 * @param3	*ptr_tlv		Pointer to the structure that holds info about Tag, Length and Value of the Parameter.
 * @param4	*ptr_traverse	Pointer to the structure that holds info about the traversal data of the Parameter.
 *
 * @return	bool			Returns if value_to_check is equal to the value stored in the Flash of the Parameter.
 */
uint8_t chk_tlv( int32_t value_to_check, Param_ID req_tag, Tlv_Flash *ptr_tlv, Tlv_Traversal *ptr_traverse );

/** 
 * \brief Replies if the value to be written same as the value stored in the Flash.
 * 
 * @param1	*ptr_tlv		Pointer to the structure that holds info about Tag, Length and Value of the Parameter.
 * @param2	param_id		Enum Value which refers to a Parameter's Tag.
 * @param3	*ptr_traverse	Pointer to the structure that holds info about the traversal data of the Parameter.
 *
 * @return	bool			true = No write operation will take place, false = erase block and write operation will take place.
 */	
uint8_t check_tlv_param( Tlv_Flash *ptr_tlv, Param_ID param_id, Tlv_Traversal *ptr_traverse, int32_t value_to_check );

/** 
 * \brief Uses the Traverse function to find the Tag in the Flash memory starting from the PARAM_FIRST_MEM_LOC.
 *
 * @param1	*ptr_tlv		Pointer to the structure that holds info about Tag, Length and Value of the Parameter.
 * @param2	param_id		Enum Value which refers to a Parameter's Tag.
 * @param3	*ptr_traverse	Pointer to the structure that holds info about the traversal data of the Parameter.
 *
 * @return	ptr_tlv			Pointer to the structure that holds info about Tag, Length and Value of the Parameter.
 */
int32_t read_tlv_flash( Tlv_Flash *ptr_tlv, Param_ID param_id, Tlv_Traversal *ptr_traverse );
#endif /* TLV_FLASH_H_ */