/*
 * tlv_flash.c
 *
 * Created: 17-01-2025 14:42:31
 *  Author: sreevathsank
 */ 

#include "tlv_flash.h"
#include "system/debug/sys_debug.h"

#define SPI_OP_DELAY_ms				100

// Defining Extern Variables.
Tlv_Flash flash_tlv;
Tlv_Flash *tlv_ptr = &flash_tlv;

Tlv_Traversal traversal_tlv;
Tlv_Traversal *tlv_traversal = &traversal_tlv;

Param_ID param_id;

ERROR_ID error_id;

/** 
 * \brief Writes the given ID, length of the value to be stored and the value on to the Flash.
 * \brief If writing the first parameter
 *
 * @param1 parameter_id		Enum Value which refers to a Parameter's Tag.
 * @param2 *value			Void Pointer which points to the data to be written.
 * @param3 length			Length of the data *value points to.
 *
 * @return uint8_t			return 1 for failure, return 0 for pass.
 */
uint8_t write_tlv_flash( Param_ID parameter_id, void *value, size_t length )
{
	// Check if the pointer points to NULL or not.
	if(value == NULL) 
	{
		return NULL_PTR_ERR;	// NULL Pointer error.
	}
	
	// If the parameter tag is the 1st parameter to be written to, set the mem ptr to the 
	// mem loc where the 1st must be stored.
	if(parameter_id == 0)
	{
		gFlash_mem_ptr = PARAM_FIRST_MEM_LOC;
	}
	
	// Cast the void pointer to a uint8_t pointer
	uint8_t *byte_value = (uint8_t *)value;
	
	uint8_t param_tag = (uint8_t)parameter_id, param_len = (uint8_t)length;
	
	// Write the Tag.
	if(!EXTFLASH_write(gFlash_mem_ptr, TAG_SIZE, &param_tag) )
	{
		return WRITE_OP_ERR;	// Write Operation Failed.
	}
	SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\n W Tag    Flash_mem_ptr = 0x%x   | Tag = %d or 0x%x", gFlash_mem_ptr, param_tag, param_tag);
	// Update the Flash memory pointer.
	gFlash_mem_ptr += sizeof(param_tag);
	
	// Write the Length of the Value to be stored.
	if(!EXTFLASH_write(gFlash_mem_ptr, LENGTH_SIZE, &param_len) )
	{
		return WRITE_OP_ERR;	// Write Operation Failed.
	}
	SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\n W Length Flash_mem_ptr = 0x%x   | Length = %d or 0x%x", gFlash_mem_ptr, param_len, param_len);
	// Update the Flash memory pointer.
	gFlash_mem_ptr += sizeof(param_len);
	
	// Write the Value.
	if(!EXTFLASH_write(gFlash_mem_ptr, param_len, byte_value) )
	{
		return WRITE_OP_ERR;
	}
	
	int32_t int32_val = 0;
	for(uint8_t s = (param_len - 1); s < param_len; s--)
	{
		int32_val |= (int32_t)( byte_value[s] << (s * 8) );
	}
	//int32_t int32_val = (int32_t)( (byte_value[3] << 24) | (byte_value[2] << 16) | (byte_value[1] << 8) | byte_value[0] );
	SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\n W Value  Flash_mem_ptr = 0x%x   | Value = %ld or 0x%x\n", gFlash_mem_ptr, int32_val, int32_val);
	// Update the Flash memory pointer.
	gFlash_mem_ptr += (param_len);
	
	return 0;	// Success.
}

/** 
 * \brief Traverses through the Flash from the starting memory location looking for the required Tag and returns the memory location of the required Tag if found.
 * \brief Pre-requisite: Make the gFlash_mem_ptr as 0x00 or as the starting address of the first parameter.
 *
 * @param1 req_tag			The Tag to search for.
 * @param2 ptr_tlv			Address of the struct.
 *
 * @return	uint8_t			Returns enum Error_ID value.
 */
