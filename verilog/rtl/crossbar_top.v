`default_nettype none

module crossbar_top (
  `ifdef USE_POWER_PINS
    inout vdda1,	// User area 1 3.3V supply
    inout vdda2,	// User area 2 3.3V supply
    inout vssa1,	// User area 1 analog ground
    inout vssa2,	// User area 2 analog ground
    inout vccd1,	// User area 1 1.8V supply
    inout vccd2,	// User area 2 1.8v supply
    inout vssd1,	// User area 1 digital ground
    inout vssd2,	// User area 2 digital ground
  `endif

  // for simulation purposes
  input clk,

  input  [7: 0] A_row,
  input  [7: 0] A_data,
  input  A_wenable,
  output A_wdone,

  input  [7: 0] x,
  
  output [7:0] b
);
  wire [7:0] A_row_dac;
  wire [7:0] A_data_dac;
  wire A_wenable_dac;
  wire [7:0] x_dac;

  // ============================
  //     Declare DAC blocks
  // ============================

  genvar i;
  generate 
    for(i = 0; i < 8; i = i + 1) begin
      // A row, should bump up voltage
      dac A_row_dac_block[7:0](
        `ifdef USE_POWER_PINS
          .vdda1(vdda1),
          .vdda2(vdda2),
          .vssa1(vssa1),
          .vssa2(vssa2),
          .vccd1(vccd1),
          .vccd2(vccd2),
          .vssd1(vssd1),
          .vssd2(vssd2),
        `endif
        .x_i(A_row[i]),
        .x_o(A_row_dac[i])
      );
      // A data
      dac A_data_dac_block[7:0](
        `ifdef USE_POWER_PINS
          .vdda1(vdda1),
          .vdda2(vdda2),
          .vssa1(vssa1),
          .vssa2(vssa2),
          .vccd1(vccd1),
          .vccd2(vccd2),
          .vssd1(vssd1),
          .vssd2(vssd2),
        `endif
        .x_i(A_data[i]),
        .x_o(A_data_dac[i])
      );
      // x
      dac x_dac_block[7:0](

        `ifdef USE_POWER_PINS
          .vdda1(vdda1),
          .vdda2(vdda2),
          .vssa1(vssa1),
          .vssa2(vssa2),
          .vccd1(vccd1),
          .vccd2(vccd2),
          .vssd1(vssd1),
          .vssd2(vssd2),
        `endif
        .x_i(x[i]),
        .x_o(x_dac[i])
      );
    end
  endgenerate

  // A write enable
  dac A_wenable_dac_block(
    `ifdef USE_POWER_PINS
      .vdda1(vdda1),
      .vdda2(vdda2),
      .vssa1(vssa1),
      .vssa2(vssa2),
      .vccd1(vccd1),
      .vccd2(vccd2),
      .vssd1(vssd1),
      .vssd2(vssd2),
    `endif
    .x_i(A_wenable),
    .x_o(A_wenable_dac)
  );

  // ============================
  // Declare MAC Unit (crossbar)
  // ============================
  crossbar_mac mac (
    .clk(clk),
    .A_row(A_row_dac),
    .A_data(A_data_dac),
    .A_wenable(A_wenable),
    .A_wdone(A_wdone),
    .x(x_dac),
    .b(b)
  );

endmodule
