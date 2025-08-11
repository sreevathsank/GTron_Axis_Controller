/*
 * DBG_bring_up.c
 *
 * Created: 15-12-2023 16:41:35
 *  Author: sreevathsank
 */ 

/** 
 * \file
 *
 * \brief Contains the init functions.  
 */

#include "Bring_Up/DBG_bring_up.h"
#include "Code_Dump/tlv_flash.h"

struct timer_task ramp_timer_struct;
struct timer_task vel_timer_struct;

void debounce_delay(uint32_t time_taken)
{
	current_time = millis();
	prev_time = current_time;
	while( (current_time - prev_time) < time_taken )
	{
		current_time = millis();
	}
	return;
}

/** 
 * \brief Takes two parameters iteration and time_taken(ms). Toggles the 3 LEDs on the Axis Controller for the number of iterations with time_taken used as delay between each toggle.
 *
 * @param[in] iteration Determines the number of iteration the LED toggle sequence executes.
 * @param[in] time_taken Delay between each individual toggle of LEDs in ms.
 * @return void.
 */

void led_Blink(uint32_t iteration, uint32_t time_taken)
{
	for(int i = 0; i < iteration; i++)
	{
		gpio_toggle_pin_level(DBGLED1);
		//while(!debounce_delay(time_taken));
		delay_ms(time_taken);
				
		gpio_toggle_pin_level(DBGLED1);
		gpio_toggle_pin_level(DBGLED3);
		//while(!debounce_delay(time_taken));
		delay_ms(time_taken);
		
		gpio_toggle_pin_level(DBGLED3);
		gpio_toggle_pin_level(DBGLED2);
		//while(!debounce_delay(time_taken));
		delay_ms(time_taken);
		
		gpio_toggle_pin_level(DBGLED2);
	}
	gpio_set_pin_level(DBGLED1, 1);
	gpio_set_pin_level(DBGLED2, 1);
	gpio_set_pin_level(DBGLED3, 1);
}


//The io descriptor for UART
// struct io_descriptor *io;
// void init_UART(void)
// {
// 	usart_sync_get_io_descriptor(&TARGET_IO, &io);
// 	usart_sync_enable(&TARGET_IO);
// 	printf("\n-----UART works!-----\n");
// 	//io_write(io, (uint8_t *)"Hello World!", 12);
// }

/** 
 * \brief Toggles Debug LED 1 depending on the state of the Enable 4671 pin.
 *
 * @param void.
 * @return void.
 */
void enablePin_Led_Check(void)
{
	//int32_t enable_state;
	gpio_set_pin_level(EN_4671, 1);
	gpio_set_pin_level(DBGLED1, gpio_get_pin_level(EN_4671));
	delay_ms(5000);
	gpio_set_pin_level(EN_4671, 0);
}

/** 
 * \brief Sets the timer_flag to 1 whenever this callback function is called by the timer interrupt. This flag is used by the ramp generation algorithm.
 *
 * @param void
 * @return void
 */
void timer_ramp_cb(void)
{
	rParams.timer_ramp_flag = true;
	rParams.time_ramp += 1;
	return;
}

void vel_timer_cb(void)
{
	vel_struct.flags.reeler_vel_timer = true;
	//printf("\nVEL_TIMER\n");
	return;
}

/**  
 * \brief Initialises the timer module. The interval for interrupt trigger is set by the macro TIMER_INTERVAL_MS in ms.
 *
 * @param void
 * @return void
 */
void init_timer_ramp(void)
{
	// Init the timer used for ramp generation.
	ramp_timer_struct.interval = RAMP_INTERVAL_MS;
	ramp_timer_struct.cb       = timer_ramp_cb;
	ramp_timer_struct.mode     = TIMER_TASK_REPEAT;
	timer_add_task(&TIMER_0, &ramp_timer_struct);
	
	// Init the timer used for sending position during knob mode.
	vel_timer_struct.interval	= VEL_INTERVAL_MS;
	vel_timer_struct.cb			= vel_timer_cb;
	vel_timer_struct.mode		= TIMER_TASK_REPEAT;
	timer_add_task(&VEL_TIMER, &vel_timer_struct);
}

/** 
 * \brief Interrupt Callback function for CAN receive operation. Increments a receive counter.
 *
 * @param void
 * @return void
 */
void can_Rx_Cb(void)
{
	can_rx_int++;
	return;
}

/** 
 * \brief Initialises the CAN 1 instance and Transmit and Receive Callback functions.
 *
 * @param void
 * @return void
 */
