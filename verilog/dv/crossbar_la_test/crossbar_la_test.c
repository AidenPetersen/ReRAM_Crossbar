#include <defs.h>
#include <stub.c>

void main(){
  // setup GPIO  config
  // we don't use gpio, so just set them to whatever...
  reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
  reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;

  reg_mprj_io_15 = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_14 = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_13 = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_12 = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_11 = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_10 = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_9  = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_8  = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_7  = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_6  = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_5  = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_4  = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_3  = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_2  = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_1  = GPIO_MODE_USER_STD_OUTPUT;
  reg_mprj_io_0  = GPIO_MODE_USER_STD_OUTPUT;

    
  // Apply configuration and wait to finish
  reg_mprj_xfer = 1;
  while(reg_mprj_xfer == 1);
  
  // x of Ax=b, 8-bits
  reg_la0_oenb = reg_la0_iena = 0xFFFFFFFF;
  // A of Ax=b, 8x8
  reg_la1_oenb = reg_la0_iena = 0xFFFFFFFF;
  reg_la2_oenb = reg_la0_iena = 0xFFFFFFFF;
  // b of Ax=b, 8+-bits
  reg_la3_oenb = reg_la3_iena = 0x00000000;

  // Start assigning values
  // x = [1, 0, 1, 1, 0, 1, 0, 1]
  reg_la0_data = 0b10110101;
  // A = I
  reg_la1_data = 0x80402010;
  reg_la2_data = 0x08040201;
  // print result 
  printf("%d", reg_la3_data);

  

}

