//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.2 (win64) Build 3064766 Wed Nov 18 09:12:45 MST 2020
//Date        : Sun May  3 15:10:58 2026
//Host        : DESKTOP-7CFQ9ND running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (btn_tri_i,
    cs_n_0,
    led_tri_o_tri_o,
    miso_0,
    mosi_0,
    reset,
    sclk_0,
    sys_clock,
    usb_uart_rxd,
    usb_uart_txd);
  input [3:0]btn_tri_i;
  output cs_n_0;
  output [15:0]led_tri_o_tri_o;
  input miso_0;
  output mosi_0;
  input reset;
  output sclk_0;
  input sys_clock;
  input usb_uart_rxd;
  output usb_uart_txd;

  wire [3:0]btn_tri_i;
  wire cs_n_0;
  wire [15:0]led_tri_o_tri_o;
  wire miso_0;
  wire mosi_0;
  wire reset;
  wire sclk_0;
  wire sys_clock;
  wire usb_uart_rxd;
  wire usb_uart_txd;

  design_1 design_1_i
       (.btn_tri_i(btn_tri_i),
        .cs_n_0(cs_n_0),
        .led_tri_o_tri_o(led_tri_o_tri_o),
        .miso_0(miso_0),
        .mosi_0(mosi_0),
        .reset(reset),
        .sclk_0(sclk_0),
        .sys_clock(sys_clock),
        .usb_uart_rxd(usb_uart_rxd),
        .usb_uart_txd(usb_uart_txd));
endmodule