void can_Init(void)
{
	can_begin(&CAN_1, CAN1, 500, SILENT);
	can_set_txcb(&CAN_1, (FUNC_PTR)can_Tx_Cb);
	can_set_rxcb(&CAN_1, (FUNC_PTR)can_Rx_Cb);
	can_set_filter(&CAN_1, 0, 0, EXT_ID);
	
	return;
}

void tx_cb_UART(const struct usart_async_descriptor *const io_descr)
{
	
}

void rx_cb_UART(const struct usart_async_descriptor *const io_descr)
{
	
}

void init_UART(void)
{
	
	usart_sync_get_io_descriptor(&TARGET_IO, &io);
	usart_sync_enable(&TARGET_IO);	

	//usart_async_register_callback(&UART_0, USART_ASYNC_TXC_CB, tx_cb_UART);
	usart_async_register_callback(&UART_0, USART_ASYNC_RXC_CB, rx_cb_UART);
	//usart_async_register_callback(&UART_0, USART_ASYNC_ERROR_CB, err_cb);
	usart_async_get_io_descriptor(&UART_0, &oi);
	usart_async_enable(&UART_0);
}

void tx_TMC2209_UART_cb( void )
{
	return;
}

void init_TMC2209_UART( void )
{
	//struct io_descriptor *io_tmc2209;

	
	return;
}


/** 
 * \brief Gets n no. of ADC values, averages them and finds out the Axis based on the value range
 *
 */
void check_Current_Axis_ADC(void)
{
	uint32_t adc_sum = 0, adc_result;
	uint32_t adc_max = 0, adc_min = UINT32_MAX;
	
	for(int32_t iter = 0; iter < ADC_NUM_READINGS; iter++)
	{
		adc_sync_read_channel(&ADC_0, ADC_CHANNEL, adc_reading.adc_8bit, ADC_READ_LENGTH);
		if(adc_reading.adc_16bit > adc_max)
		{
			adc_max = adc_reading.adc_16bit;
		}
		else if(adc_reading.adc_16bit < adc_min)
		{
			adc_min = adc_reading.adc_16bit;
		}
		adc_sum += adc_reading.adc_16bit;
	}
	adc_result = (uint32_t)(adc_sum / ADC_NUM_READINGS);
	PRINTF_DEBUG ? printf("\nADC Max = %ld | ADC Avg = %ld | ADC Min = %ld\n", (uint32_t)adc_max, (uint32_t)adc_result, (uint32_t)adc_min) : 0;
	//if( (adc_result >= GTRON_AXC_ADC_MIN) && (adc_result <= GTRON_AXC_ADC_MAX) )
	{
		axis_id = X_AXIS;
	}
	return;
}

/** \brief Read the ADC RAW values of channel I0 and I1 from TMC4671 when the PWM is off and ENABLE IN pin is low.
 *
 */
void read_4671_ADC_Raw(void)
{
	// Disable the PWM of TMC4671.
	tmc4671_writeInt(MOTOR, TMC4671_PWM_SV_CHOP, ZERO_HEX);
	
	// Set the Enable pin of TMC4671 to LOW.
	gpio_set_pin_level(EN_4671, LOW);
	
	// Set the ADC_ADDR register to show ADC I0 and I1 RAW values.
	tmc4671_writeInt(MOTOR, TMC4671_ADC_RAW_ADDR, ZERO_HEX);
	
	uint32_t adc_raw_value = 0;
	uint32_t adc_i0_raw = 0, adc_i1_raw = 0;
	uint32_t adc_scale = 65;
	
	for(int32_t a = 0; a < ADC_RAW_NUM_READINGS; a++ )
	{
		adc_raw_value = tmc4671_readInt(MOTOR, TMC4671_ADC_RAW_DATA);
		
		adc_i0_raw += ( adc_raw_value & 0xFFFF );
		
		adc_i1_raw += ( (adc_raw_value >> 16) & 0xFFFF );
	}
	adc_i0_raw = ( adc_i0_raw / ADC_RAW_NUM_READINGS );
	adc_i1_raw = ( adc_i1_raw / ADC_RAW_NUM_READINGS );
	printf("\nADC RAW Values i0 = %ld | i1 = %ld\n", adc_i0_raw, adc_i1_raw);
	
	adc_i0_raw = ( (adc_i0_raw & 0x0000FFFF) | ((uint32_t) adc_scale << 16) );
	adc_i1_raw = ( (adc_i1_raw & 0x0000FFFF) | ((uint32_t) adc_scale << 16) );
	
	tmc4671_writeInt(MOTOR, TMC4671_ADC_I0_SCALE_OFFSET, adc_i0_raw);
	tmc4671_writeInt(MOTOR, TMC4671_ADC_I1_SCALE_OFFSET, adc_i1_raw);
	
	tmc4671_writeInt(MOTOR, TMC4671_PWM_SV_CHOP, 0x07);
	return;
}

