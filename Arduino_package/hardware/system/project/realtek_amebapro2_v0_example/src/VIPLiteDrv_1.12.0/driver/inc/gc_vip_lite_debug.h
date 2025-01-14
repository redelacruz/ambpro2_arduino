/******************************************************************************\
|* Copyright (c) 2017-2023 by Vivante Corporation.  All Rights Reserved.      *|
|*                                                                            *|
|* The material in this file is confidential and contains trade secrets of    *|
|* of Vivante Corporation.  This is proprietary information owned by Vivante  *|
|* Corporation.  No part of this work may be disclosed, reproduced, copied,   *|
|* transmitted, or used in any way for any purpose, without the express       *|
|* written permission of Vivante Corporation.                                 *|
|*                                                                            *|
\******************************************************************************/

#ifndef _VIP_LITE_DEBUG_H
#define _VIP_LITE_DEBUG_H

#include <vip_lite.h>
#include <gc_vip_user_port.h>
#include <gc_vip_user_hardware.h>


#define GCVIP_GET_STRING    gcvip_os_snprint
#define GCVIP_DUMP_STRING   gcvip_user_print_string
#define CHECK_FUNC_CONFIG                                        \
{                                                                \
  if (network != VIP_NULL) {                                     \
      if ((network->occur_hang != vip_true_e) &&                 \
          (context->func_config.enable_capture == vip_false_e)){ \
          return VIP_SUCCESS;                                    \
      }                                                          \
  }                                                              \
  else {                                                         \
      if (context->func_config.enable_capture == vip_false_e) {  \
          return VIP_SUCCESS;                                    \
      }                                                          \
  }                                                              \
}

#define CHECK_DUMP_NBG                                           \
{                                                                \
    if (vip_false_e == context->func_config.enable_dump_nbg) {   \
        return VIP_SUCCESS;                                      \
    }                                                            \
}
#if vpmdDUMP_NBG_RESOURCE
vip_status_e gcvip_dump_network_outputs(
	vip_network_t *network
);

vip_status_e gcvip_dump_network_inputs(
	vip_network_t *network
);

vip_status_e gcvip_dump_nbg(
	gcvip_file_t file,
	void *data,
	vip_uint32_t size
);
#endif

#if vpmdENABLE_LAYER_DUMP
vip_status_e gcvip_layer_dump(
	gcvip_lite_segment_t *segment,
	vip_network_t *network,
	vip_uint32_t id
);
#endif

