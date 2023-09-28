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

   input  [7:0] bitline,
   input  [7:0] wordline,
   input  [7:0] selectline,
   input  wenable,
   input  form,
   input  mac,
   output [7:0] out

);
  assign A_wdone = A_wdone_reg;

  reg [7:0] internal [7:0];
  reg [7:0] out_mtx  [7:0];
  wire [7:0] out_sum [7:0][4:0];
  wire [7:0]

  integer i, j;
  always @(posedge clk) begin
    for (i = 0; i < 8; i = i + 1) begin
      for (j = 0; j < 8; j = j + 1) begin
        // Set/form 
        if(bitline[j] == 1 && wordline[i] == 1 && selectline[j] == 0)
          internal[i][j] <= 1;
          out_mtx[i][j] <= 0;
        // Reset
        else if(bitline[j] == 0 && wordline[i] == 1 && selectline[j] == 1)
          internal[i][j] <= 0;
          out_mtx[i][j] <= 0;
        // Read/MAC
        else if(bitline[j] == 0 && wordline[i] == 1 && selectline[j] == 0)
          internal[i][j] <= internal[i][j];
          out_mtx[i][j] <= internal[i][j];
        // do nothing
        else 
          internal[i][j] <= internal[i][j];
          out_mtx[i][j] <= 0;
      end
    end
  end
  // Or because 1-bit dac


  genvar k, l;
  assign out_sum[0] = out_mtx[0]
  for (k = 0; k < 8; k = k + 1) begin
    for (l = 1; l < 4; l = l + 1) begin
      assign out_sum[l][k] = out_sum[l - 1][k] + {3'b000, out_mtx[l][k]};
    end
  end

  genvar m;
  for (m = 0; m < 8; m = m + 1) begin
    if (out_sum[7][m] < 4'h4) 
      assign out[m] = 1'b0;
    else
      assign out[m] = 1'b1;
  end
endmodule