void read_Set_Parameters_From_Flash(void)
{
	motor_dir_rev = ( read_tlv_flash(tlv_ptr, MOTOR_DIRECTION_FLASH, tlv_traversal) == 0) ? false : true ;
	// Limit Edge Detection == 0/false -> falling edge | == 1/true -> Rising Edge.
	lim_edge_detection = ( read_tlv_flash(tlv_ptr, LIMIT_EDGE_DETECTION_FLASH, tlv_traversal) == 0) ? false : true;
	axis_params.lin_enc_res = read_tlv_flash(tlv_ptr, LINEAR_ENCODER_CPR_FLASH, tlv_traversal);
	axis_params.rotary_axis_enabled = ( read_tlv_flash(tlv_ptr, ROTARY_AXIS_FLASH, tlv_traversal) == 0 ) ? false : true;
	limit_variables.soft_limit_low = read_tlv_flash(tlv_ptr, START_RANGE_FLASH, tlv_traversal);
	limit_variables.soft_limit_high = read_tlv_flash(tlv_ptr, END_RANGE_FLASH, tlv_traversal);
	/*hri_eic_write_CONFIG_reg(EIC,
							1,
							(CONF_EIC_FILTEN8 << EIC_CONFIG_FILTEN0_Pos) | EIC_CONFIG_SENSE0(CONF_EIC_SENSE8)
							| (CONF_EIC_FILTEN9 << EIC_CONFIG_FILTEN1_Pos) | EIC_CONFIG_SENSE1(CONF_EIC_SENSE9)
							| (CONF_EIC_FILTEN10 << EIC_CONFIG_FILTEN2_Pos) | EIC_CONFIG_SENSE2(CONF_EIC_SENSE10)
							| (CONF_EIC_FILTEN11 << EIC_CONFIG_FILTEN3_Pos) | EIC_CONFIG_SENSE3(CONF_EIC_SENSE11)
							| (CONF_EIC_FILTEN12 << EIC_CONFIG_FILTEN4_Pos) | EIC_CONFIG_SENSE4(CONF_EIC_SENSE12)
							| (CONF_EIC_FILTEN13 << EIC_CONFIG_FILTEN5_Pos) | EIC_CONFIG_SENSE5(CONF_EIC_SENSE13)
							| (CONF_EIC_FILTEN14 << EIC_CONFIG_FILTEN6_Pos) | EIC_CONFIG_SENSE6(CONF_EIC_SENSE14)
							| (CONF_EIC_FILTEN15 << EIC_CONFIG_FILTEN7_Pos) | EIC_CONFIG_SENSE7(CONF_EIC_SENSE15)
							| 0);
	*/
	// PI parameters for X, Y and Z axes.
	switch((axis_current)axis_id)
	{
		case X_AXIS:
			axis_params.start_voltage		= 1000;
			axis_params.align_delay			= read_tlv_flash(tlv_ptr, ENCODER_ALIGN_DELAY_MS_FLASH, tlv_traversal);//250;
			axis_params.torque_flux_limit	= read_tlv_flash(tlv_ptr, CURRENT_LIMIT_mA_FLASH, tlv_traversal);//1800;
			axis_params.torque_i			= read_tlv_flash(tlv_ptr, TORQUE_I_FLASH, tlv_traversal);//20000; //3850;
			axis_params.torque_p			= read_tlv_flash(tlv_ptr, TORQUE_P_FLASH , tlv_traversal);//8000;  //3078;
			axis_params.flux_i				= read_tlv_flash(tlv_ptr, FLUX_I_FLASH, tlv_traversal);//20000; //3850;
			axis_params.flux_p				= read_tlv_flash(tlv_ptr, FLUX_P_FLASH, tlv_traversal);//8000;  //3078;
			axis_params.velocity_i			= read_tlv_flash(tlv_ptr, VELOCITY_I_FLASH, tlv_traversal);//5000;  //300;
			axis_params.velocity_p			= read_tlv_flash(tlv_ptr, VELOCITY_P_FLASH, tlv_traversal);//2500;  //1000;
			axis_params.position_i			= read_tlv_flash(tlv_ptr, POSITION_I_FLASH, tlv_traversal);//0;
			axis_params.position_p			= read_tlv_flash(tlv_ptr, POSITION_P_FLASH, tlv_traversal);//2000;	 //500;
			axis_params.home_search_vel		= read_tlv_flash(tlv_ptr, HOMING_VELOCITY_FLASH, tlv_traversal);//160;
			axis_params.home_switch_vel		= (axis_params.home_search_vel / 10);
			axis_params.endurance_vel		= read_tlv_flash(tlv_ptr, ENDURACE_VELOCTIY_FLASH, tlv_traversal);////1000;
			axis_params.acceleration		= read_tlv_flash(tlv_ptr, ENDURANCE_ACCELERATION_FLASH, tlv_traversal);//5000;
			axis_params.acceleration_delta	= (axis_params.acceleration * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS));
			axis_params.jerk				= read_tlv_flash(tlv_ptr, ENDURANCE_JERK_FLASH, tlv_traversal);//5000;
			axis_params.jerk_delta			= (axis_params.jerk * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS) * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS));
		break;								  
		case Y_AXIS:
			axis_params.start_voltage		= 1000;
			axis_params.align_delay			= read_tlv_flash(tlv_ptr, ENCODER_ALIGN_DELAY_MS_FLASH, tlv_traversal);//250;
			axis_params.torque_flux_limit	= read_tlv_flash(tlv_ptr, CURRENT_LIMIT_mA_FLASH, tlv_traversal);//1800;
			axis_params.torque_i			= read_tlv_flash(tlv_ptr, TORQUE_I_FLASH, tlv_traversal);//20000; //3850;
			axis_params.torque_p			= read_tlv_flash(tlv_ptr, TORQUE_P_FLASH , tlv_traversal);//8000;  //3078;
			axis_params.flux_i				= read_tlv_flash(tlv_ptr, FLUX_I_FLASH, tlv_traversal);//20000; //3850;
			axis_params.flux_p				= read_tlv_flash(tlv_ptr, FLUX_P_FLASH, tlv_traversal);//8000;  //3078;
			axis_params.velocity_i			= read_tlv_flash(tlv_ptr, VELOCITY_I_FLASH, tlv_traversal);//5000;  //300;
			axis_params.velocity_p			= read_tlv_flash(tlv_ptr, VELOCITY_P_FLASH, tlv_traversal);//2500;  //1000;
			axis_params.position_i			= read_tlv_flash(tlv_ptr, POSITION_I_FLASH, tlv_traversal);//0;
			axis_params.position_p			= read_tlv_flash(tlv_ptr, POSITION_P_FLASH, tlv_traversal);//2000;	 //500;
			axis_params.home_search_vel		= read_tlv_flash(tlv_ptr, HOMING_VELOCITY_FLASH, tlv_traversal);//160;
			axis_params.home_switch_vel		= (axis_params.home_search_vel / 10);
			axis_params.endurance_vel		= read_tlv_flash(tlv_ptr, ENDURACE_VELOCTIY_FLASH, tlv_traversal);////1000;
			axis_params.acceleration		= read_tlv_flash(tlv_ptr, ENDURANCE_ACCELERATION_FLASH, tlv_traversal);//5000;
			axis_params.acceleration_delta	= (axis_params.acceleration * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS));
			axis_params.jerk				= read_tlv_flash(tlv_ptr, ENDURANCE_JERK_FLASH, tlv_traversal);//5000;
			axis_params.jerk_delta			= (axis_params.jerk * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS) * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS));
		break;
		case Z_AXIS:
			axis_params.start_voltage		= 1500;
			axis_params.align_delay			= read_tlv_flash(tlv_ptr, ENCODER_ALIGN_DELAY_MS_FLASH, tlv_traversal);//250;//500;
			axis_params.torque_flux_limit	= read_tlv_flash(tlv_ptr, CURRENT_LIMIT_mA_FLASH, tlv_traversal);//1800;//2000;
			axis_params.torque_i			= read_tlv_flash(tlv_ptr, TORQUE_I_FLASH, tlv_traversal);//20000; //3850;//15000;
			axis_params.torque_p			= read_tlv_flash(tlv_ptr, TORQUE_P_FLASH , tlv_traversal);//8000;  //3078;//5300;
			axis_params.flux_i				= read_tlv_flash(tlv_ptr, FLUX_I_FLASH, tlv_traversal);//20000; //3850;//15000;
			axis_params.flux_p				= read_tlv_flash(tlv_ptr, FLUX_P_FLASH, tlv_traversal);//8000;  //3078;//5300;
			axis_params.velocity_i			= read_tlv_flash(tlv_ptr, VELOCITY_I_FLASH, tlv_traversal);//5000;  //300;//4000;
			axis_params.velocity_p			= read_tlv_flash(tlv_ptr, VELOCITY_P_FLASH, tlv_traversal);//2500;  //1000;//2000;
			axis_params.position_i			= read_tlv_flash(tlv_ptr, POSITION_I_FLASH, tlv_traversal);//0;//0;
			axis_params.position_p			= read_tlv_flash(tlv_ptr, POSITION_P_FLASH, tlv_traversal);//2000;	 //500;//1000;
			axis_params.home_search_vel		= read_tlv_flash(tlv_ptr, HOMING_VELOCITY_FLASH, tlv_traversal);//160;//160;
			axis_params.home_switch_vel		= (axis_params.home_search_vel / 10);//(axis_params.home_search_vel / 10);
			axis_params.endurance_vel		= read_tlv_flash(tlv_ptr, ENDURACE_VELOCTIY_FLASH, tlv_traversal);////1000;//1000;
			axis_params.acceleration		= read_tlv_flash(tlv_ptr, ENDURANCE_ACCELERATION_FLASH, tlv_traversal);//5000;//8000;
			axis_params.acceleration_delta	= (axis_params.acceleration * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS));//(axis_params.acceleration * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS));
			axis_params.jerk				= read_tlv_flash(tlv_ptr, ENDURANCE_JERK_FLASH, tlv_traversal);//5000;//8000;
			axis_params.jerk_delta			= (axis_params.jerk * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS) * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS));//(axis_params.jerk * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS) * (RAMP_INTERVAL_MS * ONE_MS_IN_SECONDS));
		break;
		default: break;
	}
	//PRINTF_DEBUG && printf("\naccel delta =%.4f | jerk delta = %.4f\n", axis_params.acceleration_delta, axis_params.jerk_delta);
	return;
}