#if vpmdENABLE_CNN_PROFILING
typedef struct _gcvip_profile_probe_t {
	/* NN */
	vip_uint32_t       nn_layer_id;
	vip_uint32_t       nn_layer_id_overflow;
	vip_uint32_t       nn_instr_info;
	vip_uint32_t       nn_total_busy_cycle;
	vip_uint32_t       nn_total_busy_cycle_overflow;
	vip_uint32_t       nn_total_read_cycle_ddr;
	vip_uint32_t       nn_total_read_cycle_ddr_overflow;
	vip_uint32_t       nn_total_read_valid_bandwidth_ddr;
	vip_uint32_t       nn_total_read_valid_bandwidth_ddr_overflow;
	vip_uint32_t       nn_total_write_cycle_ddr;
	vip_uint32_t       nn_total_write_cycle_ddr_overflow;
	vip_uint32_t       nn_total_write_valid_bandwidth_ddr;
	vip_uint32_t       nn_total_write_valid_bandwidth_ddr_overflow;
	vip_uint32_t       nn_total_read_cycle_sram;
	vip_uint32_t       nn_total_read_cycle_sram_overflow;
	vip_uint32_t       nn_total_write_cycle_sram;
	vip_uint32_t       nn_total_write_cycle_sram_overflow;
	vip_uint32_t       nn_total_mac_cycle;
	vip_uint32_t       nn_total_mac_cycle_overflow;
	vip_uint32_t       nn_total_mac_count;
	vip_uint32_t       nn_total_mac_count_overflow;
	vip_uint32_t       nn_zero_coef_skip_count;
	vip_uint32_t       nn_zero_coef_skip_count_overflow;
	vip_uint32_t       nn_non_zero_coef_count;
	vip_uint32_t       nn_non_zero_coef_count_overflow;

	vip_uint32_t       nn_reserved_counter[DATA_PER_REGISTER * MODULE_NN_RESERVED_COUNTER_NUM];
	vip_uint32_t       nn_total_idle_cycle_core_overflow[NN_CORE_NUM];
	vip_uint32_t       nn_total_idle_cycle_core[NN_CORE_NUM];

	/* TP */
	vip_uint32_t       tp_layer_id;
	vip_uint32_t       tp_layer_id_overflow;
	vip_uint32_t       tp_total_busy_cycle;
	vip_uint32_t       tp_total_busy_cycle_overflow;

	vip_uint32_t       tp_total_read_bandwidth_cache;
	vip_uint32_t       tp_total_read_bandwidth_cache_overflow;
	vip_uint32_t       tp_total_write_bandwidth_cache;
	vip_uint32_t       tp_total_write_bandwidth_cache_overflow;

	vip_uint32_t       tp_total_read_bandwidth_sram;
	vip_uint32_t       tp_total_read_bandwidth_sram_overflow;
	vip_uint32_t       tp_total_write_bandwidth_sram;
	vip_uint32_t       tp_total_write_bandwidth_sram_overflow;


	vip_uint32_t       tp_total_read_bandwidth_ocb;
	vip_uint32_t       tp_total_read_bandwidth_ocb_overflow;
	vip_uint32_t       tp_total_write_bandwidth_ocb;
	vip_uint32_t       tp_total_write_bandwidth_ocb_overflow;

	vip_uint32_t       tp_fc_pix_count;
	vip_uint32_t       tp_fc_zero_skip_count;
	vip_uint32_t       tp_fc_pix_count_overflow;
	vip_uint32_t       tp_fc_zero_skip_count_overflow;

	vip_uint32_t       tp_fc_coef_count;
	vip_uint32_t       tp_fc_coef_zero_count;
	vip_uint32_t       tp_fc_coef_count_overflow;
	vip_uint32_t       tp_fc_coef_zero_count_overflow;

	vip_uint32_t       tp_total_idle_cycle_core[TP_CORE_NUM];
	vip_uint32_t       tp_total_idle_cycle_core_overflows[TP_CORE_NUM];
} gcvip_profile_probe_t;
#endif

#if (vpmdENABLE_HANG_DUMP > 1) || vpmdENABLE_CAPTURE
typedef enum _gcvip_capture_type {
	GCVIP_CAPTURE_TYPE_CAP    = 0,
	GCVIP_CAPTURE_TYPE_HANG   = 1,
	GCVIP_CAPTURE_TYPE_GROUP  = 2,
} gcvip_capture_type_e;

typedef enum _gcvip_capture_buf_type {
	GCVIP_CAPTURE_COMMAND = 0,
	GCVIP_CAPTURE_STATES,
	GCVIP_CAPTURE_POOL,
	GCVIP_CAPTURE_INPUT,
	GCVIP_CAPTURE_VERIFY,
	GCVIP_CAPTURE_MEMORY,
}   gcvip_capture_buf_type_e;

void gcvip_capture_buffer(
	gcvip_file_t fp,
	void  *buffers,
	vip_uint32_t physical,
	vip_uint32_t size,
	gcvip_capture_buf_type_e type
);
#endif

#if vpmdENABLE_CAPTURE
vip_status_e gcvip_capture_network(
	vip_network network
);
#endif

typedef enum _gcvip_record_info_type {
	RECORD_TYPE_NONE                = 0,
	RECORD_TYPE_NN_COMMAND          = 1,
	RECORD_TYPE_TP_COMMAND          = 2,
	RECORD_TYPE_SH_COMMAND          = 3,
	RECORD_TYPE_NN_WEIGHT           = 4,
	RECORD_TYPE_TP_WEIGHT           = 5,
	RECORD_TYPE_SH_WEIGHT           = 6,
	RECORD_TYPE_DYNA_DATA           = 7,
	RECORD_TYPE_NN_WEIGHT_BITSTREAM = 8,
	RECORD_TYPE_SP_WEIGHT           = 9,
	RECORD_TYPE_SP_WEIGHT_BITSTREAM = 10,
	RECORD_TYPE_MAX
} gcvip_record_info_type_e;

