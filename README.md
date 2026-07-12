# Ondevice RTL/FPGA Portfolio

SystemVerilog/Verilog 기반 RTL 설계, FPGA 보드 검증, AXI/APB 주변장치, Vitis C 애플리케이션을 정리한 포트폴리오 저장소입니다. SPI/I2C/UART 통신 IP, RV32I CPU와 APB peripheral, 센서/시간 전송 시스템까지 온디바이스 시스템반도체 설계 과정에서 구현한 프로젝트를 포함합니다.

이 README는 면접관이 저장소를 열었을 때 어떤 프로젝트가 무엇을 보여주는지 빠르게 파악할 수 있도록 작성했습니다. 개인 연락처 등 이력서의 민감 정보는 포함하지 않았습니다.

## Core Skills

- Verilog/SystemVerilog RTL 설계
- Vivado FPGA 프로젝트 구성 및 Basys-3 계열 constraint 사용
- AXI4-Lite custom IP packaging 및 memory-mapped register 설계
- AMBA APB master/peripheral 설계
- RISC-V RV32I CPU datapath/control unit 설계
- UART, SPI, I2C protocol FSM 구현
- Vitis C application, HAL/driver 계층 분리
- FPGA board 입출력: LED, switch, button, FND, UART terminal, SR04, DHT11

## Project Map

| Directory | What It Shows | Key Files |
| --- | --- | --- |
| `AXI_SPI/` | AXI4-Lite SPI master custom IP, MicroBlaze/Vitis control software, SPI board demo, colocated UVM copy | `ip_repo/axi_spi_m_1.0/hdl/axi_spi_m_v1_0_S00_AXI.v`, `ip_repo/axi_spi_m_1.0/hdl/axi_spi_m_v1_0.v`, `vitis/src/HAL/SPI/SPI.c`, `vitis/src/ap/ap_main.c`, `0504_AXI_SPI_UVM/` |
| `AXI_I2C/` | AXI4-Lite I2C master custom IP, open-drain SDA control, Vitis HAL/app, I2C slave/FND demo | `ip_repo/i2c_1.0/hdl/i2c_v1_0_S00_AXI.v`, `ip_repo/i2c_1.0/hdl/i2c_v1_0.v`, `vitis/src/ap/I2C/i2c.c`, `vitis/src/main.c`, `20260502_I2C_slave.srcs/sources_1/new/i2c_slave.sv` |
| `RV32I/` | RV32I CPU, APB master, BRAM/GPIO/GPO/FND/UART peripherals, memory-mapped I/O execution | `RV32I.srcs/sources_1/new/RV32_CPU.sv`, `RV32I.srcs/sources_1/new/rv32i_datapath.sv`, `RV32I.srcs/sources_1/new/APB_master.sv`, `RV32I.srcs/sources_1/new/RV32I_TOP.sv` |
| `UART_SR_DHT2/` | UART command path with watch/stopwatch, SR04 distance, DHT11 temperature/humidity, FND output | `UART_SR_DHT2.srcs/sources_1/new/TOP_main.v`, `UART_SR_DHT2.srcs/sources_1/new/SR04.v`, `UART_SR_DHT2.srcs/sources_1/new/dth11_ctrl.v`, `UART_SR_DHT2.srcs/sources_1/new/top_uart.v` |
| `UART_SV/` | Standalone UART TX/RX and FIFO implementation with simulation benches | `UART_SV.srcs/sources_1/new/TOP_UART.sv`, `UART_SV.srcs/sources_1/new/fifo.sv`, `UART_SV.srcs/sim_1/new/tb_UART.sv` |
| `SPI_fnd_M/` | SPI master board-side project with button debounce | `SPI_fnd_M.srcs/sources_1/imports/new/Top_Master.sv`, `SPI_fnd_M.srcs/sources_1/imports/new/SPI_master.sv` |
| `SPI_fnd_S/` | SPI slave board-side project with FND display path | `SPI_fnd_S.srcs/sources_1/imports/new/Top_Slave.sv`, `SPI_fnd_S.srcs/sources_1/imports/new/SPI_slave.sv`, `SPI_fnd_S.srcs/sources_1/imports/new/fnd_controller_direct.sv` |
| `stopwatch.srcs/` | Watch/stopwatch datapath, UART ASCII sender, FND controller, simulation benches | `sources_1/new/top_stopwatch.v`, `sources_1/imports/new/top_uart.v`, `sim_1/new/tb_stopwatch.v` |
| `sram_sv.srcs/` | SystemVerilog SRAM and pre/post-style simulation benches | `sources_1/new/sram.sv`, `sim_1/new/tb_sram.sv`, `sim_1/new/tb_sram_pre.sv` |