/** 
 * \brief Initialises SPI and does a Pings the TMC4671 via SPI.
 *
 * @param void
 * @return bool 
 */
bool check_4671_version_spi(void)
{
	SPI_0_init();
	SPI_0_enable();
	delay_ms(10);
	tmc4671_writeInt(MOTOR, TMC4671_CHIPINFO_ADDR, ZERO_HEX);
	delay_ms(1);
	
	bool ret_val = VERSION_4671 == tmc4671_readInt(MOTOR, TMC4671_CHIPINFO_DATA);
	ret_val ? PRINTF_DEBUG ? printf("\nSPI Comms with TMC4671 is successful\n"): 0
			: 0;
    return ret_val;
}

bool check_passive_flash_spi(void)
{
	EXT_FLASH_SPI_init();
	EXT_FLASH_SPI_enable();
	//hri_sercomspi_set_CTRLA_ENABLE_bit(SERCOM3);
	delay_ms(10);
	//EXTFLASH_erase(PARAM_FIRST_MEM_LOC, FLASH_ERASE_SECTOR_SIZE);
	// Check the Flash Manufacture and Device ID.
	if( EXTFLASH_open() )
	{
		PRINTF_DEBUG && printf("\nExt Flash ID Check Pass\n");
		ioxp_Init();
		return 0; // Success.
	}
	return 1; // Failure.
}

