module crossbar_mac (
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

   input  [7:0] A_row,
   input  [7:0] A_data,
   input  A_wenable,
   output A_wdone,

   input  [7:0] x,
   
   output [7:0] b

);
  reg A_wdone_reg = 0;
  assign A_wdone = A_wdone_reg;

  reg [7:0] A [7:0];
  wire [7:0]A0,A1,A2,A3,A4,A5,A6,A7;
  assign A0 = A[0];
  assign A1 = A[1];
  assign A2 = A[2];
  assign A3 = A[3];
  assign A4 = A[4];
  assign A5 = A[5];
  assign A6 = A[6];
  assign A7 = A[7];

  wire [2:0] A_row_enc;
  // encoder
  assign A_row_enc[2] = A_row[4] | A_row[5] | A_row[6] | A_row[7];
  assign A_row_enc[1] = A_row[2] | A_row[3] | A_row[6] | A_row[7];
  assign A_row_enc[0] = A_row[1] | A_row[3] | A_row[5] | A_row[7];

  // done tracking, weird sensitivities, it should be fine
  always @(posedge clk) begin
    if (A_wenable && ~A_wdone_reg) begin
      A[A_row_enc] = A_data;
      A_wdone_reg = 1'b1;
    end else if (~A_wenable && A_wdone_reg) begin
      A_wdone_reg = 1'b0;    
    end
  end

  wire [15:0] mult_arr [7:0];

  
  wire [15:0] add1 [3:0];
  wire [15:0] add2 [1:0];
  wire [15:0] result;
  genvar i;
  genvar j;
  genvar k;
  // multiplication
  generate
    for(i = 0; i < 8; i = i + 1) begin
      assign mult_arr[i] = x * A[i];
    end
    for(j = 0; j < 4; j = j + 1) begin
      assign add1[j] = mult_arr[2 * j] + mult_arr[2 * j + 1];
    end
    for(k = 0; k < 2; k = k + 1) begin
      assign add2[k] = add1[2 * k] + add1[2 * k + 1];
    end
  endgenerate

  assign result = add2[0] + add2[1];
  assign b = result[7:0];
endmodule