## Main Design Highlights

### AXI4-Lite SPI IP

`AXI_SPI/ip_repo/axi_spi_m_1.0/hdl/axi_spi_m_v1_0_S00_AXI.v` implements a 4-register AXI4-Lite slave wrapped around an SPI master.

- `slv_reg0`: TX data
- `slv_reg1`: control bits including `start`, `CPOL`, `CPHA`, and `clk_div`
- read register 2: `done` and `busy` status
- read register 3: RX data

The Vitis side is organized as a small application stack under `AXI_SPI/vitis/src/`, with HAL-level SPI transfer logic in `HAL/SPI/SPI.c` and application control in `ap/ap_main.c`.

### AXI4-Lite I2C IP

`AXI_I2C/ip_repo/i2c_1.0/hdl/i2c_v1_0_S00_AXI.v` uses AXI4-Lite registers to drive an I2C master FSM.

- command bits: `start`, `write`, `read`, `stop`, `ack_in`
- `slv_reg1[7:0]`: TX data
- read status: RX data, `ack_out`, `done_latch`, `busy`
- external pins: `scl`, bidirectional `sda`

The C HAL in `AXI_I2C/vitis/src/ap/I2C/i2c.c` exposes start/stop/write/read level functions for the application layer.

### RV32I + APB System

`RV32I/` contains the CPU datapath/control logic and an APB interconnect for peripherals.

- `RV32_CPU.sv`: control unit and CPU top connection
- `rv32i_datapath.sv`: register file, ALU, PC, immediate extension, mux paths
- `APB_master.sv`: APB IDLE/SETUP/ACCESS FSM, decoder, read mux
- `RV32I_TOP.sv`: BRAM, GPO, GPI, GPIO, FND, UART peripheral integration

The APB decoder selects RAM with `addr[31:28] == 4'h1`. Peripheral space uses `addr[31:28] == 4'h2` and `addr[15:12]` to select GPO, GPI, GPIO, FND, or UART.

### UART/Sensor System

`UART_SR_DHT2/` integrates UART command handling, stopwatch/watch time data, SR04 distance, DHT11 temperature/humidity, and FND output. The portfolio describes this project as a sensor/time sender that formats data as ASCII strings for a PC terminal while maintaining board display output.

## How To Review Or Rebuild

- Open each `.xpr` file with Vivado when board synthesis/implementation context is needed.
- Review `*.srcs/sources_1/new/` and `*.srcs/sources_1/imports/new/` first for authored RTL.
- Review `ip_repo/*/hdl/` for packaged AXI custom IP.
- Review `vitis/src/` for software-side HAL, driver, and application structure.
- Treat `.runs/`, `.gen/`, `.cache/`, `.ip_user_files/`, and `.hw/` as generated Vivado artifacts unless debugging tool output is required.

## Interviewer Guide

If time is short, review in this order:

1. `AXI_SPI/ip_repo/axi_spi_m_1.0/hdl/axi_spi_m_v1_0_S00_AXI.v` - AXI register interface plus SPI control FSM connection.
2. `AXI_I2C/ip_repo/i2c_1.0/hdl/i2c_v1_0_S00_AXI.v` - bidirectional I2C control and status register mapping.
3. `RV32I/RV32I.srcs/sources_1/new/RV32_CPU.sv` and `rv32i_datapath.sv` - ISA decode, control signals, datapath construction.
4. `RV32I/RV32I.srcs/sources_1/new/APB_master.sv` and `RV32I_TOP.sv` - CPU-to-peripheral system integration.
5. `UART_SR_DHT2/UART_SR_DHT2.srcs/sources_1/new/TOP_main.v` - sensor/time/UART board-level integration.

For verification-specific review, see the separate UVM repository or the copied `AXI_SPI/0504_AXI_SPI_UVM/` directory.