/** 
 * \brief Resets TMC4671 by disabling PWM and toggling RST_4671 pin LOW and then HIGH.
 *
 * @param void
 * @return void
 */
void reset_TMC4671(void)
{
	//tmc4671_disablePWM(MOTOR);
	delay_ms(1);
	gpio_set_pin_level(RST_4671, 0);
	delay_ms(1);
	gpio_set_pin_level(RST_4671, 1);	
}

/** 
 * \brief Defines the Global Variables to be used.
 *
 * @param void
 * @return void
 */
void define_All_Global_Variables(void)
{
	// Open Loop Variables.
	open_loop.acceleration = 0x00000064;
	open_loop.velocity = -1 * 0x00000064;
	open_loop.uq_ud = 0x00000FA0;
	
	// Ramp Variables.
	ramp_State = ACCEL;
	timer_flag = false;
	current_time = 0;
	v = 0; v_temp = 0;
	prev_time = 0;
	//non_rep = 1;
	move_given_trapezoidal_ramp = true;
	move_given_s_ramp = true;
	repeat_ramp = 0;		// Remove
	//t_Position = 500000;
	t_Position = 100000;
	
	// Limit variables flags.
	limit_variables.left_limit_flag = false;
	limit_variables.right_limit_flag = false;
	limit_variables.homing = true;					// Initially motor goes for Homing Sequence.
	limit_variables.hit_limit_left = false;
	limit_variables.hit_limit_right = false;
	limit_variables.loop = false;
	limit_variables.first_limit_hit = false;
	limit_variables.other_limit_hit = false;
	limit_variables.switch_seq_flag = true;			// Executes Switching Sequence after Homing Sequence
	limit_variables.homing_done = false;
	
	rfs_ping_rxvd = false;
	
	// Limit variables position.
	limit_variables.right_limit_position = 0;
	limit_variables.left_limit_position = 0;
	limit_variables.home_position = 0;
	limit_variables.zero_limit_position = 0;
	limit_variables.other_limit_position = 0;
	limit_variables.middle_position = 0;
	limit_variables.tpos = 0;
	limit_variables.soft_limit_high = 0;
	limit_variables.soft_limit_low = 0;
	
	velocity_limit = 0;
	rParams.phase_error = 0;
	
	// AutoFocus variables.
	autofocus_variables.combined = 0U;
	autofocus_variables.startPointAF = 0;
	autofocus_variables.gQDECstepSizeCount = 0U;
	autofocus_variables.starting_position = 0;
	autofocus_variables.sweep_no = 0;
	memset(autofocus_variables.af_table, 0x00, sizeof(autofocus_variables.af_table));
	idx = 0;
		
	//AutoFocus flags.
	autofocus_variables.one_received = false;
	autofocus_variables.change_comp_cnt = false;
	
	// Velocity Knob mode variables.
	//vel_struct.test_enabled  = false;
	//vel_struct.position_send = false;
	vel_struct.vel_state	 = VEL_STATE_0;
	
	can_tx_frame.data_64bit = 0;
	message_Id = 0;
	
	x_axis_encoder_counters.direction = (gpio_get_pin_level(ROTENC_DIR) == HIGH) ? (1) : (-1);
}