#if vpmdENABLE_RECORD_INFO
typedef struct _gcvip_record_info {
	gcvip_record_info_type_e record_type;
	vip_uint32_t size;
	vip_uint32_t offset; /* when record type is coeff, indicate patch index */
	vip_uint32_t layer_id;
	vip_uint32_t op_index;
	vip_uint32_t abs_id;
} gcvip_record_info_t;

void gcvip_record_info_add_list(
	gcvip_lite_segment_t *segment,
	vip_uint32_t offset,
	vip_uint32_t size,
	vip_uint32_t layer_id,
	vip_uint32_t abs_op_id,
	vip_uint32_t op_index,
	vip_uint32_t type
);
#endif

#if (vpmdENABLE_CAPTURE > 1) || (vpmdENABLE_HANG_DUMP > 1)
vip_status_e gcvip_capture_hang_dump(
	vip_network_t *network
);

vip_status_e gcvip_capture_network_output(
	gcvip_file_t capture_file,
	vip_network_t *network
);

vip_status_e gcvip_capture_network_input(
	gcvip_file_t capture_file,
	vip_network network
);
#endif

#if vpmdENABLE_CAPTURE || (vpmdENABLE_HANG_DUMP > 1)
void gcvip_capture_record_list(
	gcvip_file_t capture_file,
	vip_network_t *network
);

vip_status_e gcvip_capture_dump_states(
	gcvip_file_t capture_file,
	vip_network_t *network,
	gcvip_lite_segment_t *segment
);

vip_status_e gcvip_capture_hardware_info(
	gcvip_lite_context_t *context,
	gcvip_file_t capture_file,
	vip_network_t *network
);

vip_status_e gcvip_capture_register_info(
	gcvip_lite_context_t *context,
	gcvip_file_t capture_file,
	vip_network_t *network
);

vip_status_e gcvip_capture_init_command(
	gcvip_file_t capture_file,
	vip_network_t *network
);

#if vpmdPRELOAD_COEFF > 1
vip_status_e gcvip_capture_npu_preload_coeff(
	gcvip_file_t capture_file,
	vip_network_t *network
);
#endif

vip_status_e gcvip_capture_init(
	gcvip_lite_context_t *context,
	vip_network network,
	vip_group group,
	gcvip_capture_type_e type
);

vip_status_e gcvip_capture_uninit(
	gcvip_lite_context_t *context,
	vip_network network,
	vip_group group
);
#endif

#if vpmdENABLE_GROUP_MODE && ((vpmdENABLE_HANG_DUMP > 1) || (vpmdENABLE_CAPTURE > 1))
vip_status_e gcvip_capture_group(
	vip_group group,
	vip_bool_e is_hang
);
#endif

#if vpmdENABLE_BW_PROFILING
#if vpmdENABLE_PROBE_MODE
vip_status_e gcvip_init_profiling(
	gcvip_lite_context_t *context,
	vip_network_t *network
);
vip_status_e gcvip_uninit_profiling(
	gcvip_lite_context_t *context,
	vip_network_t *network
);
#endif
vip_status_e gcvip_start_profiling(
	gcvip_lite_context_t *context,
	vip_network_t *network,
	vip_uint32_t op_id
);
vip_status_e gcvip_end_profiling(
	gcvip_lite_context_t *context,
	vip_network_t *network,
	vip_uint32_t op_id
);
#endif

#if vpmdENABLE_CNN_PROFILING
vip_status_e gcvip_layer_info(
	vip_network_t *network,
	vip_char_t *name,
	vip_uint32_t layer_id,
	vip_uint32_t op_id,
	vip_uint32_t uid
);

vip_uint32_t gcvip_get_num_initend_operation(
	vip_network_t *network
);

vip_status_e gcvip_layer_profile(
	gcvip_lite_context_t *context,
	vip_network_t *network,
	gcvip_lite_segment_t *segment
);
#endif

#if vpmdENABLE_DEBUG_LOG > 2
vip_status_e gckvip_dump_nbg_entry(
	vip_network network
);
#endif

#if vpmdENABLE_CHECKSUM
vip_status_e gcvip_network_checksum(
	vip_network_t *network
);

#if vpmdENABLE_CHECKSUM > 1
vip_status_e gcvip_nbg_checksum(
	void *data,
	vip_uint32_t size
);
#endif
#endif
#endif