uint8_t traverse_tlv_flash ( Param_ID req_tag, Tlv_Flash *ptr_tlv, Tlv_Traversal *ptr_traverse )
{	
	// Check if a NULL ptr will not be dereferenced by any chance. If it is a NULL, hop off right now!
	if( (ptr_traverse == NULL) || (ptr_tlv == NULL) ) 
	{ 
		return NULL_PTR_ERR; 
	}
	// Traversing until we find the req_tag or reach the last parameter stored.
	for(uint32_t p_cnt = 0; p_cnt < PARAMETER_COUNT; p_cnt++)
	{
		// Read the mem loc of the 1st tag.
		if(!EXTFLASH_read(gFlash_mem_ptr, TAG_SIZE, &ptr_tlv->tag) )
		{
			return READ_OP_ERR;
		}
		//SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nTraversing: Tag = 0x%x or %d | Tag Mem Loc = 0x%x\n", ptr_tlv->tag, ptr_tlv->tag, gFlash_mem_ptr);
		
		// Check if the read tag is the same as the required tag.
		if(ptr_tlv->tag == req_tag) 
		{
			// If the tag stored is the same as the tag found.
			ptr_traverse->tag_mem_loc = gFlash_mem_ptr; 
			ptr_traverse->result = true;
			
			// Increment mem_ptr to read the length of the value.
			gFlash_mem_ptr += (uint32_t) TAG_SIZE;
			//SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nIncremented Mem Loc by Tag Size = 0x%x\n", gFlash_mem_ptr);
			
			// Read the length of the value.
			EXTFLASH_read(gFlash_mem_ptr, LENGTH_SIZE, &ptr_tlv->length);
			
			// Increment the mem_ptr by the length of value.
			gFlash_mem_ptr += (uint32_t) LENGTH_SIZE;
			//SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nIncremented Mem Loc by Value Size (%d) = 0x%x\n", ptr_tlv->length, gFlash_mem_ptr);
			
			// Read the value.
			memset(&ptr_tlv->value, 0x00, sizeof(ptr_tlv->value) );
			EXTFLASH_read(gFlash_mem_ptr, ptr_tlv->length, ptr_tlv->value);
			
			return 0;	// Success.
		}
		// Increment mem_ptr to read the length of the value.
		gFlash_mem_ptr += (uint32_t) TAG_SIZE;
		//SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nIncremented Mem Loc by Tag Size = 0x%x\n", gFlash_mem_ptr);
		
		// Read the length of the value.
		EXTFLASH_read(gFlash_mem_ptr, LENGTH_SIZE, &ptr_tlv->length);
		
		// If Both Tag and Length are 0xFF, then its no use searching after this.
		if( (ptr_tlv->tag == 0xFF) || (ptr_tlv->length == 0xFF) )
		{
			SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nBoth Tag and Length are 0xFF\n");
			if(gFlash_mem_ptr == (PARAM_FIRST_MEM_LOC + TAG_SIZE) )
			{
				gFlash_mem_ptr = PARAM_FIRST_MEM_LOC;
				uint32_t current_lim = 0x00;
				write_tlv_flash(CURRENT_LIMIT_mA_FLASH, &current_lim, 4);
				current_lim = 0x00;
				write_tlv_flash(TORQUE_I_FLASH, &current_lim, 2);
			}
			return TRAVERSE_FAIL;
		}
		
		// Increment the mem_ptr by the length of value + 1.
		gFlash_mem_ptr += (uint32_t) ptr_tlv->length + 1;
		//SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nIncremented Mem Loc by Value Size (%d) = 0x%x\n", ptr_tlv->length, gFlash_mem_ptr);
		
		// Read the value.
		memset(&ptr_tlv->value, 0x00, sizeof(ptr_tlv->length) );
		EXTFLASH_read(gFlash_mem_ptr, ptr_tlv->length, ptr_tlv->value);
	}
	ptr_traverse->result = false;
	return TRAVERSE_FAIL;
}