/** 
 * \brief Initialises SPI, CAN, PWM, Timer and writes TMC4671 register to set up the motor. Also does a SPI ping test.
 *
 * @param void
 * @return void
 */
void call_All_Init_Functions(void)
{
	
	// PWM_0 is clk source for TMC4671. Produces 25MHz.
	pwm_set_parameters(&PWM_0, 1, 1);
	pwm_enable(&PWM_0);

	// PWM_1 is clk source for FPGA. Produces 12.5MHz.
	//pwm_set_parameters(&PWM_1, 1, 1);
	//pwm_enable(&PWM_1);
	
	gpio_set_pin_level(DBGLED3, 1);
	gpio_set_pin_level(DBGLED1, 1);
	gpio_set_pin_level(DBGLED2, 1);
	gpio_set_pin_level(EXT_CS, HIGH);
	gpio_set_pin_level(IOXP_CS, HIGH);
	//SYSTICK_INIT();
	//EXTFLASH_init();
	init_UART();
	init_TMC2209_UART();
	//TMC2209_UART_init();
	//TMC2209_UART_enable();
	adc_sync_enable_channel(&ADC_0, 0);
	check_Current_Axis_ADC();
	if(!check_4671_version_spi()) 
	{
		PRINTF_DEBUG && printf("\n--------TMC4671 SPI Check Failed--------\n");
		return;
	}
	gpio_set_pin_level(IOXP_CS, HIGH);
	
	if(check_passive_flash_spi())
	{
		PRINTF_DEBUG && printf("\n------Passive Flash SPI Check Failed-----\n");
	}
	gpio_set_pin_level(IOXP_CS, HIGH);
	
	PRINTF_DEBUG && printf("\nExt Flash CS -> %d | IOXP CS -> %d\n", gpio_get_pin_level(EXT_CS), gpio_get_pin_level(IOXP_CS) );
	
	read_Set_Parameters_From_Flash();
	reset_Basics(MOTOR);
	//configure_ABN(MOTOR, 2400);
	init_Basics(MOTOR);
	init_PosMode(MOTOR);
	read_4671_ADC_Raw();
	init_timer_ramp();
	
	//timer_start(&TIMER_0);
	can_Init();
	init_ext_irq_limits();
	//init_Enc_Cnt_Dir();
	return;
}

void print_uart(const uint8_t *const str_output)
{
	size_t str_length = strlen(str_output);
	//delay_us(100);
	//for(str_length = 0; *str_output != '\0'; str_length ++);
	io_write(&UART_0, (uint8_t *)"on\n", 3);
}

/** 
 * \brief Runs the stepper motor in open loop for the given openloop parameters and sets up the motor to be driven in closed loop.
 *
 * @param void
 * @return void
 */
