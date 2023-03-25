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
  
  /*
   * bitmap: 
   * la0
   * 0:7 : x
   *
   * la1
   * 0:7  : write row (one hot encoded)
   * 8:15 : write data
   * 16:16: write enable
   * 17:17: write done
   *
   * la3
   * 96:127 : b
   */
  // x stuff
  reg_la0_oenb = reg_la0_iena = 0x000000FF;

  // A stuff
  reg_la1_oenb = reg_la0_iena = 0x0001FFFF;

  // doesn't matter
  reg_la2_oenb = reg_la0_iena = 0x00000000;

  // b stuff
  reg_la3_oenb = reg_la3_iena = 0x00000000;

  // Write identity matrix weights
  for(int i = 0; i < 8; i++){
    // set write row
    reg_la1_data &= 0xFFFFFF00;
    reg_la1_data |= (1 << (8-i));

    // set write data
    reg_la1_data &= 0xFFFF00FF;
    reg_la1_data |= (1 << (i + 8));

    // start write
    reg_la1_data |= 0x00010000;
    // wait for write to complete
   
    // clear just the 16th bit
    reg_la1_data &= 0xFFFEFFFF;
  }

  // assign x val
  reg_la0_data |= 0b10110101;
  // printf("%d", reg_la3_data);

  reg_la0_data |= 0b10100010;
  // printf("%d", reg_la3_data);

  reg_la0_data |= 0b11110100;
  // printf("%d", reg_la3_data);

}