/** 
 * \brief Checks the value stored in the tag to be written to and returns if it contains the same value. True if same | False if not same.
 *
 * @param1	value_to_check	The value to compare with the value stored in the Flash of the respective Parameter.
 * @param2	req_tag			The Tag of the parameter to search for in the Flash.
 * @param3	*ptr_tlv		Pointer to the structure that holds info about Tag, Length and Value of the Parameter.
 * @param4	*ptr_traverse	Pointer to the structure that holds info about the traversal data of the Parameter.
 *
 * @return	uint8_t			Returns enum Error_ID value.
 */
uint8_t chk_tlv( int32_t value_to_check, Param_ID req_tag, Tlv_Flash *ptr_tlv, Tlv_Traversal *ptr_traverse )
{
	// Check if a NULL ptr will not be dereferenced by any chance. If it is a NULL, hop off right now!
	if( (ptr_traverse == NULL) || (ptr_tlv == NULL) ) 
	{ 
		return NULL_PTR_ERR; 
	}
	// Set gFlash_mem_ptr to 0x00 before calling the traverse function.
	gFlash_mem_ptr = PARAM_FIRST_MEM_LOC;
	uint8_t ret_value = traverse_tlv_flash(req_tag, ptr_tlv, ptr_traverse);
	
	uint32_t read_mem_ptr = ptr_traverse->tag_mem_loc;
	
	// Check if the traversal is successful or not. return TRAVERSE_FAIL for failure.
	if(ptr_traverse->result == false) 
	{ 
		return TRAVERSE_FAIL; 
	}
	if(ret_value != 0)
	{
		return ret_value;
	}
	// Read the value of the tag.
	if(!EXTFLASH_read(read_mem_ptr, TAG_SIZE, &ptr_tlv->tag) )
	{
		return READ_OP_ERR;
	}

	// Increment the read_mem_ptr by size of Tag.
	read_mem_ptr += (uint32_t) TAG_SIZE;
	
	// Read the length of the value.
	if(!EXTFLASH_read(read_mem_ptr, LENGTH_SIZE, &ptr_tlv->length) )
	{
		return READ_OP_ERR;
	}
	
	// Increment the read_mem_ptr by the size of Length.
	read_mem_ptr += (uint32_t) LENGTH_SIZE;
	
	// Read the value.
	memset(&ptr_tlv->value, 0x00, sizeof(ptr_tlv->length) );
	if(!EXTFLASH_read(read_mem_ptr, ptr_tlv->length, ptr_tlv->value) )
	{
		return READ_OP_ERR;
	}
	
	int32_t cmp_val = ( (ptr_tlv->value[3] << 24) | (ptr_tlv->value[2] << 16) | (ptr_tlv->value[1] << 8) | ptr_tlv->value[0] );
	
	ptr_traverse->value_check_result = (value_to_check == cmp_val) ? true : false;
	SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nCheck Result = %d | To be stored %ld == Stored %ld ?\n", ptr_traverse->value_check_result, value_to_check, cmp_val );
	
	return 0 ;	// Success.
}

/** 
 * \brief Replies if the value to be written same as the value stored in the Flash.
 * 
 * @param1	*ptr_tlv		Pointer to the structure that holds info about Tag, Length and Value of the Parameter.
 * @param2	param_id		Enum Value which refers to a Parameter's Tag.
 * @param3	*ptr_traverse	Pointer to the structure that holds info about the traversal data of the Parameter.
 *
 * @return	uint8_t			Returns enum Error_ID value.
 */	