void run_Open_Loop_Setup_Closed_Loop(uint32_t time_taken)
{
	//delay_ms(100);
	gpio_set_pin_level(EN_4671, 1);
	set_RampVelocity(0);
	open_loop_fb();	
	delay_ms(time_taken);
	//while( debounce_delay(time_taken) );
	open_loop.acceleration = 0;
	open_loop.velocity = 0;
	open_loop.uq_ud = 0;
	open_loop_fb();
	align_Rotor_ABNEnc(MOTOR, axis_params.start_voltage); // Contains Encoder Direction.
	tmc4671_writeInt(MOTOR, TMC4671_PHI_E_SELECTION, 0x00000003);
	tmc4671_setModeMotion(MOTOR, POSITION_MODE);
	tmc4671_setAbsolutTargetPosition(MOTOR, tmc4671_getActualPosition(MOTOR));	
	tmc4671_writeInt(MOTOR, TMC4671_MODE_RAMP_MODE_MOTION, STOPPED_MODE);
	tmc4671_setVelocityLimit(MOTOR, ZERO_HEX);
	
	switch(axis_id)
	{
		case X_AXIS:
			PRINTF_DEBUG ? printf("\nX Axis Rotary Encoder Resolution = %5ld ppr", tmc4671_readInt(MOTOR, TMC4671_ABN_DECODER_PPR)):0;
			PRINTF_DEBUG && printf("\nX Axis Rotary Encoder Direction = %ld\n", tmc4671_readInt(MOTOR, TMC4671_ABN_DECODER_MODE));
			PRINTF_DEBUG ? printf("\nX Axis Linear Encoder Resolution = %5ld ppr", tmc4671_readInt(MOTOR, TMC4671_ABN_2_DECODER_PPR)):0;
			PRINTF_DEBUG && printf("\nX Axis Linear Encoder Direction = %ld\n", tmc4671_readInt(MOTOR, TMC4671_ABN_2_DECODER_MODE));
		break;
		case Y_AXIS:
			PRINTF_DEBUG ? printf("\nY Axis Rotary Encoder Resolution = %5ld ppr", tmc4671_readInt(MOTOR, TMC4671_ABN_DECODER_PPR)):0;
			PRINTF_DEBUG && printf("\nY Axis Rotary Encoder Direction = %ld\n", tmc4671_readInt(MOTOR, TMC4671_ABN_DECODER_MODE));
			PRINTF_DEBUG ? printf("\nY Axis Linear Encoder Resolution = %5ld ppr", tmc4671_readInt(MOTOR, TMC4671_ABN_2_DECODER_PPR)):0;
			PRINTF_DEBUG && printf("\nX Axis Linear Encoder Direction = %ld\n", tmc4671_readInt(MOTOR, TMC4671_ABN_2_DECODER_MODE));
		break;
		case Z_AXIS:
			PRINTF_DEBUG ? printf("\nZ Axis Rotary Encoder Resolution = %5ld ppr", tmc4671_readInt(MOTOR, TMC4671_ABN_DECODER_PPR)):0;
			PRINTF_DEBUG && printf("\nZ Axis Rotary Encoder Direction = %ld\n", tmc4671_readInt(MOTOR, TMC4671_ABN_DECODER_MODE));
		break;
		default: break;
	}
	
	return;
}

/** 
 * \brief Running the motor in openloop and getting the openloop_phi and abn_decoder_phi_e values to know if the direction of the encoder is aligned or not.
 *
 * @param  void
 * @return void
 */