uint8_t check_tlv_param( Tlv_Flash *ptr_tlv, Param_ID param_id, Tlv_Traversal *ptr_traverse, int32_t value_to_check )
{
	// A dummy value, for testing.
	//int32_t value_to_check = 0x101;
	// Check if the value stored is the same as the one we're going to write.
	//int32_t value_to_check = decoding_CAN_Byte_Data();
	uint8_t ret_value = chk_tlv(value_to_check, param_id, ptr_tlv, ptr_traverse);
	if(ret_value != 0)
	{
		return ret_value;
	}
	switch(axis_id)
	{
		case X_AXIS: { message_Id = CAN_ID(REPLY_ID_X, X_ADDR, 0x64, CHK_FW_PARAM); break; }
		case Y_AXIS: { message_Id = CAN_ID(REPLY_ID_Y, Y_ADDR, 0x64, CHK_FW_PARAM); break; }
		case Z_AXIS: { message_Id = CAN_ID(REPLY_ID_Z, Z_ADDR, 0x64, CHK_FW_PARAM); break; }
		default: break;
	}
	if(ptr_traverse->value_check_result)
	{
		// The value we're going to write is the same as the one stored in the flash. No write required.
		int32_t ret_data = 0;
		encoding_CAN_Byte_Data(ret_data);
		can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, ret_data);
		can_Write(message_Id, ret_data);
		SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nValue stored is same. Not writing\n");
	}
	else
	{
		// Send CAN reply with the data 1.
		// Erase the sector PARAM_FIRST_MEM_LOC
		// and be ready to receive and write the
		// entire JSON to the Flash.
		int32_t ret_data = 1;
		encoding_CAN_Byte_Data(ret_data);
		can_tx_frame.data[4] = can_Message_Calculate_Crc(message_Id, ret_data);
		can_Write(message_Id, ret_data);
		EXTFLASH_erase(PARAM_FIRST_MEM_LOC, FLASH_ERASE_SECTOR_SIZE);
		SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nValue stored is not same. Erasing Sector...\n");
	}
	return 0; // Success.
}

/** 
 * \brief Uses the Traverse function to find the Tag in the Flash memory starting from the PARAM_FIRST_MEM_LOC.
 *
 * @param1	*ptr_tlv		Pointer to the structure that holds info about Tag, Length and Value of the Parameter.
 * @param2	param_id		Enum Value which refers to a Parameter's Tag.
 * @param3	*ptr_traverse	Pointer to the structure that holds info about the traversal data of the Parameter.
 *
 * @return	uint8_t			Returns enum Error_ID value.
 */
int32_t read_tlv_flash( Tlv_Flash *ptr_tlv, Param_ID param_id, Tlv_Traversal *ptr_traverse )
{
	// NULL check of the pointers.
	if( (ptr_tlv == NULL) || (ptr_traverse == NULL) )
	{
		return NULL_PTR_ERR;
	}
	
	// Get the mem loc of the parameter to be read.
	gFlash_mem_ptr = PARAM_FIRST_MEM_LOC;
	uint8_t ret_val_err = traverse_tlv_flash( param_id, ptr_tlv, ptr_traverse );
	
	if(ret_val_err != 0)
	{
		ptr_tlv->tag = 0x00;
		ptr_tlv->length = 0x00;
		ptr_tlv->value[0] = 0x00; ptr_tlv->value[1] = 0x00; ptr_tlv->value[2] = 0x00; \
		ptr_tlv->value[3] = 0x00; 
		ptr_tlv->value_32bit = 0x00;
		return ret_val_err;
	}
	
	int32_t val_i32 = 0;
	// To print the Value read from the Flash.
	for(uint8_t s = (tlv_ptr->length - 1); s < tlv_ptr->length; s--)
	{
		val_i32 |= ( ptr_tlv->value[s] << (s * 8) );
		
	}
	ptr_tlv->value_32bit = val_i32;
	//val_i32 = (int32_t) ( (ptr_tlv->value[3] << 24) | (ptr_tlv->value[2] << 16) | (ptr_tlv->value[1] << 8) | ptr_tlv->value[0] );
	SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "\nRead: Tag = 0x%x or %ld | Length = 0x%x or %ld | Value = 0x%x or %ld\n", ptr_tlv->tag, ptr_tlv->tag,\
							ptr_tlv->length, ptr_tlv->length, val_i32, val_i32);
	
	// Check if the read was successful.
	if(ptr_traverse->result) 
	{ 
		return ptr_tlv->value_32bit; 
	}
	else
	{
		return READ_OP_ERR;
	}
}