void doEncoderDirectionCheck(void)
{
	// Set phi_e_selection to 2:phi_e_openloop
	tmc4671_writeInt(MOTOR, TMC4671_PHI_E_SELECTION, 0x02);
	
	// Set mode motion to 8:up_ud_ext
	tmc4671_setModeMotion(MOTOR, UQ_UD_MODE);
	
	// Set openloop_velocity target, openloop acceleration and ud_ext.
	tmc4671_writeInt(MOTOR, TMC4671_OPENLOOP_ACCELERATION, 0x3C);
	tmc4671_writeInt(MOTOR, TMC4671_OPENLOOP_VELOCITY_TARGET, 0x01);
	tmc4671_writeInt(MOTOR, TMC4671_UQ_UD_EXT, 0x7D0);
	delay_ms(50);
	
	int32_t curr_abn_phi_e = 0, prev_abn_phi_e = 0, diff_abn_phi_e = 0;
	int32_t curr_openloop_phi = 0, prev_openloop_phi = 0, diff_openloop_phi = 0;
	bool is_abn_negative = false, is_openloop_negative = false;
	
	// Get the values to check difference.
	prev_abn_phi_e = tmc4671_readRegister16BitValue(MOTOR, TMC4671_ABN_DECODER_PHI_E_PHI_M, BIT_16_TO_31);
	prev_openloop_phi = tmc4671_readInt(MOTOR, TMC4671_OPENLOOP_PHI);
	delay_ms(100);
	curr_abn_phi_e = tmc4671_readRegister16BitValue(MOTOR, TMC4671_ABN_DECODER_PHI_E_PHI_M, BIT_16_TO_31);
	curr_openloop_phi = tmc4671_readInt(MOTOR, TMC4671_OPENLOOP_PHI);
	
	// Find the difference
	diff_abn_phi_e = curr_abn_phi_e - prev_abn_phi_e;
	diff_openloop_phi = curr_openloop_phi - prev_openloop_phi;
	
	// Check if the difference is positive or negative.
	//PRINTF_DEBUG ? printf("\nprev_abn_phi_e     = %6ld | curr_abn_phi_e    = %6ld | curr - prev = %6ld", prev_abn_phi_e, curr_abn_phi_e, diff_abn_phi_e) : 0;
	is_abn_negative = ( diff_abn_phi_e == abs(diff_abn_phi_e) ) ? false : true;
	//(is_abn_negative) ? (PRINTF_DEBUG ? printf(" | Difference is -ve"): 0) : (PRINTF_DEBUG ? printf(" | Difference is +ve"): 0);
	
	//PRINTF_DEBUG ? printf("\nprev_openloop_ phi = %6ld | curr_openloop_phi = %6ld | curr - prev = %6ld", prev_openloop_phi, curr_openloop_phi, diff_openloop_phi) : 0;
	is_openloop_negative = ( diff_openloop_phi == abs(diff_openloop_phi) ) ? false : true;
	//(is_openloop_negative) ? (PRINTF_DEBUG ? printf(" | Difference is -ve"): 0) : (PRINTF_DEBUG ? printf(" | Difference is +ve"): 0);
	
	if(is_openloop_negative == is_abn_negative)
	{
		switch(axis_id)
		{
			case X_AXIS: PRINTF_DEBUG ? printf("\n\nX axis Rotary Encoder Direction IS aligned.") : 0; break;
			case Y_AXIS: PRINTF_DEBUG ? printf("\n\nY axis Rotary Encoder Direction IS aligned.") : 0; break;
			case Z_AXIS: PRINTF_DEBUG ? printf("\n\nZ axis Rotary Encoder Direction IS aligned.") : 0; break;
			default: break;
		}
	}
	else 
	{
		switch(axis_id)
		{
			case X_AXIS: PRINTF_DEBUG ? printf("\nX Axis Rotary Encoder Direction IS NOT aligned.") : 0; break;
			case Y_AXIS: PRINTF_DEBUG ? printf("\nY Axis Rotary Encoder Direction IS NOT aligned.") : 0; break;
			case Z_AXIS: PRINTF_DEBUG ? printf("\nZ Axis Rotary Encoder Direction IS NOT aligned.") : 0; break;
			default: break;
		}
		if(tmc4671_readInt(MOTOR, TMC4671_ABN_DECODER_MODE) == ABN_ENC_FORWARD_DIRECTION)
		{
			switch(axis_id)
			{
				case X_AXIS: PRINTF_DEBUG ? printf("\nX Axis Rotary Encoder Direction is FORWARD. Set it to REVERSE.") : 0; break;
				case Y_AXIS: PRINTF_DEBUG ? printf("\nY Axis Rotary Encoder Direction is FORWARD. Set it to REVERSE.") : 0; break;
				case Z_AXIS: PRINTF_DEBUG ? printf("\nZ Axis Rotary Encoder Direction is FORWARD. Set it to REVERSE.") : 0; break;
				default: break;
			}
		}
		else
		{
			switch(axis_id)
			{
				case X_AXIS: PRINTF_DEBUG ? printf("\nX Axis Rotary Encoder Direction is REVERSE, Set it to FORWARD.") : 0; break;
				case Y_AXIS: PRINTF_DEBUG ? printf("\nY Axis Rotary Encoder Direction is REVERSE, Set it to FORWARD.") : 0; break;
				case Z_AXIS: PRINTF_DEBUG ? printf("\nZ Axis Rotary Encoder Direction is REVERSE, Set it to FORWARD.") : 0; break;
				default: break;
			}
		}
		/*PRINTF_DEBUG ? printf("\n\nCorrecting Encoder Direction") : 0;
		if(tmc4671_readInt(MOTOR, TMC4671_ABN_DECODER_MODE) == ABN_ENC_FORWARD_DIRECTION)
		{
			tmc4671_writeInt(MOTOR, TMC4671_ABN_DECODER_MODE, ABN_ENC_REVERSE_DIRECTION);
		}
		else
		{
			tmc4671_writeInt(MOTOR, TMC4671_ABN_DECODER_MODE, ABN_ENC_FORWARD_DIRECTION);
		}*/
	}
	tmc4671_writeInt(MOTOR, TMC4671_OPENLOOP_VELOCITY_TARGET, (-1) );
	delay_ms(150);

	return;
}
